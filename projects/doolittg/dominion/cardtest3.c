/*******************
* Greg Doolittle
* CS362 Aburas
* 7/22/2018
* Assignment 3
*
* Description: this file tests the refactored code from assignment 2. Specifically,
* it tests the funciton created for the Council Room card.
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

	time_t t;
	srand((unsigned)time(&t));

	int failureCount = 0;
	int seed = rand();
	int numPlayer = 4;
	int p, handCount;
	int cards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	struct gameState G;
	struct gameState G_before;
	int maxHandCount = 5;

	printf("TESTING Council Room: cardEffectCouncilRoom():\n");
	printf("TESTING card effect should add 4 cards and 1 buy\n");
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
			memcpy(&G_before, &G, sizeof(struct gameState)); // make a copy of game state
			cardEffectCouncilRoom(p, &G, 0);				// call the refactored Council Room function
															// now compare the number of cards in hand. it should have 4 extra cards, minus the 1 
															// Adventurer card played.
#if (DEBUGGING == 1)
			printf("before %d cards, after %d cards, expected 3 more after\n", G_before.handCount[p], G.handCount[p]);
#endif
			failureCount += assertEqual(G_before.handCount[p] == G.handCount[p] - 3);

			// now compare the number of buys in the current state. it should have 1 extra buy
#if (DEBUGGING == 1)
			printf("before %d buys, after %d buys, expected 1 more after \n", G_before.numBuys, G.numBuys);
#endif
			failureCount += assertEqual(G_before.numBuys == G.numBuys - 1);

			// now compare the number of actions in the current state. it should have 1 fewer actions bc
			// we just used one by player this card.
			// additionally, i added a bug in assignment 2 such that Council Room will actually add 1 action 
			// instead of removing 1 action.
#if (DEBUGGING == 1)
			printf("before %d actions, after %d actions, expected 1 less after\n", G_before.numActions, G.numActions);
#endif
			failureCount += assertEqual(G_before.numActions == G.numActions + 1);
		}
	}
	if (failureCount != 0) {
		printf("%d tests FAILED!\n", failureCount);
	}
	else {
		printf("All tests PASSED!\n");
	}
	return 0;
}