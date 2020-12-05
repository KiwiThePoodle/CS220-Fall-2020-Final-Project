#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>
#include <string>
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
  Player() {
    name = "";
    stock = new Pile();
    discard[0] = new Pile();
    discard[1] = new Pile();
    discard[2] = new Pile();
    discard[3] = new Pile();
    hand = new Pile();
  }
  
  Player(string player_name, Pile stock_pile, Pile discard_piles[4], Pile hand_pile) {
    name = player_name;
    stock = stock_pile;
    discard = discard_piles;
    hand = hand_pile;
  }

  void display() const;

  std::string toString() const;

  void readIn(istream & is);

  ~Player();   //destructor

  //actions that a player can perform
  void drawToHand();

  void handToDiscard(Card cd, char c);

  void stockpileToBuild(Card cd);

  void discardToBuild(Card cd, char c);

  void handToBuild(Card cd);

};


#endif
