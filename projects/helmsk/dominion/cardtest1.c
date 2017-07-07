/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 6, 2017
 * Filename:        cardtest1.c
 *
 * Overview:
 * This file tests the card Adventurer.
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "testing.h"

int main ()
{
    //set up game
    int numPlayers;
    int seed;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState G;
    
    printf("Testing Adventurer card\n");
    
    //get valid amount of players and random seed
    numPlayers = rand() % 3 + 2;
    seed = rand();
    
    //initialize game
    initializeGame(numPlayers, k, seed, &G);
    
    //give player adventurer
    G.hand[0][0] = adventurer;
    int handCountBefore = G.handCount[0];
    int deckCountBefore = G.deckCount[0];
    
    //play adventurer
    int returnValue = playCard(0, 0, 0, 0, &G);
    assert(returnValue == 0);
    
    //see results
    int handCountAfter = G.handCount[0];
    int deckCountAfter = G.deckCount[0];
    
    //test for two drawn treasure cards
    assert(G.hand[0][handCountAfter-1] == gold || G.hand[0][handCountAfter-1] == silver || G.hand[0][handCountAfter-1] == copper);
    assert(G.hand[0][handCountAfter-2] == gold || G.hand[0][handCountAfter-2] == silver || G.hand[0][handCountAfter-2] == copper);
    
    //test for correct hand count (+2 treasure, -1 discard adventurer)
    assert(handCountAfter == handCountBefore + 2 - 1);
    
    //test for correct deck count (-2 treasure)
    assert(deckCountAfter <= deckCountBefore - 2);
    
    //test for discarding played card
    assert(G.hand[0][0] != adventurer);
    
    //check the tests
    checkTest();

	return 0;
}
