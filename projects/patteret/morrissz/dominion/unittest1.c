/*
unit test 1

tests the isGameOver() function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "rngs.h"

void testStatus(char *executable, char *testName, bool pass) {
  printf("%s - %s result: %d\n", executable, testName, pass);
}

int main(int argc, char *argv[]) {

  int i;
  int returnValue;
  bool test_result;

  // clear gamestate and initialize game
  struct gameState gs;
  memset(&gs, 0, sizeof(struct gameState));

  // set the default values w/ empty gamestate
  returnValue = isGameOver(&gs);
  test_result = (returnValue == 1);
  testStatus(argv[0], "isGameOver() is true by w/ empty gamestate", test_result);

  // set the supply count to 1 for the first five
  // means that there are still enough cards left
  for (i = 0; i < 25; i++) {
    gs.supplyCount[i] = 1;
  }
  returnValue = isGameOver(&gs);
  test_result = (returnValue == 0);
  testStatus(argv[0], "isGameOver() when all card types still available", test_result);

  // set the province count > 0
  gs.supplyCount[province] = 10;
  returnValue = isGameOver(&gs);
  test_result = (returnValue == 0);
  testStatus(argv[0], "isGameOver() when enough provinces still available", test_result);

  return 0;
}
