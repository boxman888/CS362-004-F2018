/*
unit test 1

tests the updateCoins function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(int argc, char *argv[]) {

  int player = 0;
  int bonus = 1;
  int returnValue;

  // clear gamestate and initialize game
  struct gameState gs;
  memset(&gs, 0, sizeof(struct gameState));

  returnValue = updateCoins(player, &gs, bonus);

  return 0;
}
