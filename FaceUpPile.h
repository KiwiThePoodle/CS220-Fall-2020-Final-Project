#ifndef _FACEUPPILE_H
#define _FACEUPPILE_H

#include <iostream>
#include "Card.h"
#include "Pile.h"

class FaceUpPile {
 protected:
  Pile pile;
 public:
  FaceUpPile() { pile = new Pile(); }

  FaceUpPile(Pile f) { pile = f; }

  virtual void display() const;

  ~FaceUpPile();
};

#endif
