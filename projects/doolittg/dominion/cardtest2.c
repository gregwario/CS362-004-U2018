/*******************
* Greg Doolittle
* CS362 Aburas
* 7/22/2018
* Assignment 3
*
* Description: this file tests the refactored code from assignment 2. Specifically,
* it tests the funciton created for the Adventurer card.
*
* This was added to the makefile to build this test:
* cardtest2: cardtest2.c dominion.o rngs.o assert_equal.o
*	gcc -o cardtest1 -g  cardtest2.c dominion.o rngs.o assert_equal.o $(CFLAGS)
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
	struct gameState G_copy;
	int maxHandCount = 5;

	printf("TESTING Adventurer: cardEffectAdventurer():\n");
	printf("TESTING card effect should add 2 more treasure cards");
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
			int treasureCountBefore = 0;
			int t;
			for (t = 0; t < handCount; t++) {
				if (G.hand[p][t] == copper || G.hand[p][t] == silver || G.hand[p][t] == gold) {
					treasureCountBefore++;
				}
			}
			cardEffectAdventurer(p, &G);				// call the refactored Adventurer function
														// now compare the number of cards in hand. it should have 2 extra treasure cards, minus the 1 
														// Adventurer card played.
														// additionally, i added a bug in assignment 2 that Adventurer will add unlimited gold, and only
														// limits you to added 2 treasures that are copper or silver. This test expects the original 
														// behavior of the card.
			int treasureCountAfter = 0;
			int u;
			for (u = 0; u < G.handCount[p]; u++) {
				if (G.hand[p][u] == copper || G.hand[p][u] == silver || G.hand[p][u] == gold) {
					treasureCountAfter++;
				}
			}

			failureCount += assertEqual(treasureCountBefore == treasureCountAfter - 2);
#if (DEBUGGING == 1)
			printf("treasureCountBefore (%d) and treasureCountAfter (%d), expected a difference of 2\n", treasureCountBefore, treasureCountAfter);
#endif
			// unsure if there's an additional bug here with Adventurer logic. seems like it should discard one more card.
			failureCount += assertEqual(G_copy.handCount[p] == G.handCount[p] - 2); 
#if (DEBUGGING == 1)
			printf("total cards in hand before (%d) and after (%d), expected a difference of 2\n", G_copy.handCount[p], G.handCount[p]);
#endif
		}
	}
	//*failureCount = 1;
	if (failureCount != 0) {
		printf("%d tests FAILED!\n", failureCount);
	}
	else {
		printf("All tests PASSED!\n");
	}
	return 0;
}