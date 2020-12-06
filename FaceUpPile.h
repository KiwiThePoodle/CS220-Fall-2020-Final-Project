#ifndef _FACEUPPILE_H
#define _FACEUPPILE_H

#include <iostream>
#include "Card.h"
#include "Pile.h"

class FaceUpPile {
 protected:
  Pile faceUpPile;
 public:
  FaceUpPile() { }

  FaceUpPile(Pile f) { faceUpPile = f }

  virtual void display() const;

  ~FaceUpPile();
};

#endif
