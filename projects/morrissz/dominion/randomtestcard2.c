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

#define MAX_TESTS 5000

int main(int argc, char *argv[]) {
  // random seed generator
  srand(time(NULL));

  int i;
  int j = 0;
  int p = 0;
  int currentPlayer = 0;
  int pass, pass1, pass2;
  int changes;
  int randHandPos;
  int originalActionCount, originalHandCount;
  int seedValue = rand() % 1000;
  int cards[10];
  int initGameVal;

  while (j < MAX_TESTS) {
    j++;

    // randomize cards
    cards[0] = village;
    for (p = 1; p < 10; p++) {
      cards[p] = rand() % treasure_map;
    }

    // clear gamestate and initialize game
    struct gameState gs;
    memset(&gs, 0, sizeof(struct gameState));
    seedValue = (rand() % 1000) + 1;
    initGameVal = initializeGame(2, cards, seedValue, &gs);
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

    // cache the original variables
    originalHandCount = gs.handCount[currentPlayer];
    originalActionCount = gs.numActions;

    // change card to village
    gs.hand[currentPlayer][0] = village;
    playCard(0, -1, -1, -1, &gs);

    // verify that it added two actions correctly
    pass1 = ((originalActionCount + 1) == gs.handCount[currentPlayer]);
    pass2 = (originalHandCount == gs.handCount[currentPlayer]);

    pass = (pass1 && pass2);
    if (pass) {
      break;
    }
  }

  printf("%s village test ran %d iterations and result was: %d\n", argv[0], j, pass);

  return 0;
}
