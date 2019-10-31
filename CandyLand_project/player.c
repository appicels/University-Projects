#include "player.h"



PLAYER newPlayer(char * name, BOARD * location)
{
  PLAYER p;
  p = (PLAYER) malloc(sizeof(player_t));
  p->name = (char *)malloc(sizeof(char)*20);
  strcpy(p->name,name);
  p->location = location;
  return p;
}


void printPlayer(PLAYER thePlayer, void (*printFunction)(void * A))
{
  printf("%s is on space\n", thePlayer->name);
  printFunction(thePlayer->location->item);
}
