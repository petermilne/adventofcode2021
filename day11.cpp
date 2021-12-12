/*
 * day11.cpp
 *
 *  Created on: 12 Dec 2021
 *      Author: pgm
 */

/* game of life simulation with 100 octopi */



#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <string.h>


struct Coord {
	const int x;
	const int y;

	Coord(int _x, int _y): x(_x), y(_y)
	{}
};


std::ostream& operator<< (std::ostream &out, Coord const& data) {
    out << "{ " << data.x << ", " << data.y << " }";
    return out;
}

std::ostream& operator<< (std::ostream &out, std::vector<Coord> const& data) {
	int ii = 0;
	for (Coord c: data){
		if (ii++) out << ",";
		out << c;
	}
    return out;
}

#define ANSI_BOLD_ON 	"\033[1m"
#define ANSI_BOLD_OFF	"\033[0m"

template <int X, int Y>
class Surface {

public:
	char data[X][Y];

	int z(Coord cd) const {
		return data[cd.x][cd.y];
	}
	char& z(Coord cd) {
			return data[cd.x][cd.y];
	}
	std::vector<Coord> neighbours(Coord cd) const {
		std::vector<Coord> nb;
		if (cd.x > 0){
			nb.push_back({cd.x-1, cd.y});
		}
		if (cd.x < X-1){
			nb.push_back({cd.x+1, cd.y});
		}
		if (cd.y > 0){
			nb.push_back({cd.x, cd.y-1});
			if (cd.x > 0){
				nb.push_back({cd.x-1, cd.y-1});		// left upper diag
			}
			if (cd.x < X-1){
				nb.push_back({cd.x+1, cd.y-1});	// right upper diag
			}
		}
		if (cd.y < Y-1){
			nb.push_back({cd.x, cd.y+1});
			if (cd.x > 0){
				nb.push_back({cd.x-1, cd.y+1});		// left upper diag
			}
			if (cd.x < X-1){
				nb.push_back({cd.x+1, cd.y+1});	// right upper diag
			}
		}
		//std::cout << cd << "nb:" << nb << std::endl;

		return nb;
	}

	void print() const {
		for (int yy = 0; yy < Y; ++yy){
			for (int xx = 0; xx < X; xx++){
				//std::cout << "xx:" << xx << " yy:" << yy << " z:" << z({xx, yy}) << std::endl;
				bool flash = data[xx][yy] == 0;
				if (flash){
					std::cout << ANSI_BOLD_ON;
				}
				std::cout << z({xx, yy});
				if (flash){
					std::cout << ANSI_BOLD_OFF;
				}
			}
			std::cout << std::endl;
		}
	}
	int step(int _step) {
		int total_flashes = 0;
		std::cout << "Surface::step() " << _step << std::endl;
		for (int xx = 0; xx < X; xx++){
			for (int yy = 0; yy < Y; ++yy){
				data[xx][yy] += 1;
			}
		}
		int flashes;
		do {
			flashes = 0;
			Surface increments;
			for (int xx = 0; xx < X; xx++){
				for (int yy = 0; yy < Y; ++yy){
					if (data[xx][yy] > 9){
						flashes += 1;
						data[xx][yy] = 0;

						std::vector<Coord> nb = neighbours({xx, yy});
						for (Coord cd: nb){
							increments.z(cd) += 1;
						}
						//std::cout << "FLASH at " << Coord(xx, yy) << "nb:" << nb << std::endl;
					}
				}
			}
			for (int xx = 0; xx < X; xx++){
				for (int yy = 0; yy < Y; ++yy){
					if (data[xx][yy]){
						data[xx][yy] += increments.data[xx][yy];
					}
				}
			}
			//std::cout << "increments:" <<std::endl;
			//increments.print();
			total_flashes += flashes;
		} while(flashes);

		std::cout <<"Total:" << total_flashes << std::endl;
		return total_flashes;
	}

	bool allFlash() {
		for (int xx = 0; xx < X; xx++){
			for (int yy = 0; yy < Y; ++yy){
				if (data[xx][yy]){
					return false;
				}
			}
		}
		return true;
	}
	Surface() {
		memset(data, 0, X*Y);
	}
	Surface(std::istream &in){
		std::string str;
		int yy = 0;
		while(std::getline(in, str)){
			if (str.length() < X){
				std::cerr << "ERROR input too short at line " << yy << "\"" << str << "\"" << std::endl;
			}
			for (int xx = 0; xx < X; ++xx){
				data[xx][yy] = str.c_str()[xx] - '0';
			}
			if (++yy >= Y){
				break;
			}
		}
	}

};


int main(int argc, const char* argv[])
{
	int steps = argc>1? atoi(argv[1]): 0;
	Surface<10,10> surface(std::cin);
	surface.print();
	int flashes = 0;
	for (int step = 1; step <= steps; ++step){
		flashes += surface.step(step);
		surface.print();
		if (surface.allFlash()){
			std::cout << "allFlash at step " << step << std::endl;
			break;
		}
	}
	std::cout <<"Total:" << flashes << std::endl;
	return 0;
}
