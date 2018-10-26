#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

int unit_test_smithy();
int test(int testHand, int gHand, int testDeck, int gDeck, int testCoins, int gCoins);


int main()
{
	unit_test_smithy();
	return 0;
}

int unit_test_smithy()
{
	int newCards = 0;
	int discarded = 1;
	int extraCoins = 0;
	int shuffledCards = 0;

	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &G);

	printf("\n------------------- Testing Smithy Card:  ------------------\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	newCards = 3;
	extraCoins = 0;

	int testHand = testG.handCount[thisPlayer];
	int gHand = G.handCount[thisPlayer] + newCards - discarded;
	int testDeck = testG.deckCount[thisPlayer];
	int gDeck = G.deckCount[thisPlayer] - newCards + shuffledCards;
	int testCoins = testG.coins;
	int gCoins = G.coins; + extraCoins;

	printf("Cards in hand = %d, should be = %d\n", testHand, gHand);
	printf("deck count = %d, should be = %d\n", testDeck, gDeck);
	printf("coin total = %d, should be = %d\n", testCoins, gCoins);
	test(testHand, gHand, testDeck, gDeck, testCoins, gCoins);

	printf("The below tests should fail\n");

	printf("Cards in hand = %d, should be = %d\n", testHand, gHand);
	printf("deck count = %d, should be = %d\n", testDeck, gDeck);
	printf("coin total = %d, should be = %d\n", testCoins, gCoins);
	test(testHand+2, gHand, testDeck+1, gDeck, testCoins-4, gCoins);
	

	return 0;
}

int test(int testHand, int gHand, int testDeck, int gDeck, int testCoins, int gCoins)
{
	int failCount = 0;
	if (testHand == gHand){
		printf(ANSI_COLOR_GREEN"Card hands are correct - PASS\n"ANSI_COLOR_RESET);
	}
	else{
		printf(ANSI_COLOR_RED"Card hands are not the same - FAIL\n"ANSI_COLOR_RESET);
		failCount++;
	}

	if (testDeck ==  gDeck){
		printf(ANSI_COLOR_GREEN"Card deck are correct - PASS\n"ANSI_COLOR_RESET);
	}
	else{	
		printf(ANSI_COLOR_RED"Card decks are not the same - FAIL\n"ANSI_COLOR_RESET);
		failCount++;
	}

	if (testCoins == gCoins){
		printf(ANSI_COLOR_GREEN"Coin count is correct - PASS\n"ANSI_COLOR_RESET);
	}
	else{	
		printf(ANSI_COLOR_RED"Coin count is not the same - FAIL\n"ANSI_COLOR_RESET);
		failCount++;
	}

	printf("\nTotal fails %d\n", failCount);

	return 0;
}
