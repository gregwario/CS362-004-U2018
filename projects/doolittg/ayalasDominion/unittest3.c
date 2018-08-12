/*******************
* Greg Doolittle
* CS362 Aburas
* 7/22/2018
* Assignment 3
*
* Description: this file tests the refactored code from assignment 2. Specifically,
* it tests the function from dominion.c getCost().
*
* This was added to the makefile to build this test:
* cardtest3: cardtest3.c dominion.o rngs.o assert_equal.o
*	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o assert_equal.o $(CFLAGS)
********************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "assert_equal.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <time.h>

// set DEBUGGING to 0 to remove printfs from output
#define DEBUGGING 1

int main() {

	int failureCount = 0;
	int cards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	printf("TESTING getCost():\n");
	int costs[10] = { 6, 5, 4, 4, 5, 4, 4, 3, 4, 3};
	int i;
	for (i = 0; i < 10; i++) {
#if (DEBUGGING == 1)
		printf("card[%d] should cost: %d, and getCost(card[%d]) is %d.\n", i, costs[i], i, getCost(cards[i]));
#endif
		failureCount += assertEqual(costs[i] == getCost(cards[i]));
	}

	if (failureCount != 0) {
		printf("%d tests FAILED!\n", failureCount);
	}
	else {
		printf("All tests PASSED!\n");
	}
	return 0;
}