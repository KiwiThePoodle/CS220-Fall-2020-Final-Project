#include <iostream>
#include <string>
#include <sstream>
#include "Player.h"

// for live game play - must not change!
void Player::display() const {
  std::cout << "Current ";
  std::cout << name << ":  Stock{0}: " ;
  stock->display(); //using pointers now
  std::cout << std::endl;
  std::cout << "   Discards{1-4}: ";
  for (int i = 0; i < 4; ++i) {
    discard[i].display();
    std::cout << "  ";
  }
  std::cout << std::endl;
  std::cout << "   Hand{5-9}: ";
  handPile->display(); //using pointers now
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
  result << "Stock " << stock->toString();
  result << "Hand " << handPile->toString();
  for (int i = 0; i < 4; ++i) {
    result << "Discard" << i << " " << discard[i].toString();
  }
  return result.str();
}

void Player::readIn(std::istream & is) {
  std::string playerName;
  std::string temp;
  is >> playerName;   //reads first string as player name
  name = playerName;
  int size;   //size of each pile
  int cardNumber;
  is >> temp;
  is >> size;   //first int found is stock pile size
  for(int i = 0; i < size; i++) {   //loop through stock size number of times
    is >> cardNumber;   //each int is a number representing a card
    stock->addCard(Card(cardNumber));   //add new cards to stock pile for each number
  }
  is >> temp;
  is >> size;   //next int is hand pile size
  for(int i = 0; i < size; i++) {   //adds hand size number of cards to hand pile
    is >> cardNumber;
    handPile->addCard(Card(cardNumber));
  }
  is >> temp;
  is >> size;   //next int is discard[0] pile size
  for(int i = 0; i < size; i++) {
    is >> cardNumber;
    discard[0].addCard(Card(cardNumber));
  }
  is >> temp;
  is >> size;   //next int is discard[1] pile size
  for(int i = 0; i < size; i++) {
    is >> cardNumber;
    discard[1].addCard(Card(cardNumber));
  }
  is >> temp;
  is >> size;   //discard[2] pile size
  for(int i = 0; i < size; i++) {
    is >> cardNumber;
    discard[2].addCard(Card(cardNumber));
  }
  is >> temp;
  is >> size;   //discard[3] pile size
  for(int i = 0; i < size; i++) {
    is >> cardNumber;
    discard[3].addCard(Card(cardNumber));
  }
}

/*Player::~Player() {   //deletes each pile for a player
  delete stock;
  delete handPile;
  delete discard[0];
  delete discard[1];
  delete discard[2];
  delete discard[3];
  delete updatedDrawPile;
}*/

void Player::drawToHand() {                   //called at the start of player's turn, draws cards until hand is full
  int cardsToDraw = 5 - handPile->size();
  for(int i = 0; i < cardsToDraw; i++) {
    handPile->addCard(updatedDrawPile->topCard());   //adds top card from draw pile to hand, *removes card from draw pile*
  }
}

void Player::handToDiscard(int handNum, int discardNum) {   //moves card from hand to a discard pile
  handNum -= 5;
  //Card temp = handPile->removeCard(handNum);
  discardNum -= 1;
  discard[discardNum].addCard(temp);
}

Card Player::getStockPileCard() {   //returns top card of stock
  return stock->topCard();
}

Card Player::getDiscardPileCard(int discardNum) {   //returns top card of a discard pile
  discardNum -= 1;
  return discard[discardNum].topCard();
}

Card Player::getHandPileCard(int handNum) {   //returns a card from hand
  handNum -= 5;
  Card temp = handPile->removeCard(handNum);
  return temp;
}
