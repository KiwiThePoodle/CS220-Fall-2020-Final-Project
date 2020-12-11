#ifndef _HAND_H
#define _HAND_H

#include <iostream>
#include "Card.h"
#include "Pile.h"

class Hand : public Pile {
 public:
  Hand() { pile = std::vector<Card>{}; }

   Hand(std::vector<Card> h) { pile = h; }
 
  int getHandSize() {   //simply returns the number of cards in hand
   return pile.size();
  }

  void display() const;

  //inherits functions from pile
};

#endif
