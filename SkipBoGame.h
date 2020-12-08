#ifndef _SKIPBOGAME_H
#define _SKIPBOGAME_H

#include <vector>
#include <string>

#include "DrawPile.h"
#include "Pile.h"
#include "Card.h"
#include "Player.h"
//not sure what to include so i just included a bunch of stuff for now

class SkipBoGame{

private:
  int curp;
  int nump;
  int stock;
  Pile build[4];
  DrawPile draw;
  
  std::string saveFile;
  std::vector<Player*> peep;

  bool isShuffle;
  bool end;//not sure if this is needed yet, currently im thinking it can be used to decide whether or not the game should end at the time

public:
  
  SkipBoGame(bool isS /*shuffle*/, int pCount, int stk /*stock*/; string file);
  //constructor for game given shuffle bool, player count, stock, and file for fresh save
  //probably need to start creating player objects and stuff here

  
  SkipBoGame(bool isS, string file);
  //overloaded 2 parameter constructor for loading, only need shuffle and save file

  ~SkipBoGame();
  //destructor, self explanatory

  void playTurn();//will play an entire turn out

  void checkWin(Player* p);//check if a player has won, probably could alter this later, just want to see if stock is empty for now though

  void save(string file);//saves the game to the file

  void play();//will need to take command line arguments, might alter this later to fit better with playTurn

  string getCurrentPlayer() { return ("Player" + curp); }   //returns the current player's name
  
  string toString() const;

  void display() const;

  //above two were provided from starter code so I added them here
};


#endif
