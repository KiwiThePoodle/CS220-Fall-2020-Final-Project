#ifndef _HAND_H
#define _HAND_H

#include <iostream>
#include "Card.h"
#include "Pile.h"

class Hand {
 protected:
  Pile pile;
 public:
  Hand() { pile = new Pile(); }

  Hand(Pile h) { pile = h; }

  virtual void display() const;

  ~Hand();

  int size() { return pile.size(); }

  void add(Card c) { pile.addCard(c); }
};

#endif
