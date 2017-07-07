/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 3, 2017
 * Filename:        unittest1.c
 *
 * Overview:
 * This file tests the function isGameOver().
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "testing.h"

int main()
{
    //set up game
	int numPlayers;
	int seed;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState G;
    
	printf("Testing isGameOver\n");

    //get valid amount of players and random seed
	numPlayers = rand() % 3 + 2;
	seed = rand();
	
    //initialize game
	initializeGame(numPlayers, k, seed, &G);
	
    //test for in process game
	assert(isGameOver(&G) == 0);
	
    //test for completed game with no provinces
	G.supplyCount[province] = 0;
	assert(isGameOver(&G) == 1);
	
    //test for in process game again
	G.supplyCount[province] = 2;
	assert(isGameOver(&G) == 0);
	
    //test for completed game with 3 empty supply piles
	G.supplyCount[2] = 0;
	G.supplyCount[6] = 0;
	G.supplyCount[20] = 0;
	assert(isGameOver(&G) == 1);
	
    //check the tests
	checkTest();
	
	return 0;
}
