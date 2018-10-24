/*
unit test 4

tests the shuffle() function
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
  int newDeck[MAX_HAND];
  int currentPlayer = 0;
  int seedValue = 1234;
  int cards[10] = {embargo, ambassador, outpost,      salvager, sea_hag,
                   remodel, gardens,    council_room, baron,    tribute};

  // clear gamestate and initialize game
  struct gameState gs;
  memset(&gs, 0, sizeof(struct gameState));
  initializeGame(2, cards, seedValue, &gs);

  for (i = 0; i < gs.deckCount[currentPlayer]; i++) {
    newDeck[i] = gs.deck[currentPlayer][i];
  }

  shuffle(currentPlayer, &gs);

  // verify that the cards are not in the same order
  test_result = 0;
  for (i = 0; i < gs.deckCount[currentPlayer]; i++) {
    if (newDeck[i] != gs.deck[currentPlayer][i]) {
      test_result = 1;
      break;
    }
  }

  testStatus(argv[0], "shuffle() changed the order of the deck", test_result);

  return 0;
}
