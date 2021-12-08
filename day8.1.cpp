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

using namespace std;

const char* SEVEN_SEG[] = {
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
	vector<string> unique;
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
		vector<string>* cursor = &dataline->unique;
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

void print_input(vector<DataLine*>& vv)
{
	int ii;
	for (DataLine* dataLine: vv){
		cout << setw(3) << ii++ << " unique:" << dataLine->unique.size() << " ";
		for (string s : dataLine->unique){
			cout << s << " " ;
		}
		cout << " outputs:" << dataLine->outputs.size() << " ";
		for (string s : dataLine->outputs){
			cout << s << " " ;
		}
		cout << endl;
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

int main(int argc, const char** argv)
{

	vector<DataLine*> data;

	for (int ii = 0; ii < 10; ++ii){
		int segs = strlen(SEVEN_SEG[ii]);
		cout << "no: " << ii << " len:" << segs << " " << SEVEN_SEG[ii] << endl;
		by_seg_count[strlen(SEVEN_SEG[ii])] += to_string(ii);
	}

	for (int ii = 1; ii <= 7; ++ii){
		cout << "segs:" << ii << " numbers:" << by_seg_count[ii] << " segs:" << candidate_numbers(by_seg_count[ii]) << endl;
	}

	get_input(cin, data);
	print_input(data);
	analyse_outputs(data);
}
