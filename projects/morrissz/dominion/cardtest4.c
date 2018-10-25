/*
test outpost card effect
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
  int seedValue = 1234;
  int cards[10] = {embargo, ambassador, smithy,       salvager, sea_hag,
                   remodel, outpost,    council_room, baron,    tribute};

  // clear gamestate and initialize game
  struct gameState gs;
  memset(&gs, 0, sizeof(struct gameState));
  initializeGame(2, cards, seedValue, &gs);

  // specifically set numActions/buys to 1
  gs.numActions = 1;
  gs.numBuys = 1;

  // cache the original variables
  int originalWhoseTurn = gs.whoseTurn;

  // change card to village
  gs.hand[currentPlayer][0] = outpost;
  playCard(0, -1, -1, -1, &gs);

  testStatus(argv[0], "outpost played flag was set correctly", (gs.outpostPlayed > 0));

  // outpost should let you have another turn
  endTurn(&gs);
  pass = (gs.whoseTurn == originalWhoseTurn);
  testStatus(argv[0], "outpost should let the player have another turn", pass);

  return 0;
}
