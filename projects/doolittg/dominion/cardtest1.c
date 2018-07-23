/*******************
* Greg Doolittle
* CS362 Aburas
* 7/22/2018
* Assignment 3
*
* Description: this file tests the refactored code from assignment 2. Specifically,
* it tests the funciton created for the Smithy card.
* 
* This was added to the makefile to build this test:
* cardtest1: cardtest1.c dominion.o rngs.o assert_equal.o
*	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o assert_equal.o $(CFLAGS)
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

	time_t t;
	srand((unsigned)time(&t));

	int failureCount = 0;
	int seed = rand();
	int numPlayer = 2;
	int p, handCount;
	int cards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	struct gameState G;
	struct gameState G_copy;
	int maxHandCount = 5;

	printf("TESTING Smithy: cardEffectSmithy():\n");
	printf("TESTING card effect should add 3 cards and remove 1 card\n");
	for (p = 0; p < numPlayer; p++)
	{
		for (handCount = 1; handCount <= maxHandCount; handCount++)
		{
#if (DEBUGGING == 1)
			printf("TESTING player % d with %d card(s) in hand.\n", p, handCount);
#endif
			memset(&G, 23, sizeof(struct gameState));   // clear the game state
			initializeGame(numPlayer, cards, seed, &G); // initialize a new game

			G.handCount[p] = handCount;                 // set the number of cards on hand
			memcpy(&G_copy, &G, sizeof(struct gameState)); // make a copy of game state
			cardEffectSmithy(p, &G, 0);					// call the refactored Smithy function
														// now compare the number of cards in hand. it should have 3 extra cards, minus the 1 smithy played.
														// additionally, i added a bug in assignment 2 that smithy adds only 2 cards. after playing it, the 
														// hand count will only go up by 1, but we'll test it as going up by 2, the way it's supposed to be.
			failureCount += assertEqual(G.handCount[p] == G_copy.handCount[p] + 2);
#if (DEBUGGING == 1)
			printf("G.handCount = %d, expected = %d\n", G.handCount[p], G_copy.handCount[p] + 2);
#endif
		}
	}
	//*failureCount = 1;
	if (failureCount != 0) {
		printf("%d tests FAILED!\n", failureCount);
	} else {
		printf("All tests PASSED!\n");
	}
	return 0;
}