#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

int test(int hand, int deck, int rtn, int numPlayers, struct gameState *G);

int main()
{
	int seed = 43;
	int numPlayers = 2;
	int thisPlayer = 0;
	int rtn = 0;

	struct gameState G, badG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	rtn = initializeGame(numPlayers, k, seed, &G);
	
	int hand = G.handCount[thisPlayer];
	int deck = G.deckCount[thisPlayer];
	
	printf("---------Testing initializeGame for deck hand and number of players------\n");

	printf("Number of players is %d\n",G.numPlayers);	
	printf("Number of cards in hand %d\n", hand);
	printf("Number of cards in deck %d\n", deck);
	test(hand, deck, rtn, G.numPlayers, &G);

	hand = badG.handCount[thisPlayer];
	deck = badG.deckCount[thisPlayer];
	rtn = -1;
	printf("This test below  should fail\n");
	printf("Number of players is %d\n",G.numPlayers);	
	printf("Number of cards in hand %d\n", hand);
	printf("Number of cards in deck %d\n", deck);
	test(hand, deck, rtn, badG.numPlayers, &badG);

	return 0;
}

int test(int hand, int deck, int rtn, int numPlayers, struct gameState *G)
{
	if (rtn != -1){
		printf(ANSI_COLOR_GREEN"Return was normal -PASS\n"ANSI_COLOR_RESET);
	}
	else{
		printf(ANSI_COLOR_RED"Return was bad with -1 -FAIL\n"ANSI_COLOR_RESET);
	}
	if (hand == 5){
		printf(ANSI_COLOR_GREEN"Cards in hand is 5 -PASS\n"ANSI_COLOR_RESET);
	}
	else{
		printf(ANSI_COLOR_RED"Cards in hand are not 5 -FAIL\n"ANSI_COLOR_RESET);
	}

	if (deck == 5){
		printf(ANSI_COLOR_GREEN"Cards in deck is 5 -PASS\n"ANSI_COLOR_RESET);
	}
	else{
		printf(ANSI_COLOR_RED"Cards in deck are not 5 -FAIL\n"ANSI_COLOR_RESET);
	}
	if (2 == numPlayers){	
		printf(ANSI_COLOR_GREEN"Game States player count is correct - PASS\n"ANSI_COLOR_RESET);
	}
	else{
		printf(ANSI_COLOR_RED"Game States player count is not correct -FAIL\n"ANSI_COLOR_RESET);
	}

	return 0;
}
