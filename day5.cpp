/*
 * day5.cpp
 *
 *  Created on: 5 Dec 2021
 *      Author: pgm
 *  Consider only horizontal and vertical lines. At how many points do at least two lines overlap?
 *
 * sample input:
0,9 -> 5,9
8,0 -> 0,8
9,4 -> 3,4
2,2 -> 2,1
7,0 -> 7,4
6,4 -> 2,0
0,9 -> 2,9
3,4 -> 1,4
0,0 -> 8,8
5,5 -> 8,2
 */


#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <string.h>

struct Point {
	int x; int y;

	Point(int _x, int _y): x(_x), y(_y) {}
};

struct Line {
	Point p1; Point p2;
	char str[128];

	Line(int x1, int y1, int x2, int y2) : p1(x1, y1), p2(x2, y2) {
		snprintf(str, 128, "%3d,%3d -> %3d,%3d", p1.x, p1.y, p2.x, p2.y);
	}

	bool isHorizontal() const {
		return p1.y == p2.y;
	}
	bool isVertical() const {
		return p1.x == p2.x;
	}
	const char* toString() const {
		return str;
	}
};


typedef std::vector<Line*> VL;

int get_data(std::istream& is, VL* lines)
{
	std::string current;
	while (std::getline(is, current) && current.length() > 1){
		int x1, y1, x2, y2;
		if (sscanf(current.c_str(), "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) == 4){
			lines->push_back(new Line(x1, y1, x2, y2));
		}
	}
	return lines->size();
}



int main(int argc, const char** argv)
{
	VL* lines = new VL;
	int nlines = get_data(std::cin, lines);

	int ii = 0;
	for (Line* l : *lines){
		printf("[%3d] %s %s\n", ii++, l->toString(),
				l->isHorizontal()? "HORIZ": l->isVertical()? "VERT": "SLOPE");
	}
}


