#include <iostream>
#include <sstream>
#include "SkipBoGame.h"

#include <string>
#include <vector>
#include "DrawPile.h"
#include "Pile.h"
#include "Card.h"
#include "Player.h"

/* for live game play - must not change format!

drawPile  build_a  build_b  build_c  build_d
playerName  stock_0  
discards: discard_1 discard_2 discard_3 discard_4
hand: card_5 card_6 card_7 card_8 card_9
 */
void SkipBoGame::display() const {
  std::cout << "Draw: ";
  draw.display();
  std::cout << "  Build Piles: ";
  for (int j = 0; j < 4; j++) {
    build[j].display();
    std::cout << " ";
  }
  std::cout << std::endl;
  peep[curp].display();
}

/* for saving state - must not change format!

shuffle numplayers currplayer
PlayerCurp [display]
PlayerCurp+1 [display]
[etc for all players]
Draw [display]
Build_a [display]
Build_b [display]
Build_c [display]
Build_d [display]
*/
std::string SkipBoGame::toString() const {
  std::stringstream result;
  int idx;
  result << draw.getRand() << " " << nump << " " << curp << "\n";
  for (int i = 0; i < nump; ++i) {
    idx = (curp+i) % nump;
    result << peep[idx].toString();
  }
  result << "Draw " << draw.toString(); 
  for (int j = 0; j < 4; j++) {
    result << "Build_" << char('a'+j) << " ";
    result << build[j].toString();  
  }
  return result.str();
}

SkipBoGame::SkipBoGame(bool isS, int pCount, int stk, string file){
  turn = 0;
  playerCount = pCount;
  stock = stk;
  isShuffle = isS;
  end = false;

  //need to make 4 piles for the build pile

  //need to generate deck, and draw cards for everyone, taking those cards out of the deck
  for (int i = 0; i < pCount; i ++){
    //generate players
    String n = "player";
    name = n + std::to_string(i);//gives us player0, player1, and so on


    /* need to create piles here
       stock pile
       4 discard piles as an array
       hand pile
    */
    Player* p = new Player(name, sPile, dPile, hPile);

    players.push_back(p);
  }
  string saveFile = file;
}

SkipBoGame::SkipBoGame(bool isS, string file){
  isShuffle = isS;

  //open a stream with file, and assign private variables there
}

SkipBoGame::~SkipBoGame(){
  for (int i = 0; i < players.size(); i ++){
    delete players.at(i);
  }
}

void SkipBoGame::playTurn(){
}

void SkipBoGame::checkWin(Player* p){
}

void SkipBoGame::play(){
}


