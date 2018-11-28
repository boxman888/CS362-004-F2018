#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int randomtest();

int main()
{
	printf("-------------Testing adventurer card-------------\n");
	srand(time(0));
	int i;
	for (i = 0; i < 1000;++i){
		randomtest();
	}
	return 0;
}

int randomtest()
{
	int numberPlayers = (rand() % (4 - 2 + 1) + 2);// Max number of players for a base game is 4.
	// Documentation says game seed cannot be any larger than 2147483647
	// Zero is a reserved value, and negatives will changed to
	// Positives in initalizeGame function.
	unsigned long int seed1 = (rand() % (2147483647 - 1 + 1) + 1);
	// Used to test initializeGame random seed handler
	// for negative numbers.
	long int seed2 = (rand() % (10000 - 1 + -1) + 1) * -1;

	int choice1 = 0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
	int drawnTreasure = 0;
	int temphand[MAX_HAND];
	int rtn1 = 0, rtn2 = 0;
	struct gameState G1, G2, testG1, testG2;

	int k[10] = {steward, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	// Set up game 1.
	printf("\nNumber of players in game1 %d\n", numberPlayers);
	printf("Seed for game1 is %lu\n", seed1);
	rtn1 = initializeGame(numberPlayers, k, seed1, &G1);
	printf("Game initialization returned %d\n\n", rtn1);

	// Set up game 2.
	printf("Number of players in game2 %d\n", numberPlayers);
	printf("Seed for game2 is %ld\n", seed2);
	rtn2 = initializeGame(numberPlayers, k, seed2, &G2);
	printf("Game initialization returned %d\n\n", rtn2);

	memcpy(&testG1, &G1, sizeof(struct gameState));
	memcpy(&testG2, &G2, sizeof(struct gameState));
	// Play card in game 1.
	cardEffect(adventurer, choice1, choice2, choice3, &testG1, handpos, &bonus);
	// Play card in game 2.
	cardEffect(adventurer, choice1, choice2, choice3, &testG2, handpos, &bonus);

	// Test game 1.
	if (testG1.coins > G1.coins){
		printf("Game1 player obtained coins - PASS\n");
	}
	else{
		printf("Game1 player did not obtain more coins - FAIL\n");
	
	}
	// Test game 2
	if (testG2.coins > G2.coins){
		printf("Game2 player obtained coins - PASS\n");
	}
	else{
		printf("Game2 player did not obtain more coins - FAIL\n");
	}
	
	return 0;
}
