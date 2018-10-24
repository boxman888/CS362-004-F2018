/*
unit test 1

tests the endTurn() function
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
  int test_result;
  int currentPlayer;
  int seedValue = 1234;
  int cards[10] = {embargo, ambassador, outpost,      salvager, sea_hag,
                   remodel, gardens,    council_room, baron,    tribute};

  // clear gamestate and initialize game
  struct gameState gs;
  memset(&gs, 0, sizeof(struct gameState));
  initializeGame(2, cards, seedValue, &gs);

  currentPlayer = gs.whoseTurn;

  // end the turn
  endTurn(&gs);

  // verify that it switched to the other player
  test_result = (gs.whoseTurn != currentPlayer);
  testStatus(argv[0], "endTurn switched players correctly", test_result);

  // check that the player has 5 cards
  test_result = (gs.handCount[gs.whoseTurn] == 5);
  testStatus(argv[0], "endTurn drew 5 cards for the new player", test_result);

  // check that num actions and num buys is reset
  test_result = (gs.numActions == 1 && gs.numBuys == 1);
  testStatus(argv[0], "endTurn reset actions and buys correctly", test_result);

  return 0;
}
