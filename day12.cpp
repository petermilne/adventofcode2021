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

using namespace std;

class Cave;

typedef vector<Cave> VC;
typedef vector<Cave>::iterator VCI;


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
    	out << c.name;
    }
    out << "} }";
    return out;
}

class CaveSystem {
public:
	set<Cave> caves;

	CaveSystem(std::istream &in){
		std::vector<std::string> lines;
		std::string str;
		while (std::getline(in, str)){
			if (str.length() == 0){
				continue;
			}
			lines.push_back(str);
			for (auto tok: split(str, "-")){
				caves.insert(Cave(tok));
			}
		}

		for (string line: lines){
			vector<string> tokens = split(line, "-");
			set<Cave>::iterator it1 = caves.find(Cave(tokens[0]));
			set<Cave>::iterator it2 = caves.find(Cave(tokens[1]));
			//cout << "linking" << *it1 << " and " << *it2 << std::endl;
			// set fun. we can't modify set elems, so remove, modify, replace ..
			Cave t1 = *it1;
			Cave t2 = *it2;
			caves.erase(it1);
			caves.erase(it2);
			t1.links.push_back(t2);
			t2.links.push_back(t1);
			caves.insert(t1);
			caves.insert(t2);
		}
	}
};


int main(int argc, const char** argv){
	CaveSystem caveSystem(std::cin);
	for (auto c: caveSystem.caves){
		std::cout << c << endl;
	}
}
