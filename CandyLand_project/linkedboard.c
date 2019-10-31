#include "linkedboard.h"
#include <assert.h>

BOARD makeNewBoardNode(void * item){
  BOARD p;
  p = (BOARD) malloc(sizeof(node_t));
  p->item = item;
  p->next = NULL;
  p->prev = NULL;
  return p;
}


BOARD insert_rear(BOARD head,BOARD m){
  BOARD p;
  if (head==NULL)
    return m;
  p=head;
  //now move to the rear of the BOARD
  while(p->next != NULL){
    p=p->next;
  }
  p->next = m;
  m->prev = p;
  return head;
}

void displayBoard_forw(BOARD head, void (*printFunction)(void * A)){
  BOARD temp;
  int cnt=0;
  temp = head;
  if (temp==NULL){
    puts("NO LINKED BOARD");
    return;
  }
  printf("node values are:\n");
  while (temp != NULL){
    printFunction(temp->item);
    temp=temp->next;
    cnt++;
  }
  printf("%d students were found\n",cnt);
}

void displayBoard_back(BOARD head, void (*printFunction)(void * A)){
  BOARD temp;
  int cnt=0;
  temp = head;
  if (temp==NULL){
    puts("NO LINKED BOARD");
    return;
  }
  while(temp->next != NULL)
  {
    temp = temp->next;
  }
  printf("node values are:\n");
  while (temp != NULL){
    printFunction(temp->item);
    temp=temp->prev;
    cnt++;
  }
  printf("%d students were found\n",cnt);
}


void display_value(BOARD head, void * itemToBeRemoved, void (*printFunction)(void * A),  int (*compare)(void * A, void * B)){
  BOARD temp;
  temp = head;
  if (temp == NULL){
    puts("There is no BOARD");
    return;
  }
  while(temp != NULL)
  {
    if(compare(temp->item, itemToBeRemoved) == 0)
    {
      printf("The Node is\n");
      printFunction(temp->item);
      return;
    }
    if(temp->next == NULL)
    {
      //name not found, return original BOARD
      printf("There was no match found\n");
      return;
    }
    if(compare(temp->item,itemToBeRemoved) != 0)
    {
      temp = temp->next;
    }
  }
}


BOARD move_forward_x(BOARD current, int x )
{
  BOARD temp;
  temp = current;
  int i;

  for(i = 1; i < x-1; i++)
  {
    //goes one less space than needed
    //then gets out of loop to make sure the next space isn't off the BOARD
    temp = temp->next;
  }
  if(temp->next != NULL)
  {
    temp = temp->next;

  }
  else
  {
    printf("Stay where you are, there are not enough spaces to move forward\n");
    for(i = 1; i< x-1; i++)
    {
      temp = temp->prev;
    }
  }
  printf("\n");
  return temp;
}


BOARD move_back_x(BOARD current, int x)
{
  BOARD temp;
  temp = current;
  int i;
  for(i = 1; i < x; i++)
  {
    //goes one less space than needed
    //then gets out of loop to make sure the next space isn't off the BOARD
    temp = temp->prev;
  }
  if(temp->prev != NULL)
  {
    temp = temp->prev;
  }

  else
  {
    printf("You are now at the beginning of the board\n");
  }

  return temp;
}

BOARD move_turn(BOARD current, char * roll_color, int (*compareColorFunction)(void * A, void * B), void (*printFunction)(void * A))
{

  BOARD temp;
  int count;
  count = 0;
  int i;
  int id = 0;
  temp = current;
  while(compareColorFunction(temp->item, roll_color) != 0)
  {
    if(temp->next == NULL)
    {
      id = 1;
      break;
    }
    temp = temp->next;
    count++;
  }
  if(id == 1)
  {
    printf("Stay where you are, there are not enough spaces\n");
    for(i = 0 ; i <= count; i++)
    {
      temp = temp->prev;

    }
  }
//  printFunction(temp->item);
  printf("\n");

  return temp;
}

BOARD doSpecial(BOARD current, int (*compareSpecialFunction)(void * A, void * B), void (*printFunction)(void * A), int (*getXFunction)(void * X))
{
  BOARD temp;
  temp = current;
  //printFunction(current->item);
  if(compareSpecialFunction(temp->item, "NONE") == 0 || compareSpecialFunction(temp->item, "WIN") == 0)
  {
  //  printf("Case 1\n");
    //printFunction(temp->item);
    return temp;
  }
  else if (compareSpecialFunction(temp->item, "GOFORWARD") == 0)
  {
  //  printf("Case 2\n");
    printf("Yay you get to move foward more!\n");
    int x;
    x = getXFunction(temp->item);
    temp = move_forward_x(temp, x);
  //  printFunction(temp->item);
    return temp;
  }
  else
  {
  //  printf("Case 3\n");
  printf("Sorry you have to move back :( \n");
    int x;
    x = getXFunction(temp->item);
    temp = move_back_x(temp, x);
  //  printFunction(temp->item);
    return temp;
  }
}
