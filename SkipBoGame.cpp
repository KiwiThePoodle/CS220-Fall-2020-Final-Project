#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
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
    build[j]->display();
    std::cout << " ";
  }
  std::cout << std::endl;
  peep[curp]->display();
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
    result << peep[idx]->toString();
  }
  result << "Draw " << draw.toString(); 
  for (int j = 0; j < 4; j++) {
    result << "Build" << char('a'+j) << " ";
    result << build[j]->toString();  
  }
  return result.str();
}

SkipBoGame::SkipBoGame(bool isS, int pCount, int stk, std::string file) {
  if(isS) {    //if shuffle is on, random first player
    curp = rand() % pCount;
  }
  else {   //else first player is 0
    curp = 0;
  }
  nump = pCount;
  stock = stk;
  isShuffle = isS;
  end = false;
  draw = new DrawPile();

  
  std::ifstream deck0("deck0.txt");
  DrawPile tempDeck = new DrawPile();
  tempDeck.readIn(deck0);
  draw = new DrawPile(tempDeck);
  draw.setRand(isShuffle);
	
  if(isS) {   //if shuffle is on, shuffle the draw pile
    draw.shuffle();
  }
  
  //need to make 4 piles for the build pile
  for (int i = 0; i < 4; i ++){
    FaceUpPile* p = new FaceUpPile();
    build[i] = p;
  }
  
	
  //need to generate deck, and draw cards for everyone, taking those cards out of the deck
  for (int i = 0; i < pCount; i ++){
    //generate players
    std::string n = "Player";
    std::string name = n + std::to_string(i);//gives us player0, player1, and so on
    
    Player* p = new Player(name);

    peep.push_back(p);
  }
  
  

  FaceUpPile[] stocks = new FaceUpPile[nump];
  for(int i = 0; i < stock; i++) {
    for(int j = 0; j < nump; j++) {
      stocks[j].addCard(draw.topCard());
    }
  }

  int index = curp;
  for(int i = 0; i < nump; i++) {
    peep[index].setStockPile(stocks[i]);
    index = (index + 1) % nump;
  }
  
  std::string saveFile = file;
}

SkipBoGame::SkipBoGame(bool isS, std::string file){
  isShuffle = isS;

  end = false;
  
  std::ifstream save(file);

  std::string trash;
  save >> trash;//dont care about this boolean, we want the one from the command line argument

  save >> nump;
  save >> curp;

  std::string tempString = "a";
  save >> tempString;

  for (int i = 0; i < nump; i ++){
    std::string playerName;
    save >> playerName;
    
    save >> tempString; //should get rid of word "stock"
    int stockSize;
    save >> stockSize;
    FaceUpPile sp = new FaceUpPile;
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

    FaceUpPile disPiles[4];
    for (int d = 0; d < 4; d++){
      FaceUpPile dp;
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
    peep.push_back(p);
  }
  
  save >> tempString;
  int deckSize;
  save >> deckSize;
  vector<Card> deckPile;
  for (int i5 = 0; i5 < deckSize; i5++){
    int cardNum;
    save >> cardNum;
    Card c = new Card(cardNum);
    deckPile.push_back(c);
  }
  draw = new DrawPile(deckPile);
  draw.setRand(isShuffle);

  for (int i6 = 0; i6 < 4; i6 ++){
    save >> tempString;
    int buildSize;
    save >> buildSize;
    vector<Card> b;
    for (int i7 = 0; i7 < buildSize; i7 ++){
      int cardNum;
      save >> cardNum;
      Card c = new Card(cardNum);
      b.push_back(c); 
    }
    FaceUpPile* bd = new FaceUpPile(b);
    build[i] = bd;
  }
  
  
}

SkipBoGame::~SkipBoGame(){
  for (int i = 0; i < peep.size(); i ++){
    delete peep.at(i);
  }
}

void SkipBoGame::playTurn(){

  int playerToGo = (curp+1)%nump;
  bool discard = false;
  peep[playerToGo]->display();

  peep[playerToGo]->updateDrawPile(draw);
  peep[playerToGo]->drawToHand();
	
  while(!discard){
    display();
    discard = play(playerToGo);  
    
  }
  draw = peep[playerToGo]->getUpdatedDrawPile();
  curp ++;
}

bool SkipBoGame::checkWin(){
  for (int i = 0; i < nump; i ++){
    if (peep[i]->stockSize() == 0){
      return true;
    }
  }
  return false;
}

bool SkipBoGame::play(int p){
  std::cout << "(m)ove [start] [end] or (d)raw ? ";
  std::string action;
  std::string from;
  std::string to;

  std::cin >> action >> from >> to;
  std::cout << std::endl;

  int f;
  int t;
  bool built = false;
  int b;
  
  if (action != "d"){
    f = std::stoi(from);
    if (to == "a" || to == "b" || to == "c" || to == "d"){
      built = true;
      if (to == "a"){b = 0;}
      if (to == "b"){b = 1;}
      if (to == "c"){b = 2;}
      if (to == "d"){b = 3;}
    }else{
      t = std::stoi(to);
    }
  }
  
  
  if (action == "d"){
    //draw
    if (peep[p]->handSize() == 0){
      for (int i = 0; i < 5; i ++){
	peep[p]->drawToHand();
      }
    }
  }
  else if (action == "m"){
    Card c;
    if (f == 0){
      c = getStockPileCard();
    }else if (f >= 1 && f <= 4){
      c = getDiscardPileCard(f);
    }else if (f >= 5 && f <= 9){
      c = getHandPileCard(f);
    }
    //move
   
    
    if (t <= 4 && t >= 1){
      //move to discard
      handToDiscard(f, t);
      return true;
    }
    
    build[b].addCard(c);
    
  }
  return false;
}

void SkipBoGame::save(std::string file){
  
  //int turn = curp;
  std::ofstream saveFile(file);
  /*saveFile << isShuffle << " " << nump << " " << curp << endl;
  for (int i = curp; i < nump + curp; i ++){
    int playerN = i;
    if (i > nump-1){
      playerN -= nump;
    }
    std::string p = peep[playerN]->toString();
    saveFile << p << endl;//might need hand tostring unless it inherits from pile?
    
  }

  saveFile << draw.toString() << endl;

  for (int i = 0; i < 4; i ++){
    saveFile << build[i]->toString() << endl;
  }
  */
  saveFile << toString();


}
