/*
test smithy card effect
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

void testStatus(char *executable, char *testName, bool pass) {
  printf("%s - %s result: %d\n", executable, testName, pass);
}

int main(int argc, char *argv[]) {
  // random seed generator
  srand(time(NULL));

  int currentPlayer = 0;
  bool pass = 0;
  int seedValue = rand() % 1000;
  int cards[10] = {embargo, village, outpost,      salvager, sea_hag,
                   remodel, smithy,  council_room, baron,    tribute};

  // clear gamestate and initialize game
  struct gameState gs;
  memset(&gs, 0, sizeof(struct gameState));
  initializeGame(2, cards, seedValue, &gs);

  // cache the original variables
  int originalActionCount = gs.numActions;

  // change card to village
  gs.hand[currentPlayer][0] = village;
  playCard(0, -1, -1, -1, &gs);

  // verify that it added two actions correctly
  pass = ((originalActionCount + 1) == gs.handCount[currentPlayer]);
  testStatus(argv[0], "village added an action correctly", pass);

  return 0;
}
