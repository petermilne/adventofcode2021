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

// uncomment this line to run SAMPLE
//#define SAMPLE 1
#ifdef SAMPLE
#define CMAX 10
#else
#define CMAX 1000
#endif

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

	// this nomenclature is BAD because y1 could pair with x2 ..
	int y1() const {
		return std::min(p1.y, p2.y);
	}
	int y2() const {
		return std::max(p1.y, p2.y);
	}
	int x1() const {
		return std::min(p1.x, p2.x);
	}
	int x2() const {
		return std::max(p1.x, p2.x);
	}
	bool isHorizontal() const {
		return p1.y == p2.y;
	}
	bool isVertical() const {
		return p1.x == p2.x;
	}
	bool isDiagonal() const {
		return y2()-y1() == x2()-x1();
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


template <int R, int C>
class Canvas {
public:
	int points[R][C];

	Canvas() {
		memset(points, 0, sizeof(R*C));		// may not be necessary ?
	}
	void draw(Line* line){
		if (line->isHorizontal()){
			for (int x = line->x1(); x <= line->x2(); ++x){
				points[line->p1.y][x] ++;
			}
		}else if (line->isVertical()){
			for (int y = line->y1(); y <= line->y2(); ++y){
				points[y][line->p1.x] ++;
			}
		}else if (line->isDiagonal()){
			int dx = line->p2.x - line->p1.x > 0? 1: -1;
			int dy = line->p2.y - line->p1.y > 0? 1: -1;
			int steps = line->x2() - line->x1();
			for (int step = 0; step <= steps; ++step){
				points[line->p1.y+step*dy][line->p1.x+step*dx] ++;
			}
		}else{
			printf("SORRY, WORKTODO %s\n", line->toString());
		}
	}
	void print() {
		for (int y = 0; y < R; ++y){
			for (int x = 0; x < C; ++x){
				printf("%c", points[y][x]>9? '*': points[y][x]? points[y][x]+'0': '.');
			}
			printf("\n");
		}
	}
};

int main(int argc, const char** argv)
{
	VL* lines = new VL;
	int nlines = get_data(std::cin, lines);

	static Canvas<CMAX,CMAX> canvas; 			// use the heap, avoid blowing the stack

	int ii = 0;
	for (Line* l : *lines){
		printf("[%3d] %s %s\n", ii++, l->toString(),
				l->isHorizontal()? "HORIZ": l->isVertical()? "VERT": l->isDiagonal()? "DIAG": "SLOPE");
		canvas.draw(l);
#ifdef SAMPLE
		canvas.print();
#endif
	}

	int total_gt_1 = 0;
	for (int r = 0; r < CMAX; ++r){
		for (int c = 0; c < CMAX; ++c){
			if (canvas.points[r][c] > 1){
				total_gt_1 ++;
			}
		}
	}
	std::cout << "total points gt1 " << total_gt_1 << std::endl;
}


