/*
 * day10.cpp
 *
 *  Created on: 11 Dec 2021
 *      Author: pgm
 */



#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>    // std::sort

#include <iomanip>      // std::setw


std::map<char, char> pairs = {
		{ '(', ')' },
		{ '[', ']' },
		{ '{', '}' },
		{ '<', '>' },
};

std::map<char, char> anti_pairs = {
		{ ')', '(' },
		{ ']', '[' },
		{ '}', '{' },
		{ '>', '<' },
};


std::map<char, int> costs = {
		{ ')',  3 },
		{ ']', 57 },
		{ '}', 1197 },
		{ '>', 25137 },
};

std::map<char, int> repair_costs = {
		{ ')',  1 },
		{ ']',  2 },
		{ '}',  3 },
		{ '>',  4 },
};

bool is_opener(char c){
	return pairs.find(c) != pairs.end();
}

bool is_closer(char c){
	return anti_pairs.find(c) != pairs.end();
}

std::vector<long long> fixup_scores;

int fixup(int line, std::string& str, std::vector<char>& stack)
// correct the line and return score;
{
	long long score = 0;
	while(!stack.empty()){
		char closer = pairs[stack.back()];
		str.append(1, closer);
		score = score*5 + repair_costs[closer];
		stack.pop_back();
	}
	std::cout << "FIXUP:" << std::setw(3) << line << " " << str <<  "score:" << score << std::endl;
	fixup_scores.push_back(score);
	return 0;
}



int validate(int line, std::string& str)
{
	std::vector<char> stack;

	for(int ii; ii < str.length(); ++ii){
		char c = str[ii];
		if (is_opener(c)){
			stack.push_back(c);
		}else if (is_closer(c)){
			if (pairs[stack.back()] == c){
				stack.pop_back();
			}else{
				std::cout << "ERROR:" << std::setw(3) << line << str << std::endl;
				std::cout << "ERROR:" << std::setw(3) << line << std::string(ii, '-') << '^' <<
								" expected:" << pairs[stack.back()] << " got:" << c << std::endl;
				return costs[c];
			}
		}
	}

	if (stack.size()){
		std::cout << "ERROR:" << std::setw(3) << line << str << " truncated" << std::endl;
		fixup(line, str, stack);
	}else{
		std::cout << "GOOD1:" << std::setw(3) << line << " " << str << std::endl;
	}
	return 0;
}



int main(int argc, const char** argv){
	std::string str;
	int total_score = 0;
	int line = 0;

	while(std::getline(std::cin, str)){
		total_score += validate(++line, str);
		std::cout << "SCORE at " << std::setw(3) << line << ":" << total_score <<std::endl;
	}
	std::cout << "SCORE at " << std::setw(3) << line << ":" << total_score <<std::endl;

	std::cout << "FIXUPS:" << fixup_scores.size() << std::endl;

	std::sort(fixup_scores.begin(), fixup_scores.end());
	std::cout << "FIXUP MIDSCORE:" << fixup_scores[fixup_scores.size()/2] << std::endl;
}
