/*
unit test 4

tests the initializeGame() function
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
  bool pass;
  int seedValue = 1234;
  int cards[10] = {embargo, ambassador, outpost,      salvager, sea_hag,
                   remodel, gardens,    council_room, baron,    tribute};

  // clear gamestate and initialize game
  struct gameState gs;
  memset(&gs, 0, sizeof(struct gameState));

  initializeGame(2, cards, seedValue, &gs);

  pass = gs.numPlayers = 2;
  testStatus(argv[0], "initializeGame() set num players correctly", pass);

  pass = gs.handCount[currentPlayer] = 5;
  testStatus(argv[0], "initializeGame() added 5 cards to current players hand", pass);

  // player 1 should've drawn from deck
  pass = ((gs.deckCount[0] == 5) && (gs.deckCount[1] == 10));
  testStatus(argv[0], "initializeGame() created player decks correctly", pass);

  // player 2 should have 3 estate and 7 copper
  int i;
  int estateCount = 0;
  int copperCount = 0;
  for (i = 0; i < gs.deckCount[1]; i++) {
    if (gs.deck[1][i] == estate) {
      estateCount++;
    } else if (gs.deck[1][i] == copper) {
      copperCount++;
    }
  }
  pass = ((copperCount == 7) && (estateCount == 3));
  testStatus(argv[0], "initializeGame() added the right number of copper and estates", pass);



  return 0;
}
