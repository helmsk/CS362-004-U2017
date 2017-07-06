/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 6, 2017
 * Filename:        cardtest2.c
 *
 * Overview:
 * This file tests the card Gardens.
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
    
    printf("Testing Gardens card\n");
    
    numPlayers = rand() % 3 + 2;
    seed = rand();
    
    initializeGame(numPlayers, k, seed, &G);
	
	G.hand[0][0] = gardens;
	int handCountBefore = G.handCount[0];
    int scoreBefore = scoreFor(0, &G);
	
	int returnValue = playCard(0, 0, 0, 0, &G);
	assert(returnValue == 0);
	
	int handCountAfter = G.handCount[0];
    int scoreAfter = scoreFor(0, &G);

	assert(handCountAfter == (handCountBefore - 1));
    assert(scoreAfter == (scoreBefore + (fullDeckCount(0, 0, &G) / 10)));
    assert(G.hand[0][0] != gardens);
	
	checkTest();
	
	return 0;
}
