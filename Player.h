#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>
#include <string>
#include <iostream>
#include "Card.h"
#include "Pile.h"
#include "DrawPile.h"

class Player {
 protected:
  String name;
  Pile stock;
  FaceUpPile discard[4];
  Pile hand;
  DrawPile updatedDrawPile;
 public:
  Player() {
    name = "";
    stock = new Pile();
    discard[0] = new FaceUpPile();
    discard[1] = new FaceUpPile();
    discard[2] = new FaceUpPile();
    discard[3] = new FaceUpPile();
    hand = new Pile();
    updatedDrawPile = new DrawPile();
  }
  
  Player(string player_name, Pile stock_pile, FaceUpPile discard_piles[4], Pile hand_pile) {
    name = player_name;
    stock = stock_pile;
    discard = discard_piles;
    hand = hand_pile;
  }

  void display() const;

  std::string toString() const;

  void readIn(istream & is);

  ~Player();   //destructor

  void updateDrawPile(Drawpile d) { updatedDrawPile = d; }

  DrawPile getUpdatedDrawPile() { return updatedDrawPile; };

  //actions that a player can perform
  void drawToHand();

  void handToDiscard(Card cd, char c);

  void stockpileToBuild(Card cd);

  void discardToBuild(Card cd, char c);

  void handToBuild(Card cd);

};


#endif
