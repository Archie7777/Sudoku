#include "pch.h"
#include "sourse.h"
#include <time.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	clock_t begin, end;
	double cost;
	begin = clock();//开始记录时间

	process_input(argc, argv);

	end = clock();//结束记录时间
	cost = (double)end - (double)begin / CLOCKS_PER_SEC;
	printf("constant CLOCKS_PER_SEC is: %ld, time cost is: %lf secs", CLOCKS_PER_SEC, cost);

}