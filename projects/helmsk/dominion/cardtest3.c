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
    //set up game
    int numPlayers;
    int seed;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState G;
    
    printf("Testing Smithy card\n");
    
    //get valid amount of players and random seed
    numPlayers = rand() % 3 + 2;
    seed = rand();
    
    //initialize game
    initializeGame(numPlayers, k, seed, &G);
	
    //give player smithy
	G.hand[0][0] = smithy;
	int handCountBefore = G.handCount[0];
	int actionCountBefore = G.numActions;
	
    //play smithy
	int returnValue = playCard(0, 0, 0, 0, &G);
	assert(returnValue == 0);
	
    //see results
	int handCountAfter = G.handCount[0];
	int actionCountAfter = G.numActions;

    //test for correct hand count (+3 drawn, -1 discard smithy)
	assert(handCountAfter == (handCountBefore + 3 - 1));
    
    //test for correct action count
	assert(actionCountAfter == (actionCountBefore - 1));
    
    //test for discarding played card
    assert(G.hand[0][0] != smithy);
	
    //check the tests
	checkTest();
	
	return 0;
}
