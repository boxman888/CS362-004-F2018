#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

int test(int rtn);

int main()
{
	int rtn = 0;
	int seed = 8345;
	int numPlayers = 2;

	struct gameState G;

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &G);
	rtn = supplyCount(mine, &G);

	printf("-----------------------Testing that supply count returns the correct number of supplys-------------------------\n");
	printf("SupplyCount is %d\n", rtn);
	test(rtn);

	rtn += 1;
	printf("The below test should fail\n");
	printf("SupplyCount is %d\n", rtn);
	test(rtn);

	return 0;
}

int test(int rtn)
{	
	if (rtn == 10){
		printf(ANSI_COLOR_GREEN"SupplyCount - PASS\n"ANSI_COLOR_RESET);
	}
	else{
		printf(ANSI_COLOR_RED"SupplyCount - FAIL\n"ANSI_COLOR_RESET);
	}

	return 0;
}
