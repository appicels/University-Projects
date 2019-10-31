#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "linkedboard.h"
#include "square.h"


typedef struct player{
	char * name;
  BOARD location;
}player_t;

typedef player_t * PLAYER;

BOARD readFile();
SQUARE makeSquareNode(char buffer[]);
int randomNumber(int upperBound);
char * num_to_color(int c);

PLAYER newPlayer(char * name, BOARD location);
void printPlayer(PLAYER thePlayer, BOARD current, void (*printFunction)(void * A));
void playgame(char * roll1, char * roll2, BOARD head);


int main(int argc, char *argv[])
{

  char * roll1;
	char *roll2;
  BOARD head;
  head = readFile();
  printf("You're Board is: \n");
  displayBoard_forw(head, printSquare);

	roll1 = getColor(head->item);
	roll2 = getColor(head->item);
	playgame(roll1, roll2, head);

}



BOARD readFile(){
  FILE *inf = fopen("board.txt", "r"); //opens a file for READING
  char buffer[80];
  SQUARE S;
  BOARD head, l;
  int count = 0, answer;
  head = NULL;

	if (inf == NULL){
		puts("no file you idiot");
		exit(1);
	}
  while (1) {
    fgets(buffer, 80, inf); //reads in at most 80 char from a line
    if (feof(inf)) //this checks to see if the special EOF was read
      break;     //if so, break out of while and continue with your main

    S = makeSquareNode(buffer);
    count++;
    l = makeNewBoardNode(S);
    head =  insert_rear(head,l);//now you need to insert the square into a node of the generic link list
  }

  fclose(inf);  //Closes a file.
  printf("%d new records were read\n", count);
  return head;
//Hopefully, at this point, the data is nicely stored in the generic link list
}

SQUARE makeSquareNode(char buffer[]){
  SQUARE S;
  char *color, *special, *x; //need these since you read data in as a char string then convert to float or int
  int numx;

  color = (char *) malloc(sizeof(char)*20);
  special = (char *) malloc(sizeof(char)*20);

  color = strtok(buffer, " ");//get first token up to space
  special = strtok(NULL, " ");  //get next token up to space
  x = strtok(NULL, "\n"); //get next token up to \n

  numx = atoi(x);
  S = newSquare(color, special, numx, toString);
  return S;
}

int randomNumber(int upperBound){
//this is the simple rn generator that generates a random number between 1 and upperBound
    int j;
    //srand(time(NULL));
    j=1+(rand() % upperBound);
    return j;
}

char * num_to_color(int c)
{
  char * roll_color;
  if (c == 1)
  {
    roll_color = "RED";
  }
  else if (c == 2)
  {
    roll_color = "BLUE";

  }
  else if ( c == 3)
  {
    roll_color = "ORANGE";
  }
  else
  {
    roll_color = "GREEN";
  }
  return roll_color;
}


PLAYER newPlayer(char * name, BOARD location)
{
  PLAYER p;
  p = (PLAYER) malloc(sizeof(player_t));
  p->name = (char *)malloc(sizeof(char)*20);
  strcpy(p->name,name);
  p->location = location;
  return p;
}


void printPlayer(PLAYER thePlayer, BOARD current, void (*printFunction)(void * A))
{
  printf("%s is on space\n", thePlayer->name);
  printSquare(current->item);
}



void playgame(char * roll1, char * roll2, BOARD head)
{
	int r1, r2;
	PLAYER player1, player2;
	BOARD p1_current, p2_current;

	//initalizing player1 on the board
	p1_current = move_turn(head, roll1, compareColor, printSquare);
	player1 = newPlayer("player1", p1_current);
	printPlayer(player1, p1_current, printSquare);

  p1_current = doSpecial(p1_current, compareSpecial, printSquare, getX);
	player1->location = p1_current;
	printPlayer(player1, p1_current, printSquare);


	//initalizing player2 on the board
	p2_current = move_turn(head, roll2, compareColor, printSquare);
	player2 = newPlayer("player2", p2_current);
	printPlayer(player2, p2_current, printSquare);

	p2_current = doSpecial(p2_current, compareSpecial, printSquare, getX);
	player2->location = p2_current;
	printPlayer(player2, p2_current, printSquare);

	printf("LETS START THE GAME \n");
	printf(" \n");


	while(compareSpecial(p1_current->item, "WIN") != 0 && compareSpecial(p2_current->item, "WIN") != 0)
	{
		//player 1 goes
		r1 = randomNumber(4);
		roll1 = num_to_color(r1);
		printf("Player 1 rolled %s\n", roll1);
		p1_current = move_turn(p1_current->next, roll1, compareColor, printSquare);
		player1->location = p1_current;
		printPlayer(player1, p1_current, printSquare);
		p1_current = doSpecial(p1_current, compareSpecial, printSquare, getX);
		player1->location = p1_current;
		printf("After viewing the special\n");
		printPlayer(player1, p1_current, printSquare);

		printf(" \n");
		//player2 goes
		r2 = randomNumber(4);
    roll2 = num_to_color(r2);
    printf("Player 2 rolled %s\n", roll2);
    p2_current = move_turn(p2_current->next, roll2, compareColor, printSquare);
		player2->location = p2_current;
		printPlayer(player2, p2_current, printSquare);
    p2_current = doSpecial(p2_current, compareSpecial, printSquare, getX);
		player2->location = p2_current;
		printf("After viewing the special\n");
		printPlayer(player2, p2_current, printSquare);
		printf(" \n");

  }

	if(compareSpecial(p1_current->item, "WIN") == 0)
	{
		printf("Congrats Player1 won the game!\n ");
	}
	else if(compareSpecial(p2_current->item, "WIN") == 0)
	{
		printf("Congrats Player2 won the game! \n");
	}
	else
	{
		printf("It's a tie!\n");
	}
}
