/*
test village card effect
*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define NUM_TESTS 100

void testStatus(char *executable, char *testName, bool pass) {
  printf("%s - %s result: %d\n", executable, testName, pass);
}

int main(int argc, char *argv[]) {
  // random seed generator
  srand(time(NULL));

  int i, j;
  int currentPlayer = 0;
  bool pass = 0;
  int changes;
  int randHandPos;
  int originalActionCount, originalHandCount;
  int seedValue = rand() % 1000;
  int cards[10] = {embargo, village, outpost,      salvager, sea_hag,
                   remodel, smithy,  council_room, baron,    tribute};

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

    // cache the original variables
    originalHandCount = gs.handCount[currentPlayer];
    originalActionCount = gs.numActions;

    // change card to village
    gs.hand[currentPlayer][0] = village;
    playCard(0, -1, -1, -1, &gs);

    // verify that it added two actions correctly
    pass = ((originalActionCount + 1) == gs.handCount[currentPlayer]);
    testStatus(argv[0], "village added an action correctly", pass);
    pass = (originalHandCount == gs.handCount[currentPlayer]);
    testStatus(argv[0], "village drew a card correctly", pass);
  }

  return 0;
}
