#ifndef _SKIPBOGAME_H
#define _SKIPBOGAME_H

#include <vector>
#include <string>

#include "DrawPile.h"
#include "Pile.h"
#include "Card.h"
#include "Player.h"
#include "FaceUpPile.h"
#include "Hand.h"
//not sure what to include so i just included a bunch of stuff for now

class SkipBoGame{

private:
  int curp;
  int nump;
  int stock;
  FaceUpPile * build[4];
  DrawPile draw;
  
  std::string saveFile;
  std::vector<Player*> peep;

  bool isShuffle;
  bool end;//not sure if this is needed yet, currently im thinking it can be used to decide whether or not the game should end at the time

public:
  
  SkipBoGame(bool isS /*shuffle*/, int pCount, int stk /*stock*/, std::string file);
  //constructor for game given shuffle bool, player count, stock, and file for fresh save
  //probably need to start creating player objects and stuff here

  
  SkipBoGame(bool isS, std::string file);
  //overloaded 2 parameter constructor for loading, only need shuffle and save file

  ~SkipBoGame();
  //destructor, self explanatory

  void displayBuild();//displays the build 
  void playTurn();//will play an entire turn out
  //UPDATE: This will use the current player and communicate with the command line for moves until move has indicated that the player's turn
  //is over then update current player. In the while loop for the function, prompt user for a move (checking if valid move), pass move to play
  //function. This will print the display.

  bool checkWin();//check if a player has won, probably could alter this later, just want to see if stock is emmpy for now though
  //UPDATE: checkWin() altered, all this has to do is return true or false when called, true if there is a winner, boolean updated from false
  //to true when
  //a stock pile is realized as empty

  void save(std::string file);//saves the game to the file
  //UPDATE: save(string file) needs to be implemented
  
  bool play(int p);//will need to take command line arguments, might alter this later to fit better with playTurn
  //UPDATE: Accepts a string that is a move, interprets move, and performs it, this is where it checks if a stock pile is empty
  //(after the move), if a stock pile is empty then change boolean used by checkWin() to true

  std::string getCurrentPlayer() { return ("Player" + std::to_string(curp)); }   //returns the current player's name
  
  std::string toString() const;

  void display() const;

  //above two were provided from starter code so I added them here
};


#endif
