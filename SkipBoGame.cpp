#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
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
    build[j]->display();
    std::cout << " ";
  }
  std::cout << std::endl;
  peep[curp%nump]->display();
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
    draw.setRand(true);
  }
  else {   //else first player is 0
    curp = 0;
  }
  nump = pCount;
  stock = stk;
  isShuffle = isS;
  end = false;
  
  std::ifstream deck0("deck0.txt");   //reads in the playing deck
  draw.readIn(deck0);
  draw.setRand(isShuffle);
	
  if(isS) {   //if shuffle is on, shuffle the draw pile
    draw.shuffle();
  }
  
  //need to make 4 piles for the build pile
  for (int i = 0; i < 4; i ++){
    BuildPile* p = new BuildPile();
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
  
  int index = curp;
  for(int i = 0; i < stock; i++) {   //gives each player's stock pile a card in round-robin fashion
    for(int j = 0; j < nump; j++) {
      peep[index]->addToStockPile(draw.topCard());                                
      index = (index + 1) % nump; 
    }
  }
  std::string saveFile = file;
  }

SkipBoGame::SkipBoGame(bool isS, std::string file){
  isShuffle = isS;

  if(isS) {
    draw.setRand(true);
  }
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
    FaceUpPile* sp = new FaceUpPile;
    for (int i2 = 0; i2 < stockSize; i2 ++){
      int cardNum;
      save >> cardNum;
      Card* c = new Card(cardNum);
      sp->addCard(*c);
    }

    save >> tempString; //gets rid of "Hand"
    if (tempString != "Hand"){
      //use this for error checking right now, if the code reaches here then we have an issue
    }

    int handSize;
    save >> handSize;
    Hand* h = new Hand();
    for (int i3 = 0; i3 < handSize; i3++){
      int cardNum;
      save >> cardNum;
      Card* c = new Card(cardNum);
      h->addCard(*c);//not sure how hand works yet, just using this as filler
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
	Card* c = new Card(cardNum);
	dp.addCard(*c);
      }
      disPiles[i] = dp;
    }

    Player* p = new Player(playerName, sp, disPiles, h);   //creates players
    peep.push_back(p);
  }
  
  save >> tempString;
  int deckSize;
  save >> deckSize;
  for (int i5 = 0; i5 < deckSize; i5++){    //cards to draw pile
    int cardNum;
    save >> cardNum;
    Card* c = new Card(cardNum);
    draw.addCard(*c);
  }
  draw.setRand(isShuffle);

  for (int i6 = 0; i6 < 4; i6 ++){   //cards to build piles
    save >> tempString;
    int buildSize;
    save >> buildSize;
    std::vector<Card> b;
    for (int i7 = 0; i7 < buildSize; i7 ++){
      int cardNum;
      save >> cardNum;
      Card* c = new Card(cardNum);
      b.push_back(*c); 
    }
    FaceUpPile* bd = new FaceUpPile(b);
    build[i6] = bd;
  }
  
  
}

SkipBoGame::~SkipBoGame(){   //destructor
  for (int i = 0; i < (int)peep.size(); i ++){
    delete peep.at(i);
  }
}

void SkipBoGame::playTurn(){   //just plays a player's entire turn

  int playerToGo = (curp)%nump;   //updates player
  bool discard = false;   //for if the player plays a card to a discard pile

  peep[playerToGo]->updateDrawPile(&draw);   //update draw pile to player and draw to hand
  peep[playerToGo]->drawToHand();

  display();	
  while(!discard && !checkWin()){   //if played to discard pile or player wins, end turn
   
  discard = play(playerToGo);
  display();    
  }
  DrawPile* temp = peep[playerToGo]->getUpdatedDrawPile();   //receives draw pile back from player
  draw = *temp;
  curp ++;
}

bool SkipBoGame::checkWin(){
  for (int i = 0; i < nump; i ++){   //just checks if any player has zero cards in stock
    if (peep[i]->stockSize() == 0){
      curp = i;
      return true;
    }
  }
  return false;
}

void SkipBoGame::illegalMove(){

    std::cout << "illegal command, try again" << std::endl << std::endl;
    display();
    //std::cout << "(m)ove [start] [end] or (d)raw ? ";
    
}

