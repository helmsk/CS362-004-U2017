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
    //set up game
    int numPlayers;
    int seed;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState G;
    
    printf("Testing Gardens card\n");
    
    //get valid amount of players and random seed
    numPlayers = rand() % 3 + 2;
    seed = rand();
    
    //initialize game
    initializeGame(numPlayers, k, seed, &G);
	
    //give player gardens
	G.hand[0][0] = gardens;
	int handCountBefore = G.handCount[0];
    int scoreBefore = scoreFor(0, &G);
	
    //play gardens
	int returnValue = playCard(0, 0, 0, 0, &G);
	assert(returnValue == 0);
	
    //see results
	int handCountAfter = G.handCount[0];
    int scoreAfter = scoreFor(0, &G);

    //test for correct hand count (-1 discard gardens)
	assert(handCountAfter == (handCountBefore - 1));
    
    //test for correct score (+1 for every 10 in deck)
    assert(scoreAfter == (scoreBefore + (fullDeckCount(0, 0, &G) / 10)));
    
    //test for discarding played card
    assert(G.hand[0][0] != gardens);
	
    //check the tests
	checkTest();
	
	return 0;
}
