#ifndef _DRAWPILE_H
#define _DRAWPILE_H

#include <iostream>
#include "Card.h"
#include "Pile.h"

class DrawPile : public Pile {
 private:
 bool rand;
 public:
  DrawPile() { pile = std::vector<Card>{};rand=false;}
   //pile = std::vector<Card>;
  bool getRand() const {   //returns whether random is on or not
   return rand;
  }

 void setRand(bool b){   //sets whether random is on or not
  rand = b;
 }
  DrawPile(std::vector<Card> d) { pile = d; }

  void display() const;

  //other functions inherited from pile.h
};

#endif
