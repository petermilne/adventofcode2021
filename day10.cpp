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

bool is_opener(char c){
	return pairs.find(c) != pairs.end();
}

bool is_closer(char c){
	return anti_pairs.find(c) != pairs.end();
}


void validate(int line, std::string& str){
	static int score = 0;
	static std::vector<char> stack;


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
				score += costs[c];
				break;
			}
		}
	}
	if (stack.size()){
		std::cout << "ERROR:" << std::setw(3) << line << str << " truncated" << std::endl;
	}else{
		std::cout << "GOOD1:" << std::setw(3) << line << " " << str << std::endl;
	}
	std::cout << "SCORE at " << std::setw(3) << line << ":" << score <<std::endl;
}


int main(int argc, const char** argv){
	std::string str;
	int line = 0;

	while(std::getline(std::cin, str)){
		validate(++line, str);
	}
}
