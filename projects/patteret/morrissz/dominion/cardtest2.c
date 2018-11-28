/*
test adventurer card effect
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

  int i;
  int currentPlayer = 0;
  int seedValue = rand() % 1000;
  int originalHand[MAX_HAND];
  int originalHandCount;
  int cards[10] = {embargo, ambassador, outpost,      salvager, sea_hag,
                   remodel, smithy,     council_room, baron,    tribute};

  // clear gamestate and initialize game
  struct gameState gs;
  memset(&gs, 0, sizeof(struct gameState));
  initializeGame(2, cards, seedValue, &gs);

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
  testStatus(argv[0], "hand has changed since we last drew", pass);
  testStatus(argv[0], "handCount has increased by two new treasure",
             ((originalHandCount + 2) == gs.handCount[currentPlayer]));

  return 0;
}
