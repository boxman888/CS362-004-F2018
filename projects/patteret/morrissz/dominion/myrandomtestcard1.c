#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <math.h>

int randomtest(int testNum, int forceFailFlag);
int genRandomInt();
int test(int testHand, int gHand, int testDeck, int gDeck, int testAct, int gAct);
unsigned int CountBits(int n);

int main()
{
	printf("-------------Testing village card-------------\n");
	srand(time(0));// Generate a random seed for time.
	int rtn = 0;// Hold the total returned errors.
	int i, n = 1000;// Sample size for the tests.
	for (i = 0; i < n;++i){
		printf("--------This is test: %d---------\n", i);
		rtn += randomtest(i, n);
		printf("--------End of test: %d----------\n", i);
	}
	printf("\nTotal tests faild %d over a sample size of %d\n", rtn, n);
	return 0;
}

int randomtest(int testNum, int forceFailFlag)
{	// Random number of players between 2 and 4.
	int numberPlayers = (rand() % (4 - 2 + 1) + 2);// Random number of players between two and four.
	int seed = genRandomInt();// Random integer value.

	int choice1 = 0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
	int thisPlayer = numberPlayers; 
	int rtn = 0;

	struct gameState G, testG;// Setup two game states.
				  // G game state will b manually minipulated with
				  // expected output of a played card.

	int k[10] = {steward, embargo, adventurer, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	printf("\nNumber of Players %d\n", numberPlayers);
	printf("Seed for this game is %d\n", seed);

	rtn += initializeGame(numberPlayers, k, seed, &G);// Initialize the game
	if (rtn == -1){ // If number of players is less than 2.
		return 1;
	}
	
	memcpy(&testG, &G, sizeof(struct gameState));
	
	choice1 = 1;
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	int testHand = testG.handCount[thisPlayer];
	int gHand = G.handCount[thisPlayer];
	int testDeck = testG.deckCount[thisPlayer];
	int gDeck = G.deckCount[thisPlayer];
	int testAct = testG.numActions;
	int gAct = G.numActions;

	// To Garantee that 100% of my test code is run,
	// I force a failure on all tests for the middle sample test.
	if (testNum == forceFailFlag/2){
		testHand += 1;
		testDeck += 1;
		testAct += 1;
	}

	printf("Hand count = %d, should be = %d\n", testHand, gHand);
	printf("Deck count = %d, Deck should be = %d\n", testDeck, gDeck);
	printf("Action total = %d, should be = %d\n\n", testAct, gAct+2);
	rtn += test(testHand, gHand, testDeck, gDeck, testAct, gAct);// Compare the test game state with the manually modified one.

	return rtn;
}
// Generate a random number for an INT min max value based off system
// architecture.
int genRandomInt()
{
	// Get Number of bits in rand this should be 31 bits.
	// The MAX random variable is 2147483647 on osu's server
	int BITS_IN_RAND = CountBits(RAND_MAX);
	int rtn = 0;
	// n holds the number of bits in a char for this machine.
	// This will keep us from making an int overflow.
	int n = CHAR_BIT * sizeof(int);
	// Loop through until n bits are reached
	int i;
	for (i = 0; i < n; i += BITS_IN_RAND){
		// ret is left shifted by total Bits in rand.
		rtn <<= BITS_IN_RAND;
		rtn |= rand(); // Bitwise OR rand and the left shifted ret.
	}
	return rtn;
}
// Helper function for genRandomInt()
// This function will count the number of
// 1 bits in an intiger.
unsigned int CountBits(int n)
{
	unsigned int count = 0;
	while (n){
		n &= (n-1);
		count++;
	}
	return count;
}

// Function compares the test game(testG) and game (G).
// Artificially applys the stats of vilage card to G then preforms the compare.
// There should be no difference between the games at this point. If there is 
// Than a bug is pressent.
int test(int testHand, int gHand, int testDeck, int gDeck, int testAct, int gAct)
{
	int rtn = 0;
	if (testHand == gHand){// Test Hand count.
		printf("Hand Count - PASS\n");
	}
	else{
		printf("Hand Count - FAIL\n");
		rtn += 1;
	}
	if (testDeck == gDeck){// Test Deck count.
		printf("Deck Count - PASS\n");
	}
	else{
		printf("Deck Count - FAIL\n");
		rtn += 1;
	}
	if (testAct == gAct+2){// Test action points.
		printf("Action total - PASS\n");
	}
	else{	
		printf("Action total - FAIL\n");
		rtn += 1;
	}

	return rtn;
}
