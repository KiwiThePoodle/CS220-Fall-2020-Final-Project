#ifndef _HAND_H
#define _HAND_H

#include <iostream>
#include "Card.h"
#include "Pile.h"

class Hand : public Pile {
 protected:
  Pile pile;
 public:
  Hand() { pile = new Pile(); }

  Hand(vector<Card>h) { pile = h; }

  void display() const;

  ~Hand();

  int size() { return pile.size(); }

  void add(Card c) { pile.addCard(c); }
};

#endif
