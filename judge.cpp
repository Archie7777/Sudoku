//******************************
//判断填入数字是否合法
//输入： 填入数字所在的行数、列数、填入数字的值、数独矩阵的指针
//输出： 不合法：false   合法：true
//******************************

#include "pch.h"
#include <cstdio>
using namespace std;

int jdg_rep(int row, int line, int putnum, int sudoku[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		if (i == row) continue;
		if (sudoku[i][line] == putnum)
			return false;
	}
	for (int i = 0; i < 9; i++)
	{
		if (i == line) continue;
		if (sudoku[row][i] == putnum)
			return false;
	}
	for (int i = row - row % 3; i < row - row % 3 + 3; i++)
	{
		for (int j = line - line % 3; j < line - line % 3 + 3; j++)
		{
			if (i == row && j == line) continue;
			if (sudoku[i][j] == putnum) return false;
		}
	}
	return true;
}