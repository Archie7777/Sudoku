//*******************************************
//game类
//说明： 完成数独输入以及解数独功能
//*******************************************

#include "pch.h"
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
#include "sourse.h"

game::game(char* path)
{
	errno_t err;
	FILE* file;
	err = fopen_s(&file, path, "r");
	if (err != 0) {
		printf("文件不存在\n");
	}
	else {
		puzzle_path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
		if (puzzle_path != NULL) {
			strcpy_s(puzzle_path, strlen(path) + 1, path);
		}
	}
	if (file != NULL) {
		fclose(file);
	}
}

void game::solution()
{
	errno_t err;
	FILE* readfile;
	err = fopen_s(&readfile, puzzle_path, "r");
	FILE* writefile;
	fopen_s(&writefile, "sudoku.txt", "w");
	int flagtobreak = 0;
	if (readfile == 0) return;
	for (int count = 0; ; count++)
	{
		// read puzzle
		char temp;
		int number_temp;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				int end = fscanf_s(readfile, "%d%c", &number_temp, &temp, (unsigned int)(sizeof(int) + sizeof(char)));
				if (number_temp == 0) vec.push_back(pair<int, int>(i, j));
				else sudoku[i][j] = 1 << (number_temp - 1);
				if (end == EOF) flagtobreak = 1;
			}
		}
		if (flagtobreak == 1) break;
		//solve
		dfs(0);
		//write puzzle
		if (count != 0) fprintf(writefile, "\n\n");
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (i == 8 && j == 8) fprintf(writefile, "%d", get_index(sudoku[i][j]));
				else fprintf(writefile, "%d%c", get_index(sudoku[i][j]), j == 8 ? '\n' : ' ');
			}
		}
	}
	fclose(readfile);
	return;
}

int game::get_index(int num)
{
	int ans = 0;
	while (num) {
		ans++;
		num >>= 1;
	}
	return ans;
}

int game::dfs(int now)
{
	int row = vec[now].first;
	int line = vec[now].second;
	int f = (1 << 9) - 1;
	for (int i = 0; i < 9; i++) {
		f &= (~sudoku[row][i]) & ((~sudoku[i][line]) & (~sudoku[row / 3 * 3 + i / 3][line / 3 * 3 + i % 3]));
	}
	while (f)
	{
		sudoku[row][line] = f & (-f);
		f &= ~sudoku[row][line];
		if (now < vec.size() - 1 && !dfs(now + 1)) continue;
		else return true;
	}
	sudoku[row][line] = 0;
	return false;
}