/*******************
* Greg Doolittle
* CS362 Aburas
* 8/5/2018
* Assignment 4
*
* Description: this file tests the refactored code from assignment 2. Specifically,
* it adds random tests for the village card.
* 
* This was added to the makefile to build this test:
* randomtestcard2: randomtestcard2.c dominion.o rngs.o assert_equal.o
*	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o assert_equal.o $(CFLAGS)
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

int checkVillageCard(int p, struct gameState *post, int handPos);

int main() {

	time_t t;
	srand((unsigned)time(&t));

	//int p, handCount;
	int cards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	struct gameState G;

	printf("TESTING (random test of village card):\n");
	// card should add 1 card and add 2 actions. it has 
    // a bug so it that adds 2 cards, and 1 action
    
    const int NUM_TESTS = 5000;
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
        // call checkVillageCard
        failureCount += checkVillageCard(p, &G, handP);
        i++;
    }
    printf("Testing complete, after %d tests run.\n", NUM_TESTS);
    if (failureCount) {
        printf("Found %d test failures while testing Village.\n", failureCount);
    } else {
        printf("No test failures found while testing Village.\nAll tests pass!\n");
    }
}

int checkVillageCard(int p, struct gameState *post, int handPos) {

    struct gameState *pre;
    pre = (struct gameState*) malloc(sizeof(struct gameState));
    memcpy(pre, post, sizeof(struct gameState));

    int r;

    // we'll call cardEffect, and use village card on 'post' game state
    r = cardEffect(village, 0, 0, 0, post, handPos, 0);
    assert(r == 0);
    
    // we'll manually run village on 'pre' game state
    drawCard(p, pre);
    pre->numActions = pre->numActions + 2;
    discardCard(handPos, p, pre, 0);
    
    // if any discrepancies, report a problem
    int problemCount = 0;
    
    // test that some known effects on pre state match the effects
    // on post state, such as handCount, deckCount and numActions
    if (pre->numActions != post->numActions) { 
        problemCount = problemCount + 1;
    }
    if (pre->handCount[p] != post->handCount[p]) {
        problemCount = problemCount + 1;
    }
    int fail = 0;
    if(problemCount > 0) {
        fail = 1;
    }
    free(pre);
    return fail;
}
