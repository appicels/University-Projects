#include "square.h"

SQUARE newSquare(char* color, char * special, int x, char * (* toString)(void* S))
{
  SQUARE s;
  s = (SQUARE) malloc(sizeof(square_t));
  s->color = (char *) malloc(sizeof(char)*20);
  s->special = (char *)malloc(sizeof(char)*20);
  strcpy(s->color,color);
  strcpy(s->special, special);
  s->x = x;
  s->toString = toString;
//  s->getX = getX;
  return s;
}

void printSquare(void * S)
{
  SQUARE s;
  s = (SQUARE) S;
  puts(s->toString(s));
}

int compareColor(void * A, void * B){
  SQUARE s1;
  char * item;
  item  = (char *) B;
  s1 = (SQUARE) A;
  return (strcmp(item,s1->color));
}

int compareSpecial(void * A, void * B)
{
  SQUARE s1;
  char * item;
  item  = (char *) B;
  s1 = (SQUARE) A;
  return (strcmp(item,s1->special));
}


char * toString (void* S)
{
  char * buffer;
  SQUARE s;
  s = (SQUARE) S;
	buffer = (char *) malloc(sizeof(char)*200);
	sprintf(buffer, " %s %s %d\n", s->color, s->special, s->x);
  return buffer;
}

int getX(void * S)
{
  SQUARE s;
  s = (SQUARE)S;
  return s->x;
}

char * getColor(void * S)
{
  SQUARE s;
  s = (SQUARE)S;
  return s->color;
}
