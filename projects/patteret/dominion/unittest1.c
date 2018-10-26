#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

int test(int a, int b, int t);

int main()
{
	int a = 2;
	int b = 2;
	int t = 0;

	printf("---------------Testing the compare function-----------\n");
	t = compare(&a,&b);
	test(a, b, t);

	a = 2;
	b = 3;
	t = compare(&a, &b);
	test(a, b, t);
	
	a = 3;
	b = 2;
	t = compare(&a, &b);
	test(a, b, t);

	a = 3;
	b = 2;
	t = compare(&a, &b);
	t = 5;
	printf("The test below should fail\n");
	test(a, b, t);
	return 0;
}

int test(int a, int b, int t)
{	
	if (t ==  1 && a > b){
		printf(ANSI_COLOR_GREEN"Compare a > b - PASS\n"ANSI_COLOR_RESET);
	}
	else if(t == -1 && a < b){
		printf(ANSI_COLOR_GREEN"Compare b < a - PASS\n"ANSI_COLOR_RESET);
	}
	else if (t == 0 && a == b){
		printf(ANSI_COLOR_GREEN"Compare b = a - PASS\n"ANSI_COLOR_RESET);
	}
	else{
		printf(ANSI_COLOR_RED"Compare FAIL\n"ANSI_COLOR_RESET);
	}
}
