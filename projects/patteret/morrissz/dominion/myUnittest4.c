#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

int test(int costRtn, int num ,int i);

int main()
{
	int costRtn = 0;
	int cardList[27] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
	size_t n = sizeof(cardList)/sizeof(cardList[0]);

	printf("-------------Testing ALL Cards Values------------\n");
	int i;
	for (i = 0; i < n;++i){
		printf("The test below should PASS");
		costRtn = getCost(i);
		test(costRtn,cardList[i], i);
		printf("The next test below should FAIL\n");
		test(costRtn+1000, cardList[i], i);
	}

	return 0;
}

int test(int costRtn, int num ,int i)
{
		printf("Cost of card %d is %d, should be %d\n", i, costRtn, num);
		if (costRtn == num){
			printf(ANSI_COLOR_GREEN"Card %d - PASS\n"ANSI_COLOR_RESET,i);
		}
		else{
			printf(ANSI_COLOR_RED"Card %d - FAIL\n"ANSI_COLOR_RESET,i);
		}
	return 0;
}
