#include <stdio.h> // printf, puts
#include <stdlib.h> // rand
#include "testing.h" // assert
#include "dominion.h" // dominion

#define MAX_TESTS 12

int main() {
	printf("Testing Village card with random test...");
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	int players, seed;
	struct gameState G;
	
	int i, player;

	for (i = 0; i < MAX_TESTS; i++) {
		
		/* Randomize game */
		// pick random number of players between 2 - MAX_PLAYERS
		players = (rand() % MAX_PLAYERS-1) + 2;
		// pick random game seed
		seed = rand();
		// Initialize gameState
		initializeGame(players, k, seed, &G);
		
		for (player = 0; player < players; player++) {
			// Initiate valid state variables
			// Pick random deck size out of MAX_DECK size
			G.discardCount[player] = rand() % MAX_DECK;
			G.handCount[player] = rand() % MAX_HAND;
			G.deckCount[player] = rand() % MAX_DECK;
			// 1 in 3 chance of making empty deck for coverage
			if (seed % 3 == 0)
				G.deckCount[player] = 0;
			
			// Store number of treasure in hand before
			int handCountBefore =  G.handCount[player];
			int numberOfActionsBefore = G.numActions;
			
			/* Run adventurer card */
			G.hand[player][0] = village;
			int returnValue = playCard(0, 0, 0, 0, &G);
			assert(returnValue == 0);
			
			int handCountAfter =  G.handCount[player];
			int numberOfActionsAfter = G.numActions;
			
			assert(handCountAfter == handCountBefore);
			assert(numberOfActionsAfter == (numberOfActionsBefore + 2 - 1));
			
			endTurn(&G);
		}
	}
	
	checkTest();
	
	return 0;
}
