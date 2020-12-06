#ifndef _HAND_H
#define _HAND_H

#include <iostream>
#include "Card.h"
#include "Pile.h"

class Hand {
 protected:
  Pile hand;
 public:
  Hand() { }

  Hand(Pile h) { hand = h; }

  virtual void display() const;

  ~Hand();
};

#endif
