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
  deck = new Pile();

  
  ifstream deck0("deck0.txt");
  Pile tempDeck = new Pile();
  tempDeck.readIn(deck0);
  deck = new drawPile(tempDeck);
  
  //need to make 4 piles for the build pile
  for (int i = 0; i < 4; i ++){
    Pile* p = new Pile();
    builds[i] = p;
  }
  
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
    Pile sPile = new Pile();
    Pile dPile[4];
    Hand hPile = new Hand();
    //not properly constructed yet, Hand needs to be written
    
    for (int i2 = 0; i2 < 4; i2 ++){
      Pile p = new Pile();
      dPile[i] = p;
    }
    
    Player* p = new Player(name, sPile, dPile, hPile);

    players.push_back(p);
  }
  string saveFile = file;
}

SkipBoGame::SkipBoGame(bool isS, string file){
  isShuffle = isS;

  end = false;
  
  ifstream save(file);

  string trash;
  save >> trash;//dont care about this boolean, we want the one from the command line argument

  save >> playerCount;
  save >> turn;

  string tempString = "a";
  save >> tempString;

  for (int i = 0; i < playerCount; i ++){
    string playerName;
    save >> playerName;
    
    save >> tempString; //should get rid of word "stock"
    int stockSize;
    save >> stockSize;
    Pile sp = new Pile;
    for (int i2 = 0; i2 < stockSize; i2 ++){
      int cardNum;
      save >> cardNum;
      Card c = new Card(cardNum);
      sp.push_back(c);
    }

    save >> tempString; //gets rid of "Hand"
    if (tempString != "Hand"){
      //use this for error checking right now, if the code reaches here then we have an issue
    }

    int handSize;
    save >> handSize;
    Hand h = new Hand();
    for (int i3 = 0; i3 < handSize; i3++){
      int cardNum;
      save >> cardNum;
      Card c = new Card(cardNum);
      h.push_back(c);//not sure how hand works yet, just using this as filler
    }

    Pile disPiles[4];
    for (int d = 0; d < 4; d++){
      Pile dp;
      save >> tempString;//should be discard Pile 0 1 2 3
      int dSize;
      save >> dSize;
      for (int i4 = 0; i4 < dSize; i4++){
	int cardNum;
	save >> cardNum;
	Card c = new Card(cardNum);
	dp.push_back(c);
      }
      disPiles[i] = dp;
    }

    Player* p = new Player(playerName, sp, disPiles, h);
    players.push_back(p);
  }
  
  save >> tempString;
  int deckSize;
  save >> deckSize;
  Pile deckPile;
  for (int i5 = 0; i5 < deckSizel i5++){
    int cardNum;
    save >> cardNum;
    Card c = new Card(cardNum);
    deckPile.push_back(c);
  }
  deck = new DrawPile(deckPile);

  for (int i6 = 0; i6 < 4; i6 ++){
    save >> tempString;
    int buildSize;
    save >> buildSize;
    Pile b;
    for (int i7 = 0; i7 < buildSize; i7 ++){
      int cardNum;
      save >> cardNum;
      Card c = new Card(cardNum);
      b.push_back(c);
      
    }
    builds[i] = b;
  }
  
  
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


