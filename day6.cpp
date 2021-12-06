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

class LanternFish {

public:
	int timer;
	LanternFish(int _timer): timer(_timer)
	{}

	void onNewDay() {
		if (timer == 0){
			lanternFishes.push_back(new LanternFish(8));
			timer = 6;
		}else{
			timer--;
		}
	}
	static std::vector<LanternFish*> lanternFishes;

	static void print(int day) {
		switch(day){
		case 0:
			std::cout << "Initial state: ";
			break;
		case 1:
			std::cout << "After " << std::setw(2) << day << " day : ";
			break;
		default:
			std::cout << "After " << std::setw(2) << day << " days: ";
			break;
		}

		int ii = 0;
		for (LanternFish * lf : lanternFishes){
			if (ii++) std::cout << ',';
			std::cout << lf->timer;
		}
		std::cout << std::endl;
	}

	static int get_data(std::istream& is)
	{
		for (int days; is >> days; ){
			lanternFishes.push_back(new LanternFish(days));
			if (is.peek() == ','){
				is.ignore();
			}
		}
		return lanternFishes.size();
	}

	static void newDay() {
		for (LanternFish * lf : lanternFishes){
			lf->onNewDay();
		}
	}
};

std::vector<LanternFish*> LanternFish::lanternFishes;

int main(int argc, const char** argv)
{
	LanternFish::get_data(std::cin);
	int maxdays = argc>1? atoi(argv[1]): 18;

	std::cout << "Max Size " << LanternFish::lanternFishes.max_size() << std::endl;
	std::cout << "Capacity " << LanternFish::lanternFishes.capacity() << std::endl;
	LanternFish::lanternFishes.reserve(640000);
	int day;
	for (day = 0; day <= maxdays; ++day){
		LanternFish::print(day);
		LanternFish::newDay();
	}
	std::cout << "Total LanternFish population " << LanternFish::lanternFishes.size() <<
					" after " << maxdays << " days" << std::endl;
}


