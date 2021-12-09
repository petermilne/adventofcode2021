/*
 * day8.cpp
 *
 *  Created on: 8 Dec 2021
 *      Author: pgm
 */

#include <stdio.h>
#include <string.h>

#include <string>

#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include <vector>
#include <map>

#include <assert.h>

using namespace std;

const string SEVEN_SEG[] = {
		"abcefg",		// 0
		"cf",			// 1
		"acdeg",
		"acdfg",
		"bcdf",
		"abdfg",
		"abdefg",
		"acf",
		"abcdefg",
		"abcdfg"
};


string by_seg_count[8] = {};  // index from 1

string candidate_numbers(string segs)
{
	string rc;
	for (int ii = 0; ii < segs.length(); ++ii){
		if (ii) rc += ",";
		rc += SEVEN_SEG[segs[ii]-'0'];
	}
	return rc;
}
// acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab | cdfeb fcadb cdfeb cdbaf
struct DataLine {
	vector<string> inputs;
	vector<string> outputs;

	DataLine() {

	}
};

void get_input(istream& is, vector<DataLine*>& vv)
{
	string the_line;
	while(getline(is, the_line)){
		DataLine* dataline = new DataLine;
		stringstream temp(the_line);
		string tok;
		vector<string>* cursor = &dataline->inputs;
		while(getline(temp, tok, ' ')){
			sort(tok.begin(), tok.end());
			if (tok.compare("|") == 0){
				cursor = &dataline->outputs;
			}else{
				cursor->push_back(tok);
			}
		}
		vv.push_back(dataline);
	}
}

void print(DataLine& dataLine)
{
	for (string s : dataLine.inputs){
		cout << s << " " ;
	}
	cout << " outputs:" << dataLine.outputs.size() << " ";
	for (string s : dataLine.outputs){
		cout << s << " " ;
	}
	cout << endl;
}

void print_input(vector<DataLine*>& vv)
{
	int ii;
	for (DataLine* dataLine: vv){
		cout << setw(3) << ii++ << " unique:" << dataLine->inputs.size() << " ";
		print(*dataLine);
	}
}


void analyse_outputs(vector<DataLine*>& vv)
{
	int unique_outputs = 0;
	for (int ii = 0; ii < vv.size(); ++ii){
		DataLine* dataline = vv[ii];
		for (int jj = 0; jj < dataline->outputs.size(); ++jj){
			string& op = dataline->outputs[jj];
			string& possible_segs = by_seg_count[op.length()];
			if (by_seg_count[op.length()].length() == 1){
				cout << "output:" << dataline->outputs[jj] << " is unique:" << possible_segs[0] <<endl;
				++unique_outputs;
			}else{
				cout << "output:" << dataline->outputs[jj] << " possible:" << possible_segs <<endl;
			}
		}
	}
	cout << "number of unique outputs:" << unique_outputs <<endl;
}

void analyse_unique(vector<DataLine*>& vv)
{
	int unique_outputs = 0;
	for (int ii = 0; ii < vv.size(); ++ii){
		DataLine* dataline = vv[ii];
		for (int jj = 0; jj < dataline->inputs.size(); ++jj){
			string& op = dataline->inputs[jj];
			string& possible_segs = by_seg_count[op.length()];
			if (by_seg_count[op.length()].length() == 1){
				cout << "unique:" << dataline->inputs[jj] << " is unique:" << possible_segs[0] <<endl;
				++unique_outputs;
			}else{
				cout << "unique:" << dataline->inputs[jj] << " possible:" << possible_segs <<endl;
			}
		}
	}
	cout << "number of unique unique:" << unique_outputs <<endl;
}


void print(map<string,vector<string>>& mapping)
{
	map<string, vector<string>>::iterator it;
	int ii = 0;
	for (it = mapping.begin(); it != mapping.end(); ++it){
		cout << "from:" << ii++ << " "<< it->first << " =>" ;
		vector<string> v = it->second;
		for (int ii = 0; ii < v.size(); ++ii){
			if (ii) cout << ",";
			cout << v[ii];
		}
		cout << endl;

	}
}

bool reduce(map<string,string>& mapping, string new_key)
{
	return false;
}

bool debug = true;

void string_remove(string& str, const string& needle)
// if str contains all the chars in needle, remove them, else leave untouched
{
	int nmatch = 0;
	for (int ii = 0; ii < needle.length(); ++ii){
		if (str.find(needle.substr(ii, 1)) != string::npos){
			++nmatch;
		}
	}
	if (nmatch == needle.length()){
		for (int ii = 0; ii < needle.length(); ++ii){
			int isrc = str.find(needle.substr(ii, 1));
			assert (isrc != string::npos);
//			cout << "string_remove:" << str << " erase " << isrc << endl;
			str.erase(isrc, 1);
//			cout << "string_remove:" << str << " erase " << endl;
		}
	}
}

