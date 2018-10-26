#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"


int main()
{
	int numPlayers = 2;
	int seed = 8432;
	int choice1 = 0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
	int darwnTreasure = 0;
	int cardDrawn;
	int temphand[MAX_HAND];
	int rtn = 0;

	struct gameState G, testG;

	int k[10] = {steward, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	rtn = initializeGame(numPlayers, k, seed, &G);

	memcpy(&testG, &G, sizeof(struct gameState));
	
	choice1 = 1;
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("rtn = %d\n",rtn);

	//printf("Cards in hand = %d, should be = %d\n", testG.handCount[thisPlayer], G.handCount);
	//printf("Deck count = %d, should be = %d\n");
	printf("coins = %d, should be greater than %d\n", testG.coins, G.coins);
	if (testG.coins > G.coins){
		printf(ANSI_COLOR_GREEN"Player obtained coins - PASS\n"ANSI_COLOR_RESET);
	}
	else{
		printf(ANSI_COLOR_RED"Player did not obtain more coins - FAIL\n"ANSI_COLOR_RESET);
	}
	return 0;
}

