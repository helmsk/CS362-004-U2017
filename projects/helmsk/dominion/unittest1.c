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
	int numPlayers;
	int seed;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState G;
    
	printf("Testing isGameOver\n");

	numPlayers = rand() % 3 + 2;
	seed = rand();
	
	initializeGame(numPlayers, k, seed, &G);
	
	assert(isGameOver(&G) == 0);
	
	G.supplyCount[province] = 0;
	assert(isGameOver(&G) == 1);
	
	G.supplyCount[province] = 2;
	assert(isGameOver(&G) == 0);
	
	G.supplyCount[2] = 0;
	G.supplyCount[6] = 0;
	G.supplyCount[20] = 0;
	assert(isGameOver(&G) == 1);
	
	checkTest();
	
	return 0;
}
