/*

*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void testStatus(char *executable, char *testName, bool pass) {
  printf("%s - %s result: %d\n", executable, testName, pass);
}

int main(int argc, char *argv[]) {
  int currentPlayer = 0;
  int seedValue = 1234;
  int initialHandCount;
  int cards[10] = {embargo, ambassador, outpost,      salvager, sea_hag,
                   remodel, smithy,     council_room, baron,    tribute};

  // clear gamestate and initialize game
  struct gameState gs;
  memset(&gs, 0, sizeof(struct gameState));
  initializeGame(2, cards, seedValue, &gs);

  // get the initial handcount so we can check that we have +3
  initialHandCount = gs.handCount[currentPlayer];

  return 0;
}
