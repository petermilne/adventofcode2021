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

class LanternFish {

public:
	unsigned char timer;
	LanternFish(int _timer): timer(_timer)
	{}

	int onNewDay()
	// return 1 if new fish
	{
		if (timer == 0){
			timer = 6;
			return 1;
		}else{
			timer--;
			return 0;
		}
	}
	static std::vector<long long int> cohort;

	static void get_data(std::istream& is)
	{
		for (int day = 0; day <= 8; ++day){
			cohort.push_back(0);
		}
		for (int day; is >> day; ){
			cohort[day] ++;
			if (is.peek() == ','){
				is.ignore();
			}
		}
	}

	static void newDay() {
		std::vector<long long int> cohort1;
		std::vector<long long int> newbies;
		for (int day = 0; day <= 8; ++day){
			cohort1.push_back(0);
			newbies.push_back(0);
		}

		for (int age = 0; age <= 8; ++age){
			printf("age:%d cohort:%d\n", age, cohort[age]);
			if (cohort[age]){
				LanternFish lf(age);
				if (lf.onNewDay()){
					newbies[6] = newbies[8] = cohort[age];
					//printf("twins %d %d %d\n", cohort[age], cohort1[6], cohort1[8]);
				}else{
					assert(lf.timer != 8);
					cohort1[lf.timer] = cohort[age];
				}
			}
		}
		for (int day = 0; day <= 8; ++day){
			cohort[day] = cohort1[day] + newbies[day];
		}
	}

	static long long total() {
		long long _total = 0;
		for (int day = 0; day <= 8; ++day){
			_total += cohort[day];
		}
		return _total;
	}

	static void print() {
		for (int day = 0; day <= 8; ++day){
			std::cout << day << ":" << cohort[day] << ",";
		}
		std::cout << " total:" << total() << std::endl;
	}
};

std::vector<long long int> LanternFish::cohort;


int main(int argc, const char** argv)
{
	LanternFish::get_data(std::cin);
	int maxdays = argc>1? atoi(argv[1]): 18;

	int day;
	for (day = 0; day <= maxdays; ++day){
		//std::cout << "population at day " << day << " :" << LanternFish::total() << std::endl;
		LanternFish::print();
		LanternFish::newDay();
	}
	std::cout << "Total LanternFish population " << LanternFish::total() <<
					" after " << maxdays << " days" << std::endl;
}


