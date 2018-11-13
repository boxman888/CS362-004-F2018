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

#define NUM_TESTS 50

int main(int argc, char *argv[]) {
  // set random
  srand(time(NULL));

  int j;
  for (j = 0; j < NUM_TESTS; j++) {
    int i, p;
    int test_runs = 0;
    int pass = 0;
    int currentPlayer = 0;
    int seedValue = rand() % 1000;
    int numPlayers = rand() % 2 + 2; // between 2 and 4
    int initialHandCount;
    int desiredHandCount;
    int changes;
    int randHandPos;
    int cards[10];
    int initGameVal;

    // loop for as many times as the test is going to take
    while (!(pass)) {
      test_runs++;

      // randomize cards
      cards[0] = smithy;
      for (p = 1; p < 10; p++) {
        cards[p] = rand() % treasure_map;
      }

      // clear gamestate and initialize game
      struct gameState gs;
      memset(&gs, 0, sizeof(struct gameState));
      initGameVal = initializeGame(numPlayers, cards, seedValue, &gs);
      if (initGameVal == -1) {
        continue;
      }

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

      // verify the handcount and pass the test if its correct
      pass = (desiredHandCount == gs.handCount[currentPlayer]);
    }

    printf("%s - Smithy tests passed on run %d.\n", argv[0], test_runs);
  }

  return 0;
}
