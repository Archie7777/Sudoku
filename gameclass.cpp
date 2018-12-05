#include "pch.h"
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <stack>
using namespace std;
#include "sourse.h"

game::game(char* path)
{
	errno_t err;
	FILE* file;
	err = fopen_s(&file, path, "r");
	if (err != 0) {
		printf("File not exist!\n");
	}
	else {
		puzzle_path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
		strcpy(puzzle_path, path);
	}
	fclose(file);
}

void game::read()
{
	errno_t err;
	FILE* file;
	err = fopen_s(&file, puzzle_path, "r");
	int flagtobreak = 0;
	for (int i = 0; i < 1; i++) /////////////�� ��
	{
		char temp;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				int end = fscanf(file, "%d%c", &sudoku[i][j], &temp);
				if (end == EOF) flagtobreak = 1;
			}
		}
		solve_puzzle();
		output();
		if (flagtobreak == 1) break;
	}
	fclose(file);
	return;
}

void game::solve_puzzle()
{
	memset(confirm, 0, sizeof(confirm));
	memset(possible_number, -1, sizeof(possible_number));
	for (int i = 0; i < 9; i++) {//�������е�״ֵ̬
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] != 0) {
				fillnum(i, j, sudoku[i][j]);
			}
		}
	}
	while (1)//��Ψһ�Ŀ�
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
	//û��Ψһ�Ŀ��ˣ���ʼdfs
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

void game::output()
{
	printf("output\n");
	errno_t err;
	FILE* file;
	err = fopen_s(&file, "sudoku.txt", "w");
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++){
			fprintf(file, "%d%c", sudoku[i][j], j == 8 ? '\n' : ' ');
		}
	}
	fprintf(file, "\n");
	fclose(file);
}