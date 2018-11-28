/*
test adventurer card randomly

This re-randomly generates multiple hands of cards to verify
that the adventurer card operates correctly on them.

Two additional random sections added:
- Multiple test runs with new random seed values.
- Draw a random amount of cards between 0 and 3 to each player so we
  can emulate a variety of different hand sizes.
*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define NUM_TESTS 100

int main(int argc, char *argv[]) {

  int i;
  int currentPlayer = 0;
  int seedValue;
  int cardsToDraw;
  int originalHand[MAX_HAND];
  int originalHandCount;
  int passes = 0;
  int cards[10] = {embargo, ambassador, outpost,      salvager, sea_hag,
                   remodel, smithy,     council_room, baron,    tribute};

  // run the test a set amount of times
  for (i = 0; i < NUM_TESTS; i++) {

    // set up a new random seed per turn
    seedValue = rand() % 1000;

    // clear gamestate and initialize game
    struct gameState gs;
    memset(&gs, 0, sizeof(struct gameState));
    initializeGame(2, cards, seedValue, &gs);

    // draw between 0 and 3 cards to the players hand
    cardsToDraw = rand() % 3;
    for (i = 0; i < cardsToDraw; i++) {
      drawCard(currentPlayer, &gs);
    }

    for (i = 0; i < gs.handCount[currentPlayer]; i++) {
      originalHand[i] = gs.hand[currentPlayer][i];
    }
    originalHandCount = gs.handCount[currentPlayer];

    // change card to adventurer
    gs.hand[currentPlayer][0] = adventurer;
    playCard(0, -1, -1, -1, &gs);

    // verify that our hand has changed
    bool pass = 0;
    for (i = 0; i < gs.handCount[currentPlayer]; i++) {
      if (originalHand[i] != gs.hand[currentPlayer][i]) {
        pass = 1;
        break;
      }
    }

    // add to number of tests passed
    passes += pass;   
  }

  printf("%s - Adventurer tests passed: %d out of %d", argv[0], passes, NUM_TESTS);

  return 0;
}
