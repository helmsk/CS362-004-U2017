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
    int numPlayers;
    int seed;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState G;
    
    printf("Testing Adventurer card\n");
    
    numPlayers = rand() % 3 + 2;
    seed = rand();
    
    initializeGame(numPlayers, k, seed, &G);
    
    G.hand[0][0] = adventurer;
    int handCountBefore = G.handCount[0];
    int deckCountBefore = G.deckCount[0];
    
    int returnValue = playCard(0, 0, 0, 0, &G);
    assert(returnValue == 0);
    
    int handCountAfter = G.handCount[0];
    int deckCountAfter = G.deckCount[0];
    
    assert(G.hand[0][handCountAfter-1] == gold || G.hand[0][handCountAfter-1] == silver || G.hand[0][handCountAfter-1] == copper);
    assert(G.hand[0][handCountAfter-2] == gold || G.hand[0][handCountAfter-2] == silver || G.hand[0][handCountAfter-2] == copper);
    assert(handCountAfter == handCountBefore + 2 - 1);
    assert(deckCountAfter <= deckCountBefore - 2);
    assert(G.hand[0][0] != adventurer);
    
    checkTest();

	return 0;
}
