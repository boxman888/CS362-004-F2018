#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

int test(int testHand, int gHand, int testNumBuys, int gNumBuys, int numPlayers, struct gameState *testG, struct gameState *G);

int main()
{
	int numPlayers = 2;
	int seed = 8432;
	int choice1 = 0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
	int darwnTreasure = 0;
	int thisPlayer = 0;
	int temphand[MAX_HAND];
	int rtn = 0;

	struct gameState G, testG;

	int k[10] = {steward, embargo, adventurer, minion, mine, cutpurse,
		sea_hag, tribute, smithy, village};
	printf("---------Testing Council Room Card---------------\n");
	rtn = initializeGame(numPlayers, k, seed, &G);

	memcpy(&testG, &G, sizeof(struct gameState));
	
	choice1 = 1;
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	printf("\nTesting that the player of Council room recived card benefits.\n");

	int testHand = testG.handCount[thisPlayer];
	int gHand = G.handCount[thisPlayer];
	int testNumBuys = testG.numBuys;
	int gNumBuys = G.numBuys;

	printf("Hand count = %d, should be = %d\n", testHand, gHand+3);
	printf("Buy count = %d, Buy count should be = %d\n", testNumBuys, gNumBuys+1);
	test(testHand, gHand, testNumBuys, gNumBuys, numPlayers, &testG, &G);	

	printf("This test will be the opposite of the above test.\n");
	printf("Hand count = %d, should be = %d\n", testHand-2, gHand+3);
	printf("Buy count = %d, Buy count should be = %d\n", testNumBuys+2, gNumBuys+1);
	testG.handCount[1] += 1;
	test(testHand-2, gHand, testNumBuys+2, gNumBuys, numPlayers, &testG, &G);	
	
	return 0;
}

int test(int testHand, int gHand, int testNumBuys, int gNumBuys, int numPlayers, struct gameState *testG, struct gameState *G)
{
	if (testHand == gHand+3){
		printf(ANSI_COLOR_GREEN"Hand Count - PASS\n"ANSI_COLOR_RESET);
	}
	else{
		printf(ANSI_COLOR_RED"Hand Count - FAIL\n"ANSI_COLOR_RESET);
	}
	if (testNumBuys == gNumBuys+1){
		printf(ANSI_COLOR_GREEN"Buy Count - PASS\n"ANSI_COLOR_RESET);
	}
	else{
		printf(ANSI_COLOR_RED"Buy Count - FAIL\n"ANSI_COLOR_RESET);
	}

	printf("\nTesting that every other player recived + 1 card.\n");

	int i;
	for (i = 1; i < numPlayers;i++){
		printf("Player %d card count = %d, should be %d - ", i, testG->handCount[i], G->handCount[i]+1);
		if (testG->handCount[i] == G->handCount[i]+1){
			printf(ANSI_COLOR_GREEN"PASS\n"ANSI_COLOR_RESET);
		}
		else{
			printf(ANSI_COLOR_RED"FAIL\n"ANSI_COLOR_RESET);
		}
	}

	return 0;
}
