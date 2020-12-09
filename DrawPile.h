#ifndef _DRAWPILE_H
#define _DRAWPILE_H

#include <iostream>
#include "Card.h"
#include "Pile.h"

class DrawPile : public Pile {
 //protected:
  //std::vector<Card> drawPile;
 public:
  DrawPile() { Pile();}
   //pile = std::vector<Card>;
  

  DrawPile(std::vector<Card> d) { pile = d; }

  void display() const;

  //~DrawPile();

  //Card topCard();
};

#endif
