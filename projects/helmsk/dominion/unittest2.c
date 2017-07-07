/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 3, 2017
 * Filename:        unittest2.c
 *
 * Overview:
 * This file tests the function numHandCards().
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testing.h"

int main()
{
    //set up game
    int numPlayers;
    int seed;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState G;
    
    printf("Testing numHandCards\n");
    
    //get valid amount of players and random seed
    numPlayers = rand() % 3 + 2;
    seed = rand();
    
    //initialize game
    initializeGame(numPlayers, k, seed, &G);
	
    //test for 5 cards drawn at start of turn
	G.whoseTurn = 0;
	int num = numHandCards(&G);
	assert(num == G.handCount[0]);
    assert(num == 5);
	
    //test for no cards before first turn
	G.whoseTurn = 1;
	num = numHandCards(&G);
	assert(num == G.handCount[1]);
    assert(num == 0);
	
    //test for no cards before first turn
	G.whoseTurn = 2;
	num = numHandCards(&G);
	assert(num == G.handCount[2]);
    assert(num == 0);
	
    //test for no cards before first turn
	G.whoseTurn = 3;
	num = numHandCards(&G);
	assert(num == G.handCount[3]);
    assert(num == 0);
    
    //test for increased hand count
    G.handCount[3]++;
    num = numHandCards(&G);
    assert(num == G.handCount[3]);
    assert(num == 1);
    
    //test for 10 added cards
    G.handCount[3] = G.handCount[3] + 10;
    num = numHandCards(&G);
    assert(num == G.handCount[3]);
    assert(num == 11);
    
    //check the tests
	checkTest();
	
	return 0;
}
