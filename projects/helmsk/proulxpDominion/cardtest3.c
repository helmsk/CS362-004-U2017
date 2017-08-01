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
    int i, j;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState G, pre;
    
    printf("Testing Smithy card\n");
    
    //get valid amount of players and random seed
    numPlayers = rand() % 3 + 2;
    seed = rand();
    
    //initialize game
    initializeGame(numPlayers, k, seed, &G);
	
    //give player smithy
	G.hand[0][0] = smithy;
    
    //copy to pre gamestate
    memcpy(&pre, &G, sizeof(struct gameState));
	
    //play smithy
	int returnValue = playCard(0, 0, 0, 0, &G);
	assert(returnValue == 0);

    //test for correct hand count (+3 drawn, -1 discard smithy)
	assert(G.handCount[0] == (pre.handCount[0] + 3 - 1));
    
    //test for correct action count
	assert(G.numActions == (pre.numActions - 1));
    
    //test for discarding played card
    assert(G.hand[0][0] != smithy);
    
    //test for state changes to other players
    for (i = 1; i < numPlayers; i++)
    {
        assert(G.handCount[i] == pre.handCount[i]);
        assert(G.deckCount[i] == pre.deckCount[i]);
        assert(G.discardCount[i] == pre.discardCount[i]);
        
        for (j = 0; j < G.handCount[i]; j++)
            assert(G.hand[i][j] == pre.hand[i][j]);
        
        for (j = 0; j < G.deckCount[i]; j++)
        {
            assert(G.deck[i][j] == pre.deck[i][j]);
            assert(G.discard[i][j] == pre.discard[i][j]);
        }
    }
    
    //test for state changes to kingdom and victory piles
    assert(supplyCount(estate, &G) == supplyCount(estate, &pre));
    assert(supplyCount(duchy, &G) == supplyCount(duchy, &pre));
    assert(supplyCount(province, &G) == supplyCount(province, &pre));
    
    for (i = 0; i < 10; i++)
    {
        assert(supplyCount(k[i], &G) == supplyCount(k[i], &pre));
    }
	
    //check the tests
	checkTest();
	
	return 0;
}
