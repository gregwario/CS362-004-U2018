/*******************
* Greg Doolittle
* CS362 Aburas
* 8/5/2018
* Assignment 4
*
* Description: this file tests the refactored code from assignment 2. Specifically,
* it adds random tests for the smithy card.
* 
* This was added to the makefile to build this test:
* randomtestcard1: randomtestcard1.c dominion.o rngs.o assert_equal.o
*	gcc -o randomtestcard -g  randomtestcard1.c dominion.o rngs.o assert_equal.o $(CFLAGS)
********************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "assert_equal.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include <time.h>
#include <math.h>
// set DEBUG to 0 to remove additional printfs from output
#ifndef DEBUG
#define DEBUG 1
#endif

int checkSmithyCard(int p, struct gameState *post, int handPos);

int main() {

	time_t t;
	srand((unsigned)time(&t));

	//int p, handCount;
	int cards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	struct gameState G;

	printf("TESTING (random test of smithy card):\n");
	// card should add 3 cards and remove 1 card
    
    const int NUM_TESTS = 50000; // roughly 10% failure rate
    int i = 0;
    int failureCount = 0;
    
    while (i < NUM_TESTS) {
        // printf("test number %d\n", i);
        // randomly arrange game state
	    int seed = rand();
        int numPlayers = 2; //rand() % 9 + 2; // 2-10 players
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayers, cards, seed, &G); // initialize a new game

        // set the other random elements we need
        int p = rand() % numPlayers; // any player
        int handP = rand() % 5; // any of 5 cards in hand
        G.handCount[p] = 5;

        G.whoseTurn = p; //player;
        G.deckCount[p] = rand() % 80 / 2;
        G.handCount[p] = rand() % 20 / 2; 

        // randomly select a player
        // call checkSmithyCard
        failureCount += checkSmithyCard(p, &G, handP);
        i++;
    }
    printf("Testing complete, after %d tests run.\n", NUM_TESTS);
    if (failureCount) {
        printf("Found %d test failures while testing Smithy.\n", failureCount);
    } else {
        printf("No test failures found while testing Smithy.\nAll tests pass!\n");
    }
}

int checkSmithyCard(int p, struct gameState *post, int handPos) {

    struct gameState *pre;
    pre = (struct gameState*) malloc(sizeof(struct gameState));
    memcpy(pre, post, sizeof(struct gameState));

    int r;

    // we'll call cardEffect, and use smithy card on 'post' game state
    r = cardEffect(smithy, 0, 0, 0, post, handPos, 0);
    assert(r == 0);
    
    // we'll manually run smithy on 'pre' game state
    int i;
    for (i = 0; i < 3; i++) { // draw 3 cards, 
        // this version of smithy has a bug 
        // that only draws 2 cards.
        if (pre->deckCount[p] > 0) {
            drawCard(p, pre);
        }
    }
    discardCard(handPos, p, pre, 0);
    
    // if any discrepancy in handCount, report a problem
    int problemCount;
    
    // test that some known effects on pre state match the effects
    // on post state, such as handCount, deckCount and numActions
    if (
            pre->handCount[p] == post->handCount[p]
        ) { 
        // can't use our typical gamestate test:
        // if (memcmp(pre, post, sizeof(struct gameState)) == 0) {
        // bc we can't predict which cards will be drawn, and
        // we're not in parity with all actual game play
        problemCount = 0;
    } else {
        problemCount = 1;
        if (DEBUG) {
            printf("card count pre: %d\n", pre->handCount[p]);
            printf("card count pos: %d\n\n", post->handCount[p]);
        }
    }
    free(pre);
    return problemCount;
}
