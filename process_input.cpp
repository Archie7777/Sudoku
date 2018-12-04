//*****************************************
//处理控制台输入
//输入： 控制台参数
//输出： true: 处理正确   false：出现错误
//*****************************************

#include "pch.h"
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
using namespace std;
#include "sourse.h"

char path_of_sudoku[17] = { 'S','u','d','o','k','u','_','f','i','n','a','l','.','t', 'x','t', '\0' }; // 要求生成数独路径

int process_input(int argc, char* argv[])
{
	
	if (argv[1][0] == '-')
	{
		if (argv[1][1] == 'c') {
			for (int i = 0; argv[2][i] != '\0'; i++) {
				if (argv[2][i] <= '9' && argv[2][i] >= '0') continue;
				else {
					printf("请输入十进制整数！\n");
					return false;
				}
			}
			int weight = 1;
			int sum = 0; // 输入数字大小
			for (int i = strlen(argv[2]) - 1; i >= 0; i--)
			{
				sum += weight * (argv[2][i] - '0');
				weight *= 10;
			}
			generate(sum, path_of_sudoku);
			return true;
		}
		else if (argv[1][1] == 's') {
			return true;
		}
		else {
			printf("请输入正确命令\n");
			return false;
		}
	}
	else { 
		printf("请输入正确命令\n"); 
		return false;
	}
}