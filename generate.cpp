//*****************************************
//生成指定数量数独终局到指定路径文件
//输入：num:生成的终局数量 、 path:输出的指定文件路径
//输出：void
//*****************************************

#include "pch.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
using namespace std;
#include "sourse.h"

int sudoku[9][9] = {0};
int putnum = 0;

void generate(int num, char* path)
{
	sudoku[0][0] = (0 + 8) % 9 + 1;

	errno_t err;
	FILE* file;
	err = fopen_s(&file, path, "w");
	if (file == 0) {
		printf("File not exist!\n");
		return;
	}
	srand((unsigned)time(NULL));
	while (num--)
	{
		for (int i = 1; i < 9; i++)
		{
			sudoku[i / 3][i % 3] = i;
		}
		for (int i = 0; i < 20; i++)
		{
			int a = rand() % 8 + 1;
			int b = rand() % 8 + 1;
			int tmp = sudoku[a / 3][a % 3];
			sudoku[a / 3][a % 3] = sudoku[b / 3][b % 3];
			sudoku[b / 3][b % 3] = tmp;
		}
		for (int a = 0; a < 3; a++) {
			for (int b = 0; b < 3; b++) {
				//枚举每个矩阵
				if (a == 0 && b == 0) continue;
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						int row = i + a * 3;
						int line = j + b * 3;
						sudoku[row][line] = sudoku[(row + b) % 3][(line + a) % 3];
					}
				}
			}
	    }
		for (int i = 0; i < 9; i++) {
			if (num == 0 && i == 8) 
				fprintf(file, "%d %d %d %d %d %d %d %d", sudoku[i][0], sudoku[i][1], sudoku[i][2], sudoku[i][3], sudoku[i][4], sudoku[i][5], sudoku[i][6], sudoku[i][7]);
			else 
				fprintf(file, "%d %d %d %d %d %d %d %d\n", sudoku[i][0], sudoku[i][1], sudoku[i][2], sudoku[i][3], sudoku[i][4], sudoku[i][5], sudoku[i][6], sudoku[i][7]);
		}
		if (num) fprintf(file, "\n");
	}
	fclose(file);
}