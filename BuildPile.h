#ifndef _BUILDPILE_H
#define _BUILDPILE_H

#include <iostream>
#include "Card.h"
#include "Pile.h"
#include "FaceUpPile.h"
#include "DrawPile.h"

class BuildPile : public FaceUpPile {
 private:
  int cardNumber;   //helps keep track of cardNumber in the build pile, even with a wildcard
 public:
  BuildPile() { pile = std::vector<Card>{}; cardNumber = 0; }

  BuildPile( std::vector<Card> f) { pile = f; cardNumber = 0; }
 
  void incrementCardNumber() { cardNumber++; }   //called after card is added to build pile
  
  int getCardNumber() { return cardNumber; }   //called to get the current number

  void addCards(DrawPile* d);   //add cards to draw pile after it becomes empty
};

#endif
