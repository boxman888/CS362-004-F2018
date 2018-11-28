/*
test smithy card effect
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
  int playedCard = 0;
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

  // change card to smithy
  gs.hand[currentPlayer][0] = smithy;
  playCard(0, -1, -1, -1, &gs);

  // ADDED TEST CODE HERE //
  playedCard = (gs.playedCards[0] == smithy)? 1:0;
  if (playedCard){
    printf("\nPrevious card was smithy - PASS\n");
  }
  else{
     printf("\nPrevious card was not smithy - FAIL\n");
  }
  printf("\nNew hand count is  %d\n",gs.handCount[currentPlayer]);
  printf("\nPrevious hand count is  %d\n",initialHandCount+3);
  // END OF ADDED TEST CODE //
  testStatus(argv[0], "smithy card added 3 to hand", ((initialHandCount + 3) == gs.handCount[currentPlayer]));



  return 0;
}
