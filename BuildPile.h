#ifndef _BUILDPILE_H
#define _BUILDPILE_H

#include <iostream>
#include "Card.h"
#include "Pile.h"
#include "FaceUpPile.h"
#include "DrawPile.h"

class BuildPile : public FaceUpPile {
 private:
  int cardNumber;
 public:
  BuildPile() { pile = std::vector<Card>{}; cardNumber = 0; }

  BuildPile( std::vector<Card> f) { pile = f; cardNumber = 0; }

  void incrementCardNumber() { cardNumber++; }
  
  int getCardNumber() { return cardNumber; }

  void reshuffle(DrawPile* d);
};

#endif
