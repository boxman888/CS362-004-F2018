/*
test the smithy card using a random test
generator
*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define NUM_TESTS 100

void testStatus(char *executable, char *testName, bool pass) {
  printf("%s - %s result: %d\n", executable, testName, pass);
}

int main(int argc, char *argv[]) {
  // set random
  srand(time(NULL));

  int i, j;
  int currentPlayer = 0;
  int seedValue = 1234;
  int initialHandCount;
  int desiredHandCount;
  int changes;
  int randHandPos;
  int cards[10] = {embargo, ambassador, outpost,      salvager, sea_hag,
                   remodel, smithy,     council_room, baron,    tribute};

  // loop for as many times as the test is going to take
  for (j = 0; j < NUM_TESTS; j++) {
    // clear gamestate and initialize game
    struct gameState gs;
    memset(&gs, 0, sizeof(struct gameState));
    initializeGame(2, cards, seedValue, &gs);

    // add or subtract a random amount of cards
    changes = rand() % 3;
    for (i = 0; i < changes; i++) {
      // randomly choose between draw and discard
      if (rand() % 2 == 0) {
        // draw random card
        drawCard(currentPlayer, &gs);
      } else {
        // discard random card
        randHandPos = rand() % gs.handCount[currentPlayer];
        discardCard(randHandPos, currentPlayer, &gs, 0);
      }
    }

    // get the initial handcount so we can check that we have +3 - 1
    // to account for discarding the smithy card
    initialHandCount = gs.handCount[currentPlayer];
    desiredHandCount = initialHandCount + 2;

    // change card to smithy
    gs.hand[currentPlayer][0] = smithy;
    playCard(0, -1, -1, -1, &gs);

    testStatus(argv[0], "smithy card added 3 to hand", (desiredHandCount == gs.handCount[currentPlayer]));
  }

  return 0;
}
