/*
unit test 3

tests the scoreFor() function
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
  int i;
  int test_result;
  int test_score;
  int currentPlayer = 0;
  int seedValue = 1234;
  int cards[10] = {embargo, ambassador, outpost,      salvager, sea_hag,
                   remodel, gardens,    council_room, baron,    tribute};

  // clear gamestate and initialize game
  struct gameState gs;
  memset(&gs, 0, sizeof(struct gameState));
  initializeGame(2, cards, seedValue, &gs);

  // set up scoreFor using estate
  gs.handCount[currentPlayer] = 1;
  gs.deckCount[currentPlayer] = 2;
  gs.discardCount[currentPlayer] = 3;
  for (i = 0; i < gs.handCount[currentPlayer]; i++) {
    gs.hand[currentPlayer][i] = estate;
  }
  for (i = 0; i < gs.deckCount[currentPlayer]; i++) {
    gs.deck[currentPlayer][i] = estate;
  }
  for (i = 0; i < gs.discardCount[currentPlayer]; i++) {
    gs.discard[currentPlayer][i] = estate;
  }

  test_score = scoreFor(currentPlayer, &gs);
  test_result = (test_score == 6); // 6 estate cards
  testStatus(argv[0], "scoreFor() returned correct score for 6 estates", test_result);


  gs.handCount[currentPlayer] = 2;
  gs.deckCount[currentPlayer] = 2;
  gs.discardCount[currentPlayer] = 2;
  for (i = 0; i < gs.handCount[currentPlayer]; i++) {
    gs.hand[currentPlayer][i] = duchy;
  }
  for (i = 0; i < gs.deckCount[currentPlayer]; i++) {
    gs.deck[currentPlayer][i] = duchy;
  }
  for (i = 0; i < gs.discardCount[currentPlayer]; i++) {
    gs.discard[currentPlayer][i] = duchy;
  }

  test_score = scoreFor(currentPlayer, &gs);
  test_result = (test_score == 18); // 6 estate cards
  testStatus(argv[0], "scoreFor() returned correct score for 6 duchy", test_score);

  return 0;
}
