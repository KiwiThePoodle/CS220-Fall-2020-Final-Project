#ifndef _HAND_H
#define _HAND_H

#include <iostream>
#include "Card.h"
#include "Pile.h"

class Hand {
 protected:
  Pile hand;
 public:
  hand() { }

  hand(Pile h) { hand = h; }

  virtual void display() const;
};

#endif
