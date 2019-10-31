#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct node{
  void * item;
  struct node *next;
  struct node *prev;
}node_t;

typedef node_t * BOARD;


BOARD makeNewBoardNode(void * item);
BOARD insert_rear( BOARD head, BOARD m);
void displayBoard_forw( BOARD m, void (*printFunction)(void * A));
void displayBoard_back( BOARD m, void(*printFunction)(void * A));
void display_value( BOARD head, void * itemToBeRemoved, void (*printFunction)(void * A),  int (*compare)(void * A, void * B));
// deleteIt( head, void * itemToBeRemoved, int (*compare)(void * A, void * B));
BOARD move_forward_x(BOARD current, int x);
BOARD move_back_x(BOARD current, int x);
BOARD move_turn(BOARD current, char * roll_color, int (*compareColorFunctionFunction)(void * A, void * B), void (*printFunction)(void * A));
BOARD doSpecial(BOARD current, int (*compareSpecialFunction)(void * A, void * B), void (*printFunction)(void * A), int (*getXFunction)(void * X));
