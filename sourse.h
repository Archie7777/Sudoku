#pragma once

void generate(int num, char* path);
int process_input(int argc, char* argv[]);
int jdg_rep(int row, int line, int putnum, int sudoku[9][9]);

class game
{
public:
	game(char* path);
	void read();
private:
	int sudoku[9][9];
	char* puzzle_path;
	int confirm[9][9];
	int possible_number[9][9][10]; // -1代表可用，即非零是可用，0代表不可用 ———— 方便初始化
	void solve_puzzle();
	//void output(FILE*);
	void fillnum(int row, int line, int putnum);
};