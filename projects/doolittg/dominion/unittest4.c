/*******************
* Greg Doolittle
* CS362 Aburas
* 7/22/2018
* Assignment 3
*
* Description: this file tests the refactored code from assignment 2. Specifically,
* it tests the function from dominion.c ().
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

	int i;
	int score;
	struct gameState G;

	score = 0;
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, cards, seed, &G); // initialize a new game
	G.hand[0][0] = curse;
	G.hand[0][1] = curse;
	G.hand[0][2] = curse;
	G.hand[0][3] = province;
	G.hand[0][4] = province;
	G.handCount[0] = 5;
	printf("expected: 3 curses (-1) and 2 provinces (6) = 9, result: %d\n", scoreFor(0, &G));
	failureCount += assertEqual(9 == scoreFor(0, &G));

	score = 0;
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, cards, seed, &G); // initialize a new game
	G.hand[1][0] = duchy;
	G.hand[1][1] = duchy;
	G.discard[1][0] = province;
	G.handCount[1] = 2;
	G.discardCount[1] = 1;
	printf("expected: 2 duchy in hand (3) and 1 province (6) in discard = 12, result: %d\n", scoreFor(1, &G));
	failureCount += assertEqual(12 == scoreFor(1, &G));

	score = 0;
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, cards, seed, &G); // initialize a new game
	G.hand[2][0] = duchy;
	G.discard[2][0] = province;
	G.deck[2][0] = province;
	G.deck[2][0] = province;
	G.handCount[2] = 1;
	G.discardCount[2] = 1;
	G.deckCount[2] = 2;
	printf("expected: 1 duchy in hand (3) and 1 province (6) in discard, and 2 provinces (6) in deck = 21, result: %d\n", scoreFor(1, &G));
	failureCount += assertEqual(21 == scoreFor(2, &G));

	if (failureCount != 0) {
		printf("%d tests FAILED!\n", failureCount);
	}
	else {
		printf("All tests PASSED!\n");
	}
	return 0;
}