/*
bool SkipBoGame::play(int p){
   bool move = true;
   while (move){
     std::cout << "(m)ove [start] [end] or (d)raw ? ";
     std::string action;
     std::string from;
     std::string to;

     std::cin >> action;
     std::cin >> from;
     std::cin>>to;   //depending on user input (move) checks validity
     while (((from == "1" || from == "2" || from == "3" || from == "4") &&(to == "1" || to == "2" || to == "3" || to == "4") )||(from == "0" && (to == "1" || to == "2" || to == "3" || to == "4")) || (action!= "m" && action != "d") || (from != "0" && from != "1" && from != "2" && from != "3" && from != "4" && from != "5" && from != "6" && from != "7" && from != "8" && from != "9")  ||(to != "a" && to != "b" && to != "c" && to != "d" && to != "1" && to != "2" && to != "3" && to != "4" )){
       illegalMove();
       std::cin >> action;
       std::cin >> from;
       std::cin >> to;
     }
	
     std::cout << std::endl;

     int f;
     int t;
     int b;
  
     if (action != "d"){   //just converts from letter to number for easier usage
       f = std::stoi(from);
       if (to == "a" || to == "b" || to == "c" || to == "d"){
	 if (to == "a"){b = 0;}
	 if (to == "b"){b = 1;}
	 if (to == "c"){b = 2;}
	 if (to == "d"){b = 3;}
	       t = 100;
       }
       else{
	 t = std::stoi(to);  
       }
     }
  
  
     if (action == "d"){   //checks if player can draw, then draws if player's hand size is zero
    //draw
       if (peep[p]->handSize() == 0){
	 for (int i = 0; i < 5; i ++){
	   peep[p]->drawToHand();
	 }
       }
     }
     Card c;
     if (action == "m"){   //moves cards depending on where from and where to  
       
       if (f == 0){
	 int temp = peep[p]->getStockCardValue();
	 if (build[b]->size() == 0){
	   c = Card(temp);
	   move = true;
	 }else{
	   if((temp == 0) || (temp == build[b]->topCardValue() + 1)) {
	     c = Card(temp);
		   //c = peep[p]->getStockPileCard();
	     move = true;
	   }else{move = false;illegalMove();}
	 }
       }else if (f >= 1 && f <= 4){
	 int temp = peep[p]->getDiscardCardValue(f);
	 if (build[b]->size() == 0){
	   //c = peep[p]->getDiscardPileCard(f);
	   c = Card(temp);
		 move = true;
	 }else{
	   if((temp == 0) || (temp == build[b]->topCardValue() + 1)) {
	     c = Card(temp);
		   //c = peep[p]->getDiscardPileCard(f);
	     move = true;
	   }else{move = false;illegalMove();}
	 }
       }else if (f >= 5 && f <= 9){
	       //std::cout << "Test1" << std::endl;
	 //      std::cout << f-5 << "." << peep[p]->handSize()-1 << std::endl;
	 	if (f - 5 > peep[p]->handSize()-1){
	   		illegalMove();
	   		move=false;
	   
	 	}else{
	   int temp = peep[p]->getHandCardValue(f);
		
	   if (build[b]->size() == 0){
	     //c = Card(temp);
		   c = peep[p]->getHandPileCard(f);
	//	   std::cout << "Test2" << std::endl;
	     move = true;
	     
	   }else{////////////////////////////////////////////
		  
	     if((temp == 0) || (temp == build[b]->topCardValue() + 1)) {
	       move = true;
	       //c = Card(temp);
		     c = peep[p]->getHandPileCard(f);
	//	     std::cout << "Test3" << std::endl;
	     }else
		if (t <= 4 &&t>=1){     
		     if((temp == peep[p]->getDiscardCardValue(t)+1)){
	     		move = true;
		     	c = peep[p]->getHandPileCard(f);
		     
	     	      }else{move = false; illegalMove();}
		}else{move = false; illegalMove();}
	   }
	 }
       }
       else {
	 move = false;
	       illegalMove();
       }
       
       
       if (move == true){
	 if (t <= 4 && t >= 1){
	   
	   peep[p]->handToDiscard(c, t);
	   
	   return true;
	 }
       }
       if(move) {
	 build[b]->addCard(c);
       }
       //  else {
       
    //display();
    std::cout << "(m)ove [start] [end] or (d)raw ? ";
    std::cin >> action;
    std::cin >> from;
    std::cin>>to;
    
	  
       move = !move;
     }
     
   }
   
   return false;
}

*/
	
