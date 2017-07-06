/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 6, 2017
 * Filename:        cardtest3.c
 *
 * Overview:
 * This file tests the card Smithy.
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "testing.h"

int main (int argc, char** argv)
{
    int numPlayers;
    int seed;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState G;
    
    printf("Testing Smithy card\n");
    
    numPlayers = rand() % 3 + 2;
    seed = rand();
    
    initializeGame(numPlayers, k, seed, &G);
	
	G.hand[0][0] = smithy;
	int handCountBefore = G.handCount[0];
	int actionCountBefore = G.numActions;
	
	int returnValue = playCard(0, 0, 0, 0, &G);
	assert(returnValue == 0);
	
	int handCountAfter = G.handCount[0];
	int actionCountAfter = G.numActions;

	assert(handCountAfter == (handCountBefore + 3 - 1));
	assert(actionCountAfter == (actionCountBefore - 1));
    assert(G.hand[0][0] != smithy);
	
	checkTest();
	
	return 0;
}
