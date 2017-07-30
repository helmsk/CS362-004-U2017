/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 24, 2017
 * Filename:        randomtestcard1.c
 *
 * Overview:
 * This file randomly tests the card Village.
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>
#include "testing.h"
#include "dominion.h"
#include "dominion_helpers.h"

#define MAX_TESTS 2000

void ignoreINT(int signo) {
    fprintf(stderr, "A signal was triggered: %d\n", signo);
}

int main()
{
    /* set up structure to specify new action */
    struct sigaction new_action;
    // signal handler ignoreINT prints newline character
    new_action.sa_handler = ignoreINT;
    // fill sa_mask with all signal types
    sigfillset(&(new_action.sa_mask));
    // set no flags
    new_action.sa_flags = 0;
    
    // Set sigaction to respond to SIGABRT, SIGTERM, SIGSEGV
    sigaction(SIGABRT, &new_action, NULL);
    sigaction(SIGTERM, &new_action, NULL);
    sigaction(SIGSEGV, &new_action, NULL);
    
    //set up game
    int numPlayers, currentPlayer;
    int seed;
    int i, j, test;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState G, pre;
    
    printf("Testing Great Hall card\n");
	
    for (test = 0; test < MAX_TESTS; test++)
    {
        //get valid amount of players and random seed
        numPlayers = rand() % 3 + 2;
        seed = rand();
        
        //initialize game
        initializeGame(numPlayers, k, seed, &G);
        
        //test every player
        for (currentPlayer = 0; currentPlayer < numPlayers; currentPlayer++)
        {
            //pick random deck size out of MAX_DECK size
            G.whoseTurn = currentPlayer;
            G.discardCount[currentPlayer] = rand() % MAX_DECK;
            G.handCount[currentPlayer] = (rand() % MAX_HAND) - G.discardCount[currentPlayer];
            G.deckCount[currentPlayer] = (rand() % MAX_DECK) - G.discardCount[currentPlayer] - G.handCount[currentPlayer];
            
            //1 in 3 chance of making empty deck for coverage
            if (seed % 3 == 0)
                G.deckCount[currentPlayer] = 0;
            
            //give player village card
            G.hand[currentPlayer][0] = great_hall;
            
            //copy to pre gamestate
            memcpy(&pre, &G, sizeof(struct gameState));
            
            //play village card
            int returnValue = cardEffect(great_hall, 0, 0, 0, &G, 0, 0);
            assert(returnValue == 0);
            
            //test for correct hand count (+1 drawn, -1 discard played card)
            assert(G.handCount[currentPlayer] == pre.handCount[currentPlayer]);
            
            //test for correct action count (+1 action)
            assert(G.numActions == (pre.numActions + 1));
            
            //test for correct deck count
            assert(G.deckCount[currentPlayer] == (pre.deckCount[currentPlayer] - 1));
            
            //test for playing 1 card
            assert(G.playedCardCount == (pre.playedCardCount + 1));
            
            //test for discarding played card
            assert(G.hand[currentPlayer][0] != great_hall);
            
            //test for state changes to other players
            for (i = 0; i < numPlayers; i++)
            {
                if (i != currentPlayer)
                {
                    assert(G.handCount[i] == pre.handCount[i]);
                    assert(G.deckCount[i] == pre.deckCount[i]);
                    assert(G.discardCount[i] == pre.discardCount[i]);
                    
                    for (j = 0; j < G.handCount[i]; j++)
                    {
                        assert(G.hand[i][j] == pre.hand[i][j]);
                    }
                    
                    for (j = 0; j < G.deckCount[i]; j++)
                    {
                        assert(G.deck[i][j] == pre.deck[i][j]);
                        assert(G.discard[i][j] == pre.discard[i][j]);
                    }
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
        }
    }
    
    checkTest();
    
    return 0;
}