bool SkipBoGame::play(int p){
   bool move = true;
   while (move){
     std::cout << "(m)ove [start] [end] or (d)raw ? ";
     std::string action;
     std::string from;
     std::string to;

     std::cin >> action;
     std::cin >> from;
     std::cin>>to;   //depending on user input (move) checks validity
     while (((from == "1" || from == "2" || from == "3" || from == "4") &&(to == "1" || to == "2" || to == "3" || to == "4") ) || (from == "0" && (to == "1" || to == "2" || to == "3" || to == "4")) || (action!= "m" && action != "d") || (from != "0" && from != "1" && from != "2" && from != "3" && from != "4" && from != "5" && from != "6" && from != "7" && from != "8" && from != "9")  ||(to != "a" && to != "b" && to != "c" && to != "d" && to != "1" && to != "2" && to != "3" && to != "4" ) || ((from == "5" || from == "6" || from == "7" || from == "8" || from == "9") &&(to == "5" || to == "6" || to == "7" || to == "8" || to == "9"))){
       illegalMove();
       std::cout << "(m)ove [start] [end] or (d)raw ? ";
       std::cin >> action;
       std::cin >> from;
       std::cin >> to;
     }
	
     std::cout << std::endl;

     int f;
     int t;
     int b;
  
     if (action != "d"){   //just converts from letter to number for easier usage
       f = std::stoi(from);
       if (to == "a" || to == "b" || to == "c" || to == "d"){
	        if (to == "a"){b = 0;}
	        if (to == "b"){b = 1;}
	        if (to == "c"){b = 2;}
	        if (to == "d"){b = 3;}
	            t = 100;
          }else{
	            t = std::stoi(to);  
          }
       }
    if (action == "d"){   //checks if player can draw, then draws if player's hand size is zero
    //draw
       if (peep[p]->handSize() == 0){
	        for (int i = 0; i < 5; i ++){
	            peep[p]->drawToHand();
	        }
       }
    }
     
     if (action == "m"){
     
      int leave;
      int target;
      Card c;
	     
      if (f == 0){
        leave = peep[p]->getStockCardValue();
      }
      if (f >= 1 && f <= 4){
	if(peep[p]->discardIsEmpty(f)){
		leave = 100;
	}else{
		
        	leave = peep[p]->getDiscardCardValue(f);
      	}
      }
      if (f >= 5 && f <= 9){
	if (f-5 > peep[p]->handSize()-1){
		leave = 100;
	}else{
        	leave = peep[p]->getHandCardValue(f);
	}
      }
       
      if (t == 100){
        if (build[b]->size()==0){
          target = 0;
        }else{
          target = build[b]->topCardValue();
        }
      }
       
      if (t >= 1 && t <=4){
	      
	if (peep[p]->discardIsEmpty(t)){
		
		target = 0;
	}else{
       	 	target = peep[p]->getDiscardCardValue(t);
	}
      }
       
      if (leave == target + 1 || leave == 0 || (t >= 1 && t <=4 && leave != 100)){
	
        move = true;
	if (f == 0){
	  c = Card(leave);
	  build[b]->addCard(c);
	  build[b]->incrementCardNumber();
	}
	if (f >= 1 && f <= 4){
	  c = Card(leave);
	  build[b]->addCard(c);
	  build[b]->incrementCardNumber();
	  
	}
	if (f >= 5 && f <= 9){
	  c = peep[p]->getHandPileCard(f);
	  if (t >= 1 && t <= 4){
	    peep[p]->handToDiscard(c,t);
	    return true;
	  }
	  build[b]->addCard(c);
	  build[b]->incrementCardNumber();
	}
      }else{
        move = false;
        illegalMove();
      }
       
     }
    
     move = !move;
     
   }
   
   return false;
}
void SkipBoGame::save(std::string file){   //saves game
  
  std::ofstream saveFile(file);
  saveFile << toString();


}
