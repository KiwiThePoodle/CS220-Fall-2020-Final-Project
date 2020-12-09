#ifndef _FACEUPPILE_H
#define _FACEUPPILE_H

#include <iostream>
#include "Card.h"
#include "Pile.h"

class FaceUpPile : public Pile{
 //protected:
  //Pile pile;
 public:
  FaceUpPile() { Pile();}
  // pile = std::vector<Card>;
  

  FaceUpPile(std::vector<Card> f) { pile = f;}

  void display() const;

  //~FaceUpPile();

  //virtual void addCard(const Card& c) { pile.push_back(c); }

  //Card topCard();

  //int size() { return pile.size(); }
};

#endif
