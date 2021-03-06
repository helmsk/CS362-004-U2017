/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 5, 2017
 * Filename:        unittest3.c
 *
 * Overview:
 * This file tests the function supplyCount().
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
    int num;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState G;
    
    printf("Testing supplyCount\n");
    
    //get valid amount of players and random seed
    numPlayers = rand() % 3 + 2;
    seed = rand();
    
    //initialize game
    initializeGame(numPlayers, k, seed, &G);
	
    //test for correct amount of supplies for 2 players
    if (numPlayers == 2)
    {
        num = supplyCount(curse, &G);
        assert(num == 10);
        num = supplyCount(estate, &G);
        assert(num == 8);
        num = supplyCount(duchy, &G);
        assert(num == 8);
        num = supplyCount(province, &G);
        assert(num == 8);
        num = supplyCount(gardens, &G);
        assert(num == 8);
        num = supplyCount(copper, &G);
        assert(num == 46);
    }
    
    //test for correct amount of supplies for 3 players
    if (numPlayers == 3)
    {
        num = supplyCount(curse, &G);
        assert(num == 20);
        num = supplyCount(copper, &G);
        assert(num == 39);
    }
    
    //test for correct amount of supplies for 4 players
    if (numPlayers == 4)
    {
        num = supplyCount(curse, &G);
        assert(num == 30);
        num = supplyCount(copper, &G);
        assert(num == 32);
    }
    
    //test for correct amount of supplies for more than 2 players
    if (numPlayers > 2)
    {
        num = supplyCount(estate, &G);
        assert(num == 12);
        num = supplyCount(duchy, &G);
        assert(num == 12);
        num = supplyCount(province, &G);
        assert(num == 12);
        num = supplyCount(gardens, &G);
        assert(num == 12);
        
    }
    
    //test for correct amount of constant supplies
    num = supplyCount(silver, &G);
    assert(num == 40);
    num = supplyCount(gold, &G);
    assert(num == 30);
    num = supplyCount(adventurer, &G);
    assert(num == 10);
    num = supplyCount(embargo, &G);
    assert(num == 10);
    num = supplyCount(village, &G);
    assert(num == 10);
    num = supplyCount(minion, &G);
    assert(num == 10);
    num = supplyCount(mine, &G);
    assert(num == 10);
    num = supplyCount(cutpurse, &G);
    assert(num == 10);
    num = supplyCount(sea_hag, &G);
    assert(num == 10);
    num = supplyCount(tribute, &G);
    assert(num == 10);
    num = supplyCount(smithy, &G);
    assert(num == 10);
    
    //test for increased supplies
    G.supplyCount[silver]++;
    num = supplyCount(silver, &G);
    assert(num == 41);
    
    //test for 10 added supplies
    G.supplyCount[silver] = G.supplyCount[silver] + 10;
    num = supplyCount(silver, &G);
    assert(num == 51);
    
    //check the tests
    checkTest();
	
	return 0;
}
