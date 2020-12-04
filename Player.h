#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>
#include <iostream>
#include "Card.h"
#include "Pile.h"

class Player {
 protected:
  String name;
  Pile stock;
  Pile discard[4];
  Pile hand;
 public:
  Player(std::string player_name, Pile stock_pile, Pile discard_piles[4], Pile hand_pile) {
    name = player_name;
    stock = stock_pile;
    discard = discard_piles;
    hand = hand_pile;
  }
  void display() const;
  std::string toString() const;
  void readIn(istream &);                     //needs to be implemented

  //actions that a player can perform
  void drawToHand() {                         //called at the start of player's turn, draws cards until hand is full
    int cardsToDraw = 5 - hand.size();
    for(int i = 0; i < cardsToDraw; i++) {
      hand.addCard(/*insert card from drawpile*/);
    }
  }
  void handToDiscard(Card cd, char c);
  void stockpileToBuild(Card cd);
  void discardToBuild(Card cd, char c);
  void handToBuild(Card cd);
};


#endif
