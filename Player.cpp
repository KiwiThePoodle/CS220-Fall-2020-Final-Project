#include <iostream>
#include <string>
#include <sstream>
#include "Player.h"

// for live game play - must not change!
void Player::display() const {
  std::cout << "Current ";
  std::cout << name << ":  Stock{0}: " ;
  stock.display();
  std::cout << std::endl;
  std::cout << "   Discards{1-4}: ";
  for (int i = 0; i < 4; ++i) {
    discard[i].display();
    std::cout << "  ";
  }
  std::cout << std::endl;
  std::cout << "   Hand{5-9}: ";
  hand.display();
  std::cout << std::endl;
}

/* saving state format - must not change!
PlayerName
Stock size
01 02 03  ...
...
Hand size
01 02 03 04 05
Discard1 size
01 02 03 04 ...
...
Discard2 size
...
Discard3 size
...
Discard4 size
...
*/
std::string Player::toString() const {
  std::stringstream result;
  result << name << "\n";
  result << "Stock " << stock.toString();
  result << "Hand " << hand.toString();
  for (int i = 0; i < 4; ++i) {
    result << "Discard" << i << " " << discard[i].toString();
  }
  return result.str();
}

void Player::readIn(std::istream & is) {
  string playerName;
  is >> playerName;
  name = playerName;
  int size;
  int cardNumber;
  is >> size;
  for(int i = 0; i < size; i++) {
    is >> cardNumber;
    stock.addCard(Card(cardNumber));
  }
  is >> size;
  for(int i = 0; i < size; i++) {
    is >> cardNumber;
    hand.addCard(Card(cardNumber));
  }
  is >> size;
  for(int i = 0; i < size; i++) {
    is >> cardNumber;
    discard[0].addCard(Card(cardNumber));
  }
  is >> size;
  for(int i = 0; i < size; i++) {
    is >> cardNumber;
    discard[1].addCard(Card(cardNumber));
  }
  is >> size;
  for(int i = 0; i < size; i++) {
    is >> cardNumber;
    discard[2].addCard(Card(cardNumber));
  }
  is >> size;
  for(int i = 0; i < size; i++) {
    is >> cardNumber;
    discard[3].addCard(Card(cardNumber));
  }
}

Player::~Player() {
  delete stock;
  delete hand;
  delete discard[0];
  delete discard[1];
  delete discard[2];
  delete discard[3];
}

void Player::drawToHand() {                    //called at the start of player's turn, draws cards until hand is full
  int cardsToDraw = 5 - hand.size();
  for(int i = 0; i < cardsToDraw; i++) {
    hand.addCard(/*insert card from drawpile*/);
    /*remove that card from drawpile*/
  }
}

void Player::handToDiscard(Card cd, char c) {
  
}

void Player::stockpileToBuild(Card cd) {
  
}

void Player::discardToBuild(Card cd, char c) {
  
}

void Player::handToBUild(Card cd) {
  
}
