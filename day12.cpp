/*
 * day12.cpp
 *
 *  Created on: 12 Dec 2021
 *      Author: pgm
 */



/* find shortest path */

#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>

#include <string.h>
#include <ctype.h>

#include <assert.h>

using namespace std;

class Cave;

typedef vector<Cave*> VC;
typedef vector<Cave*>::iterator VCI;


vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

class Cave {
public:
	const string name;
	VC links;

	Cave(const Cave& c): name(c.name), links(c.links)
	{}

	Cave(string _name): name(_name)
	{}

	bool isStart() {
		return name.compare("start") == 0;
	}
	bool isEnd() {
		return name.compare("end") == 0;
	}
	bool isTerminal() {
		return isStart() || isEnd();
	}
	bool isLarge() {
		return !isTerminal() && isupper(name.c_str()[0]);
	}
	bool isSmall() {
		return !isTerminal() && islower(name.c_str()[0]);
	}
	bool operator< (const Cave& rhs) const
	{
		return name < rhs.name;
	}
};



std::ostream& operator<< (std::ostream &out, Cave const& cave) {
    out << "{ " << cave.name << ", " << "{ ";
    int ii = 0;
    for (auto c: cave.links){
    	if (ii++) out << ",";
    	out << c->name << ":" << c->links.size();
    }
    out << "} }";
    return out;
}


std::ostream& operator<< (std::ostream &out, vector<Cave*> const& path) {
	out << "path[" << path.size() << "] :";
	int ii = 0;
	for (Cave* pc: path){
		if (ii++) out << "-> ";
		out << pc->name;
	};
    return out;
}

struct CavePointerComp {
    bool operator()(const Cave* lhs, const Cave* rhs) const {
    	return lhs->name < rhs->name;
    }
};


class CaveSystem {
public:
	set<Cave*, CavePointerComp> caves;
	vector<vector<Cave*>*> paths;

	CaveSystem(std::istream &in){
		std::vector<std::string> lines;
		std::string str;
		while (std::getline(in, str)){
			if (str.length() == 0){
				continue;
			}
			lines.push_back(str);
			for (auto tok: split(str, "-")){
				caves.insert(new Cave(tok));
			}
		}

		for (string line: lines){
			vector<string> tokens = split(line, "-");
			set<Cave*>::iterator it1 = caves.find(new Cave(tokens[0]));
			set<Cave*>::iterator it2 = caves.find(new Cave(tokens[1]));
			//cout << "linking" << *it1 << " and " << *it2 << std::endl;
			// set fun. we can't modify set elems, so remove, modify, replace ..
			Cave* t1 = *it1;
			Cave* t2 = *it2;
			caves.erase(it1);
			caves.erase(it2);
			t1->links.push_back(t2);
			t2->links.push_back(t1);
			caves.insert(t1);
			caves.insert(t2);
		}

	}

	void removePath(vector<Cave*>& pp) {
		for (vector<vector<Cave*>*>::iterator it = paths.begin(); it != paths.end(); ++it){
			if (**it == pp){
				cout << "want to erase" << pp << endl; //<< *(*it) << end;
				paths.erase(it);
				break;
			}
		}
	}
	void findPath(vector<Cave*>& pp) {
		assert(pp.size() > 1);
		Cave* head = pp.back();
		if (head->isEnd()){
			cout << "found the END!" << endl;
			return;
		}
		for (int ii = 0; ii < pp.size(); ++ii){
			for (int jj = 0; jj < pp.size(); ++jj){
				if (ii == jj){
					continue;
				}else if (pp[ii] == pp[jj]){
					if (pp[ii]->isLarge()){
						cout << "CYCLE detected LARGE OK" << endl;
						continue;
					}else{
						cout << "CYCLE detected TERMINATE" << endl;
						removePath(pp);
						return;
					}
				}
			}
		}
		Cave* coming_from = pp[pp.size()-2];
		cout << endl;
		cout << "findPath() coming_from:" << *coming_from << " head:" << *head << endl;
		cout << "findPath() " << pp << endl;
		int first = -1;
		for (int ii = 0; ii < head->links.size(); ++ii){
			if (head->links[ii] == coming_from && !head->links[ii]->isLarge()){
				cout << "no going back to " << *coming_from << endl;
			}else if (first == -1){
				first = ii;     // do me last
			}else{
				cout << "[" << ii << "] follow me " << *(head->links[ii]) << endl;
				vector<Cave*>* pp2 = new vector<Cave*> (pp);
				pp2->push_back(head->links[ii]);
				paths.push_back(pp2);
				cout << "recursive call to findPath():" << *pp2 << endl;
				findPath(*pp2);
			}
		}
		if (first == -1){
			cout << "NO FIRST, delete me" << endl;
			removePath(pp);
			return;
		}
		pp.push_back(head->links[first]);
		cout << "push first branch:" << *head->links[0] << endl;

		cout << "recursive call to findPath():" << *pp.back() << endl;
			// if there's no end ... what now?
		findPath(pp);
	}
	void findPaths() {
		auto it = caves.find(new Cave("start"));
		Cave* start = *it;
		cout << *start << endl;

		for (int ii = 0; ii < start->links.size(); ++ii){
			vector<Cave*>* pp = new vector<Cave*>;
			pp->push_back(start);
			pp->push_back(start->links[ii]);
			paths.push_back(pp);
			findPath(*pp);

			cout << *start << "link:" << ii << ": " << *start->links[ii] << endl;
		}
		vector<Cave*> path;
		path.push_back(start);
	}
};


int main(int argc, const char** argv){
	CaveSystem caveSystem(std::cin);
	for (auto c: caveSystem.caves){
		std::cout << *c << endl;
	}
	cout << "Find Paths" << endl;
	caveSystem.findPaths();
	for (auto pv: caveSystem.paths){
		cout << *pv << endl;
	}
}
