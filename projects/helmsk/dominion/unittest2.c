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
    int numPlayers;
    int seed;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState G;
    
    printf("Testing numHandCards\n");
    
    numPlayers = rand() % 3 + 2;
    seed = rand();
    
    initializeGame(numPlayers, k, seed, &G);
	
	G.whoseTurn = 0;
	int num = numHandCards(&G);
	assert(num == G.handCount[0]);
    assert(num == 5);
	
	G.whoseTurn = 1;
	num = numHandCards(&G);
	assert(num == G.handCount[1]);
    assert(num == 0);
	
	G.whoseTurn = 2;
	num = numHandCards(&G);
	assert(num == G.handCount[2]);
    assert(num == 0);
	
	G.whoseTurn = 3;
	num = numHandCards(&G);
	assert(num == G.handCount[3]);
    assert(num == 0);
    
    G.handCount[3]++;
    num = numHandCards(&G);
    assert(num == G.handCount[3]);
    assert(num == 1);
    
    G.handCount[3] = G.handCount[3] + 10;
    num = numHandCards(&G);
    assert(num == G.handCount[3]);
    assert(num == 11);
    
	checkTest();
	
	return 0;
}
