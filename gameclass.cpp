#include "pch.h"
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <stack>
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
		if (puzzle_path != NULL)
			strcpy_s(puzzle_path, strlen(path) + 1, path);
	}
	if (file != NULL)
		fclose(file);
}

void game::read()
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
		char temp;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				int end = fscanf_s(readfile, "%d%c", &sudoku[i][j], &temp, (unsigned int)(sizeof(int) + sizeof(char)));
				if (end == EOF) flagtobreak = 1;
			}
		}
		if (flagtobreak == 1) break;
		solve_puzzle();
		if (count != 0) fprintf(writefile, "\n\n");
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (i == 8 && j == 8) fprintf(writefile, "%d", sudoku[i][j]);
				else fprintf(writefile, "%d%c", sudoku[i][j], j == 8 ? '\n' : ' ');
			}
		}
	}
	fclose(readfile);
	return;
}

void game::solve_puzzle()
{
	memset(confirm, 0, sizeof(confirm));
	memset(possible_number, -1, sizeof(possible_number));
	for (int i = 0; i < 9; i++) {//更新所有的状态值
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] != 0) {
				fillnum(i, j, sudoku[i][j]);
			}
		}
	}
	while (1)//找唯一的空
	{
		int flag_of_break = 1;
		int count = 0;
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++) {
				if (confirm[i][j] == 1) continue;
				count = 0;
				int temp = 0;
				for (int x = 1; x <= 9; x++)
				{
					
					if (possible_number[i][j][x] != 0) {
						count++;
						temp = possible_number[i][j][x];
					}
				}
				if (count == 1) sudoku[i][j] = temp;
			}
		if (flag_of_break == 1) break;
	}
	//没有唯一的空了，开始dfs
	stack<int> s;
	int find_first = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
		{
			if (confirm[i][j] == 0) {
				s.push(i * 9 + j);
				for (int x = 1; x <= 9; x++) {
					if (possible_number[i][j][x] != 0) {
						sudoku[i][j] = x;
						find_first = 1;
						break;
					}
				}
				if (find_first == 1) break;
			}
		}
		if (find_first == 1) break;
	}
	while (1)
	{
		int there_is_right_number = 0;
		int flag_to_break = 0;
		int find_empty = 0;
		for (int i = s.empty() ? 0 : (s.top() / 9); i < 9; i++) {
			for (int j = s.empty() ? 0 : (i == s.top() / 9 ? s.top() % 9 + 1 : 0); j < 9; j++) {
				if (confirm[i][j] == 0) {
					find_empty = 1;
					for (int x = sudoku[i][j] + 1; x <= 9; x++)
					{
						if (x == 0) continue;
						if (possible_number[i][j][x] != 0 && jdg_rep(i, j, x, sudoku) == 1) {
							there_is_right_number = 1;
							s.push(i * 9 + j);
							sudoku[i][j] = x;
							flag_to_break = 1;
							break;
						}
					}
					if (there_is_right_number == 0) {
						s.pop();
						sudoku[i][j] = 0;
						flag_to_break = 1;
						break;
					}
				}
				if (flag_to_break == 1) break;
			}
			if (flag_to_break == 1) break;
		}
		if (find_empty == 0) break;
	}
	return;
}

void game::fillnum(int row, int line, int putnum)
{
	confirm[row][line] = 1;
	int srow_of_matrix = row - row % 3;
	int sline_of_matrix = line - line % 3;
	for (int i = 0; i < 9; i++)
	{
		possible_number[row][i][putnum] = 0;
		possible_number[i][line][putnum] = 0;
		possible_number[srow_of_matrix + i / 3][sline_of_matrix + i % 3][putnum] = 0;
	}
	sudoku[row][line] = putnum;
}

//void game::output(FILE* file)
//{
//	for (int i = 0; i < 9; i++) {
//		for (int j = 0; j < 9; j++){
//			fprintf(file, "%d%c", sudoku[i][j], j == 8 ? '\n' : ' ');
//		}
//	}
//	fprintf(file, "\n");
//}