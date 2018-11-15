#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <math.h>

int randomtest(); // Random test function for Council Room card.
int genRandomInt();// Generates a random seed.
unsigned int CountBits(int n); // Helper function for genRandomInt().
// Tests the conditions of the Council Room card after being played.
int test(int testHand, int gHand, int testNumBuys, int gNumBuys, int numPlayers, struct gameState *testG, struct gameState *G);

int main()
{
	printf("-------------Testing Council Room card-------------\n");
	srand(time(0));// Generate a random seed for time.
	int rtn = 0;// Hold the total returnd errors.
	int i, n = 1000;// Sample size for the tests.
	for (i = 0; i < n;++i){
		printf("--------This is test: %d---------\n", i);
		rtn += randomtest();
		printf("--------End of test: %d----------\n", i);
	}
	printf("\nTotal tests faild %d over a sample size of %d\n", rtn, n);
	return 0;
}

int randomtest()
{
	int numPlayers = (rand() % (4 - 2 + 1) + 2);// Random number of players between two an four.
	int seed = genRandomInt();// Generate a random seed.
	int choice1 = 0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
	int thisPlayer = 0;
	int rtn = 0;

	struct gameState G, testG;// Setup two game states.
				  // G game state will be manually minipulate with
				  // expected output of a played card.
	int k[10] = {steward, embargo, adventurer, minion, mine, cutpurse,
		sea_hag, tribute, smithy, village};

	rtn += initializeGame(numPlayers, k, seed, &G);// Initialize the game.
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 1;
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);// Play the council room card.
	
	// Move the test game state variables values temp values below.
	int testHand = testG.handCount[thisPlayer];
	int gHand = G.handCount[thisPlayer];
	int testNumBuys = testG.numBuys;
	int gNumBuys = G.numBuys;
	// Print out current stats and what they should be.
	printf("Hand count = %d, should be = %d\n", testHand, gHand+3);
	printf("Buy count = %d, Buy count should be = %d\n", testNumBuys, gNumBuys+1);
	rtn += test(testHand, gHand, testNumBuys, gNumBuys, numPlayers, &testG, &G);// Test the conditions of the test game state.

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
	// Loop though until n bits are reached
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

int test(int testHand, int gHand, int testNumBuys, int gNumBuys, int numPlayers, struct gameState *testG, struct gameState *G)
{
	int rtn = 0;// Count the errors that occur.

	// Test hand conditions
	if (testHand == gHand+3){
		printf("Hand Count - PASS\n");
	}
	else{
		printf("Hand Count - FAIL\n");
		rtn += 1;
	}
	if (testNumBuys == gNumBuys+1){
		printf("Buy Count - PASS\n");
	}
	else{
		printf("Buy Count - FAIL\n");
		rtn += 1;
	}

	printf("\nTesting that every other player recived + 1 card.\n");

	int i;// Loop over each player and see if they recived +1 card.
	for (i = 1; i < numPlayers;i++){
		printf("Player %d card count = %d, should be %d - ", i, testG->handCount[i], G->handCount[i]+1);
		if (testG->handCount[i] == G->handCount[i]+1){
			printf("\n");
		}
		else{
			printf("FAIL\n");
			rtn += 1;
		}
	}

	return rtn;
}
