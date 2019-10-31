#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct player{
	char * name;
  BOARD * location;
	//char * (* toString)(void* S);
}player_t;

typedef player_t * PLAYER;

PLAYER newPlayer(char * name, void * location);
void printPlayer(PLAYER thePlayer, void (*printFunction)(void * A));
