
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct square{
	char * color;    // the color of the space. either red, blue, orange or green;
	char * special;  // the special space. There are four values for special spaces: GOBACK, GOFORWARD
                 // WIN and NONE (i.e. nothing special)
	int x;           // if you land on a special space, this is how many spaces to move.
                 //If you land on WIN, the game is over and you win.
	char * (* toString)(void* S);
}square_t;

typedef square_t * SQUARE;

SQUARE newSquare(char* color, char * special, int x, char * (* toString)(void* S));

void printSquare(void * S);
int compareColor(void * A, void * B);
int compareSpecial(void * A, void * B);
char * toString(void* S);
int getX(void * S);
char * getColor(void * S);
