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
  FaceUpPile stock;
  FaceUpPile discard[4];
  Pile hand;
  DrawPile updatedDrawPile;   //used so a player can access the drawPile and update it as well
 public:
  Player() {   //blank player
    name = "";
    stock = new FaceUpPile();
    discard[0] = new FaceUpPile();
    discard[1] = new FaceUpPile();
    discard[2] = new FaceUpPile();
    discard[3] = new FaceUpPile();
    hand = new Pile();
    updatedDrawPile = new DrawPile();
  }
  
  Player(string player_name, FaceUpPile stock_pile, FaceUpPile discard_piles[4], Pile hand_pile) {   //player name and piles of a player
    name = player_name;
    stock = stock_pile;
    discard = discard_piles;
    hand = hand_pile;
  }

  void display() const;

  std::string toString() const;

  void readIn(istream & is);

  ~Player();   //destructor

  void updateDrawPile(Drawpile d) { updatedDrawPile = d; }   //called at the start of each players turn to update the drawPile for the player to access

  DrawPile getUpdatedDrawPile() { return updatedDrawPile; };   //called at the end of each players turn to update the drawPile in the game

  int handSize() {   //can be used to check when player has zero cards
    return hand.size();
  }
  
  //methods used to get the value of the card, should help with checking if cards can be moved to build pilea
  int getStockCardValue() {   //returns the value of the top card in the stock pile
    return stock.topCard().getValue();
  }

  int getDiscardCardValue(int discardNum) {   //value of the top card of a specified discard pile
    discardNum -= 1;
    return discard[discardNum].topCard().getValue();
  }

  int getHandCardValue(int handNum) {   //value of a specific hand card
    handNum -= 5;
    return hand.pile[handNum].getValue();
  }

  //methods that help a player perform a move
  void drawToHand();   //called either at the start of a player's turn or when the player has no cards in hand

  void handToDiscard(int handNum, int discardNum);   //directly moves a card from hand to a discard pile

  Card getStockPileCard();   //returns the top card in the stock pile to be placed in a build pile

  Card getDiscardPileCard(int discardNum);   //returns the top card in a specified discard pile to be placed in a build pile

  Card getHandPileCard(int handNum);   //returns the specified card in the hand pile to be placed in a build pile

};


#endif
