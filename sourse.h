#pragma once
#include <vector>
using namespace std;

void generate(int num, char* path);
int process_input(int argc, char* argv[]);
int jdg_rep(int row, int line, int putnum, int sudoku[9][9]);

class game
{
public:
	game(char* path);
	void solution();
private:
	int sudoku[9][9] = { 0 };
	char* puzzle_path;
	vector <pair <int, int>> vec;
	int get_index(int num);
	int dfs(int now);
};