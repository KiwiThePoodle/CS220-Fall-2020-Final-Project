#ifndef _HAND_H
#define _HAND_H

#include <iostream>
#include "Card.h"
#include "Pile.h"
#include "FaceUpPile.h"

class Hand {
 protected:
  FaceUpPile hand;
 public:
  Hand() { }

  Hand(FaceUpPile h) { hand = h; }

  virtual void display() const;

  ~Hand();
};

#endif
