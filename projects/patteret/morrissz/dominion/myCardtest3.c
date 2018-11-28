#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

int test(int testHand, int gHand, int testDeck, int gDeck, int testAct, int gAct);

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
		sea_hag, tribute, smithy, council_room};

	rtn = initializeGame(numPlayers, k, seed, &G);

	memcpy(&testG, &G, sizeof(struct gameState));
	
	choice1 = 1;
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	int testHand = testG.handCount[thisPlayer];
	int gHand = G.handCount[thisPlayer];
	int testDeck = testG.deckCount[thisPlayer];
	int gDeck = G.deckCount[thisPlayer];
	int testAct = testG.numActions;
	int gAct = G.numActions;

	printf("--------Testing Village Card------------\n"); 
	//Village removes one card and adds one card so hand should be the same.
	// Looks like a card is removed from the deck but never added to the hand.
	printf("Hand count = %d, should be = %d\n", testHand, gHand);
	printf("Deck count = %d, Deck be = %d\n", testDeck, gDeck-1);
	printf("Action total = %d, should be = %d\n", testAct, gAct+2);
	test(testHand, gHand, testDeck, gDeck, testAct, gAct);

	printf("The below test should fail, or be be the inverse of the above tests\n");
	test(testHand+1, gHand, testDeck+1, gDeck, testAct+1, gAct);


	return 0;
}

int test(int testHand, int gHand, int testDeck, int gDeck, int testAct, int gAct)
{
	if (testHand == gHand){
		printf(ANSI_COLOR_GREEN"Hand Count - PASS\n"ANSI_COLOR_RESET);
	}
	else{
		printf(ANSI_COLOR_RED"Hand Count - FAIL\n"ANSI_COLOR_RESET);
	}
	if (testDeck == gDeck-1){
		printf(ANSI_COLOR_GREEN"Deck Count - PASS\n"ANSI_COLOR_RESET);
	}
	else{
		printf(ANSI_COLOR_RED"Deck Count - FAIL\n"ANSI_COLOR_RESET);
	}
	if (testAct == gAct+2){
		printf(ANSI_COLOR_GREEN"Action total - PASS\n"ANSI_COLOR_RESET);
	}
	else{	
		printf(ANSI_COLOR_RED"Action total - FAIL\n"ANSI_COLOR_RESET);
	}
}
