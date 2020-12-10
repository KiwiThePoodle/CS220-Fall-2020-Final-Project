#ifndef _FACEUPPILE_H
#define _FACEUPPILE_H

#include <iostream>
#include "Card.h"
#include "Pile.h"

class FaceUpPile : public Pile{
 public:
  FaceUpPile() { pile = std::vector<Card>{};}

  FaceUpPile(std::vector<Card> f) { pile = f;}

  void display() const;

  //other needed functions inherited from pile.h
};

#endif