bool contains(const string& str, const string& needle)
/** return true if str contains every char from needle, individually */
{
	for (int ii = 0; ii < needle.length(); ++ii){
		if (str.find(needle.substr(ii, 1)) == str.length()){
			return false;
		}
	}
	return true;
}

void reduce(map<string, vector<string>>& mapping)
{
	map<string, vector<string>>::iterator it;
	map<string, vector<string>>::iterator needle;

	for (needle = it = mapping.begin(); it != mapping.end(); ++it){
		if (it->first.length() < needle->first.length()){
			needle = it;
		}
	}

	for (it = mapping.begin(); it != mapping.end(); ++it){
		if (contains(it->first, needle->first)){
			cout << "find " << it->first << " contains:" << needle->first <<endl;
			int removed = 0;
			int rhs_count = it->second.size();
			for (int jj = 0; jj < it->second.size(); ++jj){
				string& rhs = it->second[jj];
				//cout << "rhs: len" <<rhs.length() << " " << rhs << endl;


				for (string needlestr: needle->second){
					if (needlestr.length() < 1){
						//cout << "short needle" << endl;
						continue;
					}
					if (rhs.compare(needlestr) == 0){
						cout << "identical " << it->first << ":" << rhs << "==" <<needlestr << endl;
					}else if (contains(rhs, needlestr)){
						cout << "	reducing " << it->first << " contains:" << needle->first << " AND " << rhs << " contains:" << needlestr << endl;
						string_remove(rhs, needlestr);
						++removed;
					}else{
						cout << "	rhs " << rhs << "does NOT contain needle " << needlestr << " REMOVE the whole string" << endl;
						it->second.erase(it->second.begin()+jj);
						++removed;
					}
				}
			}

			if (removed == rhs_count){
				cout << "removed:" << removed << " rhs_count:" << rhs_count << endl;

				string newkey = it->first;
				cout << "	compare lhs oldkey:" << it->first << " needle->first:" << needle->first << endl;
				if (newkey.compare(needle->first) == 0){
					cout << "	trim lhs oldkey:" << it->first << "== newkey:" << newkey << endl;
				}else{
					//debug = true;
					string_remove(newkey, needle->first);
					//debug = false;
					cout << "	trim lhs oldkey:" << it->first << " newkey:" << newkey << endl;
					mapping[newkey] = it->second;
					mapping.erase(it);
					return;
				}
			}
		}

	}
}
void solve(DataLine &dl, int maxreduce)
{

	map<string, vector<string>> mapping;

	DataLine tmp = dl;
	cout << "solve: input " <<endl;
	print(dl);

	for (int ii = 0; ii < tmp.inputs.size(); ++ii){
		string from = tmp.inputs[ii];
		string ito = by_seg_count[from.length()];
		vector<string> to;
		for (int jj = 0; jj < ito.length(); ++jj){
			to.push_back(SEVEN_SEG[ito[jj]-'0']);
		}

		mapping[from] = to;
	}

	for (int ii = 0; ii < maxreduce; ++ii){
		cout << "from:mapping so far:" << ii <<endl;
		print(mapping);

		reduce(mapping);

		cout << "from:mapping after reduce:" << ii <<endl;
		print(mapping);
	}

/*
	for (int ii = 0; ii < tmp.inputs.size(); ++ii){
		from = tmp.inputs[ii];
		string to_choices = by_seg_count[from.length()];
		for (int jj = 0; jj < to_choices.length(); ++jj){
			string to = SEVEN_SEG[to_choices[jj]-'0'];
			if (reduce(mapping, to)){
				break;
			}
		}
	}
*/
}

int main(int argc, const char** argv)
{
	int maxreduce = argc==2? atoi(argv[1]): 1;
	vector<DataLine*> data;

	for (int ii = 0; ii < 10; ++ii){
		int segs = SEVEN_SEG[ii].length();
		cout << "no: " << ii << " len:" << segs << " " << SEVEN_SEG[ii] << endl;
		by_seg_count[SEVEN_SEG[ii].length()] += to_string(ii);
	}

	for (int ii = 1; ii <= 7; ++ii){
		cout << "segs:" << ii << " numbers:" << by_seg_count[ii] << " segs:" << candidate_numbers(by_seg_count[ii]) << endl;
	}

	get_input(cin, data);
	print_input(data);
	analyse_outputs(data);
	analyse_unique(data);



	for (DataLine* dl: data){
		solve(*dl, maxreduce);
	}
}
