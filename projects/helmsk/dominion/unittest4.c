/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 5, 2017
 * Filename:        unittest4.c
 *
 * Overview:
 * This file tests the function updateCoins().
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "testing.h"

int main()
{
    int numPlayers;
    int seed;
    int i;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState G;
    
    printf("Testing updateCoins\n");
    
    numPlayers = rand() % 3 + 2;
    seed = rand();
    
    initializeGame(numPlayers, k, seed, &G);
    
    for (i = 0; i < G.handCount[0]; i++)
    {
        G.hand[0][i] = copper;
    }
    updateCoins(0, &G, 0);
    assert(G.coins == G.handCount[0]);
    
    for (i = 0; i < G.handCount[0]; i++)
    {
        G.hand[0][i] = copper;
    }
    updateCoins(0, &G, 2);
    assert(G.coins == G.handCount[0] + 2);
    
    for (i = 0; i < G.handCount[0]; i++)
    {
        G.hand[0][i] = silver;
    }
    updateCoins(0, &G, 0);
    assert(G.coins == G.handCount[0] * 2);
    
    for (i = 0; i < G.handCount[0]; i++)
    {
        G.hand[0][i] = gold;
    }
    updateCoins(0, &G, 0);
    assert(G.coins == G.handCount[0] * 3);
    
    for (i = 0; i < G.handCount[0]; i++)
    {
        G.hand[0][i] = gold;
    }
    updateCoins(0, &G, 10);
    assert(G.coins == G.handCount[0] * 3 + 10);
    
    checkTest();
    
    return 0;
}
