/*
 * day6.cpp
 *
 *  Created on: 6 Dec 2021
 *      Author: pgm
 */


#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <functional>
#include <cmath>


static void get_data(std::istream& is, std::vector<int>& vv)
{
	for (int xx; is >> xx; ){
		vv.push_back(xx);
		if (is.peek() == ','){
			is.ignore();
		}
	}
}

static void show_data(std::vector<int>& vv){
	int ii = 0;
	for (int vx: vv){
	    if (ii++){
	    	std::cout << ",";
	    }
		std::cout << vx;
	}
	std::cout << std::endl;
	std::cout << "number of elements:" << ii << std::endl;	
}

static int cost(std::vector<int>& hp, int target)
{
	int _cost = 0;
	for (int hpx: hp){
		int steps = std::abs(hpx-target);

		for (int istep = 1; istep <= steps; ++istep){
			_cost += istep;
		}
	}
	return _cost;
}

static int calc_mean(std::vector<int>& hp)
{
	int sum = 0;
	for (int hpx: hp){
		sum += hpx;
	}
	return sum/hp.size();
}
int main(int argc, const char** argv)
{
	std::vector<int> hp;
	
	get_data(std::cin, hp);
	
	std::sort(hp.begin(), hp.end());
	
	int mean = calc_mean(hp);
	int median = hp.size()/2;
	int mode = (hp[hp.size()/2-1]+hp[hp.size()/2])/2;
	
	show_data(hp);
	
	std::cout << "mean:"<< mean << " mode:" << mode << std::endl;
	
	std::cout << "mean:" << mean << " cost of mean: " << cost(hp, mean) << std::endl;
	std::cout << "mode:" << mode << " cost of mode: " << cost(hp, mode) << std::endl;
	std::cout << "median:" << median << " cost of median: " << cost(hp, median) << std::endl;
}
