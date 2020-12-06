#ifndef _DRAWPILE_H
#define _DRAWPILE_H

#include <iostream>
#include "Card.h"
#include "Pile.h"

class DrawPile {
 protected:
  Pile drawPile;
 public:
  DrawPile() { drawPile = new Pile(); }

  DrawPile(Pile d) { drawPile = d; }

  virtual void display() const;

  ~DrawPile();

  Card topCard();
};

#endif
