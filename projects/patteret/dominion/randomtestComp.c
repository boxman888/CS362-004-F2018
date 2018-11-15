#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>

int randomtest();
int genRandomInt();
int test(const void* a, const void* b, const void* t);
int compare(const void* a, const void* b);

int main()
{
	printf("\n-------------Testing the compare funciton in the dominion.c file-------------\n");
	srand(time(0));

	int i;
	for (i = 0; i < 1000;++i){
		randomtest();
	}
	return 0;
}

int randomtest()
{ 
	int num1 = genRandomInt();
	int num2 = genRandomInt();
	int rtn = 0;
	
	rtn = compare(&num1, &num2);
	test(&num1, &num2, &rtn);
	
	return 0;
}

int genRandomInt()
{
	// Get Number of bits in rand this should be 31 bits.
	// The MAX random variable is 2147483647 on osu's server
	const int BITS_IN_RAND = (int)(log2(RAND_MAX) + 1);
	int ret = 0;
	// n holds the number of bits in a char for this machine.
	// This will keep us from making an int overflow.
	int n = CHAR_BIT * sizeof(int);
	// Loop though until n bits are reached
	int i;
	for (int i = 0; i < n; i += BITS_IN_RAND){
		// ret is left shifted by total Bits in rand.
		ret <<= BITS_IN_RAND;
		ret |= rand(); // Bitwise or rand and the left shifted ret.
	}
	return ret;
}

int test(const void* a, const void* b, const void* t)
{
	printf("a is %d\n", *(int*)a);
	printf("b is %d\n", *(int*)b);
	printf("t is %d\n", *(int*)t);

	if (*(int*)t ==  1 && *(int*)a > *(int*)b){
		printf("Compare a > b - PASS\n");
		return 0;
	}
	else if(*(int*)t == -1 && *(int*)a < *(int*)b){
		printf("Compare b < a - PASS\n");
		return 0;
	}
	else if (*(int*)t == 0 && *(int*)a == *(int*)b){
		printf("Compare b = a - PASS\n");
		return 0;
	}
	else{
		printf("Compare FAIL\n");
		return 1;
	}
	return -1;
}
