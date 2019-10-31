#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "linkedboard.h"
#include "square.h"


BOARD readFile();
SQUARE makeSquareNode(char buffer[]);
int randomNumber(int upperBound);
char * num_to_color(int c);
int playgame(char * roll, BOARD head);



int main(int argc, char *argv[])
{
  char * roll;
  int game1, game2, game3, game4, game5, avg_turns;
  BOARD head, current;
  head = readFile();
  printf("You're Board is: \n");
  displayBoard_forw(head, printSquare);
  roll = getColor(head->item);
  game1 = playgame(roll, head);
  game2 = playgame(roll, head);
  game3 = playgame(roll, head);
  game4 = playgame(roll, head);
  game5 = playgame(roll, head);
  avg_turns = (game1+game2+game3+game4+game5)/5;
  printf("It took an average of %d turns to win the game\n", avg_turns);

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


int playgame(char * roll, BOARD head)
{
  int r;
  int num_turns = 0;
  BOARD current;
  current = move_turn(head, roll, compareColor, printSquare);
  current = doSpecial(current, compareSpecial, printSquare, getX);
  printf("Lets begin the game \n");


  while(compareSpecial(current->item, "WIN") != 0)
  {

    r = randomNumber(4);
    roll = num_to_color(r);
    printf("You rolled %s\n", roll);
    current = move_turn(current->next, roll, compareColor, printSquare);
    printf("Your current space is \n");
    printSquare(current->item);
    current = doSpecial(current, compareSpecial, printSquare, getX);
    printf("After checking the special, your current space is\n");
    printSquare(current->item);
    num_turns++;
    printf("You have gone %d times \n", num_turns);
    printf(" \n");
  }
  printf("Congrats you won the game! It took a total of %d turns\n", num_turns);
  return num_turns;
}
