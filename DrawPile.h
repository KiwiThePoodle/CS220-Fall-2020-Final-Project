#ifndef _DRAWPILE_H
#define _DRAWPILE_H

#include <iostream>
#include "Card.h"
#include "Pile.h"

class DrawPile : public Pile {
 private:
 bool rand;
 //protected:
  //std::vector<Card> drawPile;
 public:
  DrawPile() { pile = std::vector<Card>{};rand=false;}
   //pile = std::vector<Card>;
  bool getRand() const {
   return rand;
  }

 void setRand(bool b){
  rand = b;
 }
  DrawPile(std::vector<Card> d) { pile = d; }

  void display() const;

  //~DrawPile();

  //Card topCard();
};

#endif
