#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_POS 70
#define MAX_STR 32
#define TRUE     1
#define FALSE    0

// Prototype Declarations
int randomInt(int max);
void makeGameArray(char gameArray[]);
void displayGameState(char gameArray[]);
int hareMove(char gameArray[], int hPos);
int tortoiseMove(char gameArray[], int tPos);
int changeTurn(int tTurn);
void runGame(char gameArray[], int hPos, int tPos, int tTurn);

int main(){
  // Seeds random number generator with current system time
  srand(time(NULL));

	// create game array
	char raceTrack[MAX_POS + 1];

	// Track if it's Tortoise's turn, 0 means False, 1 means True
	// By Default Tortoise starts first
	int tTurn = TRUE;

  // Track each players position
  int tPos = 0;
  int hPos = 0;

  // fill gameArray
  makeGameArray(raceTrack);

  // run game
  runGame(raceTrack, tPos, hPos, tTurn);

  return 0;
}


/*
  Function:  randomInt
  Purpose:   returns a random number in the range [0,max)
  Parameters:
    in:      maximum of range
    return:  randomly generated number
*/

int randomInt(int max){
  return(rand() % max);
}

/*
	Function: makeGameArray
	Purpose: Creates an array the with MAX_POS + 1 elements
	Parameters:
		in: Max index in Array
		return: Array of String
*/

void makeGameArray(char gameArray[]){
  int i=0;

  // fill array with blank spaces and starting position of T and H
  for(i=0; i <MAX_POS + 1; i++){
    gameArray[i] = ' ';
  }

  // add T and H position
  gameArray[0] = '*';
}

/*
	Function: displayGameState
	Purpose: Prints a line with the position of the Tortoise and Hare and Start
  and Finish lines. T represents Tortoise position, H represents Hare position
  * represents Tortoise and Hair are in the same position.
	Parameters:
		in: tortoise index, hare index
		return: String representing the game state
*/
void displayGameState(char gameArray[]){
  char line = '|';
  // print starting line
  printf("%c", line);
  // print all elements in gameArray
    printf("%s", gameArray);
  // print finish line
  printf("%c\n", line);

}

/*
	Function: hareMove
	Purpose: changes hare position based off a random move set and moves hare
  character within game array.
	Parameters: game array , index of hare
		in:
		return: if hare has won
*/
int hareMove(char gameArray[], int hPos){
  // determine which move hare will make
  int rand = randomInt(99);
  int distMoved = 0;

  // Big Hop
  if(rand <=19){
    distMoved = 9;
  }
  // Small Hop
  else if (rand >=20 && rand <=49){
    distMoved = 1;
  }
  // Big Slip
  else if (rand >=50 && rand <=59){
    distMoved = -12;
  }
  // Small Slip
  else if (rand >60 && rand <=79){
    distMoved = -2;
  }
  // Sleep
  else if (rand >=80 && rand <=99){
    distMoved = 0;
  }

  // if Hare is not sleeping, move character
  if(distMoved != 0){

    // remove current character representing hare position
    if(gameArray[hPos] == '*'){
      gameArray[hPos] = 'T';
    }
    else{
      gameArray[hPos] = ' ';
    }

    // change hare position
    hPos = hPos + distMoved;

    // make sure hPos is within boundaries
    if(hPos <0){
      hPos = 0;
    }
    else if (hPos>MAX_POS) {
      hPos = MAX_POS;
    }

    // move hare in game array to new position
    if(gameArray[hPos] == 'T'){
      gameArray[hPos] = '*';
    }
    else{
      gameArray[hPos] = 'H';
    }
  }

  return hPos;

}

/*
	Function: tortoiseMove
	Purpose: changes tortoise position based off a random move set and moves
  tortoise character within game array.
	Parameters:
		in: game array, tortoise position
		return:
*/
int tortoiseMove(char gameArray[], int tPos){
  // determine which move tortoise will make
  int rand = randomInt(99);
  int distMoved = 0;

  // Fast Plod
  if(rand <=49){
    distMoved = 3;
  }
  // Slow Plod
  else if (rand >=50 && rand <=79){
    distMoved = 1;
  }
  // Slip
  else{
    distMoved = -6;
  }

  // remove current character representing tortoise position
  if(gameArray[tPos] == '*'){
    gameArray[tPos] = 'H';
  }
  else{
    gameArray[tPos] = ' ';
  }


  // change tortoise position
  tPos = tPos + distMoved;

  // make sure tPos is within boundaries
  if(tPos <0){
    tPos = 0;
  }
  else if (tPos>MAX_POS) {
    tPos = MAX_POS;
  }

  // move tortoise in game array to new position
  if(gameArray[tPos] == 'H'){
    gameArray[tPos] = '*';
  }
  else{
    gameArray[tPos] = 'T';
  }

  return tPos;

}

/*
	Function: changeTurn
	Purpose: change who moves next
	Parameters:
		in: int representing if it is or isn't the tortoise's turn
		return: if it Tortoise's Turn is TRUE or FALSE
*/
int changeTurn(int tTurn){
  if(tTurn == FALSE){
    tTurn = TRUE;
  }
  else{
    tTurn = FALSE;
  }

  return tTurn;
}

/*
	Function: runGame
	Purpose: Find out who wins the race
	Parameters:
		in: game Array, Hare starting position, Tortoise starting position, if it
    is or isn't the Tortoise's turn
		return:
*/

void runGame(char gameArray[], int hPos, int tPos, int tTurn){
  // Track if either player has won
  int tWon;
  int hWon;

  tWon = FALSE;
  hWon = FALSE;
	// show opening board state
	displayGameState(gameArray);

  // T or H make one move, print board state, repeat until winner is found
  while (tWon == FALSE && hWon == FALSE) {
     // move player based on who's turn it is
      if(tTurn == TRUE){
        tPos = tortoiseMove(gameArray, tPos);
        displayGameState(gameArray);

      }
      else{
        hPos = hareMove(gameArray, hPos);
        displayGameState(gameArray);


      }

      tTurn = changeTurn(tTurn);


      // check if a player has won
      if(tPos == MAX_POS){
        tWon = TRUE;
      }
      if(hPos == MAX_POS){
        hWon = TRUE;
      }


    // return winner's name
    if(tWon == TRUE){
      printf("Winner is Timmy !!!");
    }
    if (hWon == TRUE){
      printf("Winner is Harold !!!");
    }
   }

}
