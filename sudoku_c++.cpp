#include "pch.h"
#include <iostream>
#include <cstdio>
using namespace std;
#include "sourse.h"

int main(int argc, char* argv[])
{
	int n;
	scanf("%d", &n);
	char path[17] = { 'S','u','d','o','k','u','_','f','i','n','a','l','.','t', 'x','t', '\0' };
	generate(n, path);
}