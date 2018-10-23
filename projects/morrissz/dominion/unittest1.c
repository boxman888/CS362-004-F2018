/*
unit test 1

tests the isGameOver() function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(int argc, char *argv[]) {

  int i;
  int returnValue;

  // clear gamestate and initialize game
  struct gameState gs;
  memset(&gs, 0, sizeof(struct gameState));

  // set the default values w/ empty gamestate
  returnValue = isGameOver(&gs);
  assert(returnValue == 1);

  // set the supply count to 1 for the first five
  for (i = 0; i < 25; i++) {
    gs.supplyCount[i] = 1;
  }
  returnValue = isGameOver(&gs);
  assert(returnValue == 0);

  // set the province count > 0
  gs.supplyCount[province] = 10;
  returnValue = isGameOver(&gs);
  assert(returnValue == 1);

  return 0;
}
