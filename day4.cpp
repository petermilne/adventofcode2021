// make day4
// ./day4 < day4.dat
//
//
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <string.h>

template<int R, int C>
class BingoBoard {
	int numbers[R][C];
	bool called[R][C];
	int the_score;
public:
	const int board_number;

	BingoBoard(int bn) : the_score(0), board_number(bn) {
		memset(called, 0, R*C*sizeof(bool));
	}
	virtual ~BingoBoard() {

	}

	bool full_row(int row) {
		for (int col = 0; col < C; ++col){
			if (!called[row][col]){
				return false;
			}
		}
		return true;
	}

	bool full_col(int col){
		for (int row = 0; row < R; ++row){
			if (!called[row][col]){
				return false;
			}
		}
		return true;
	}

	bool bingo() {
		for (int row = 0; row < R; ++row){
			if (full_row(row)){
				return true;
			}
		}
		for (int col = 0; col < C; ++col){
			if (full_col(col)){
				return true;
			}
		}
		return false;
	}
	void print() {
		for (int row = 0; row < R; ++row){
			for (int col = 0; col < C; ++col){
				printf("%s%2d%s ", 
						called[row][col]? "\x1B[1m": "",
						numbers[row][col],
						called[row][col]? "\x1B[0m": "");	

			}
			printf("\n");
		}
	}

	int play(int call)
	{
		for (int row = 0; row < R; ++row){
			for (int col = 0; col < R; ++col){
				if (call == numbers[row][col]){
					called[row][col] = true;
/*					
					std::cout << "called [" << row << "][" << col << "] " 
										<< call << std::endl;
*/										
					if (bingo()){
						return score(call);
					}
/*
					std::cout << "play: " << call << std::endl;
					print();
*/					
				}
			}
		}
		return 0;
	}

	int score(int call) {
		int total_unmarked = 0;
		for (int row = 0; row < R; ++row){
			for (int col = 0; col < C; ++col){
				if (!called[row][col]){
					total_unmarked += numbers[row][col];
				}
			}
		}
		return the_score = total_unmarked * call;
	}
	int score() const {
		return the_score;
	}

	static std::vector<BingoBoard<R,C>*> &factory(std::istream& in);
};

template<int R, int C>
std::vector<BingoBoard<R,C>*> &BingoBoard<R,C>::factory(std::istream &in)
{
	std::vector<BingoBoard<R,C>*> *bbv = new std::vector<BingoBoard<R,C>*>;
	int ib = 0;

	while (!in.eof()){
				
		BingoBoard<R,C> *bb = new BingoBoard<R,C>(ib+1);
		for (int row = 0; row < R; ++row){
			for (int col = 0; col < C; ++col){
				in >> bb->numbers[row][col];
			}
		}
		bbv->push_back(bb);

		if (++ib == 100){
			printf("WORKTOD: eof dodgy, quit at 100 up \n");
			break;
		}
	}
	return *bbv;
}

typedef BingoBoard<5,5> BB55;
typedef std::vector<BingoBoard<5,5>*> BB55V;

int main(int argc, char* argv[])
{
	//https://www.tutorialspoint.com/parsing-a-comma-delimited-std-string-in-cplusplus
	std::string _calls;
	std::getline(std::cin, _calls);
/*
	std::cout << "Calls:" << _calls << std::endl;
*/
	std::vector<int> calls;
	std::stringstream s_stream(_calls);
	while(s_stream.good()){
		std::string substr;
		std::getline(s_stream, substr, ',');
		calls.push_back(std::stoi(substr));
	}
	
	int ic = 1;
/*
	for (int cc : calls){
		std::cout << "Call:" << ic++ << " " << cc << std::endl;
	}
*/
	BB55V boards = BB55::factory(std::cin);
/*
	int ib = 1;
	for (BB55 board : boards){
		std::cout << "Board: " << ib++ << std::endl;
		board.print();
	}
*/
	// Showtime!
	//
	BB55* last_board_standing = 0;

	ic = 1;
	for (int cc : calls){
/*		
		std::cout << "Call:" << ic++ << " " << cc << std::endl;
*/		

		std::vector<int> erase_list;
		int ib = 0;
		for (BB55* board: boards){
	/*	
			std::cout << "playing board " << board->board_number << 
							" number " << cc << std::endl;
	*/	
			int score = board->play(cc);
			if (score){
				std::cout << "BINGO: board " << board->board_number 
						<< " score:" << score << std::endl;
				board->print();
				erase_list.push_back(ib);
				last_board_standing = board;
				std::cout << "boards remaining: " << boards.size() <<
					" erase list " << erase_list.size() << std::endl;
			}
			ib++;
		}
		for (int ib = erase_list.size() - 1; ib >= 0; --ib){
			boards.erase(boards.begin()+ib);
		}
		if (boards.size() == 1){
			break;
		}
	}		
	if (last_board_standing){
		std::cout << "Last Board Standing #" << last_board_standing->board_number 
				<< " score:" << last_board_standing->score() << std::endl;
		last_board_standing->print();
	}
}

