#ifndef _HAND_H
#define _HAND_H

#include <iostream>
#include "Card.h"
#include "Pile.h"

class Hand : public Pile {
 public:
  Hand() { pile = std::vector<Card>{}; }

  int getHandSize(){
   return pile.size();
  }
  Hand(std::vector<Card> h) { pile = h; }

  ~Hand(){
   for (int i = 0; i < getHandSize(); i ++){
    delete &pile.at(i)
   }
  }
  void display() const;

  //inherits functions from pile
};

#endif
