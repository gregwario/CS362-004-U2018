/*******************
* Greg Doolittle
* CS362 Aburas
* 7/22/2018
* Assignment 3
*
* Description: this file tests the refactored code from assignment 2. Specifically,
* it tests the function from dominion.c discardCard().
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

	printf("TESTING discardCard():\n");
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
			discardCard(handCount - 1, p, &G, 0);		// call the built-in discardCard function, with trash param turned off

#if (DEBUGGING == 1)
			printf("played card(s): before %d, after %d, expected 1 more after\n", G_before.playedCardCount, G.playedCardCount);
#endif
			failureCount += assertEqual(G.playedCardCount == G_before.playedCardCount + 1);
#if (DEBUGGING == 1)
			printf("current card(s) in hand: before %d, after %d. expected 1 less after\n", G_before.handCount[p], G.handCount[p]);
#endif
			failureCount += assertEqual(G.handCount[p] == G_before.handCount[p] - 1);

		}
	}

	// same loop, with trash flag turned on.
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
			discardCard(handCount - 1, p, &G, 1);		// call the built-in discardCard function, with trash param turned on

#if (DEBUGGING == 1)
			printf("played card(s): before %d, after %d, expected 0 more after\n", G_before.playedCardCount, G.playedCardCount);
#endif
			failureCount += assertEqual(G.playedCardCount == G_before.playedCardCount );
			

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