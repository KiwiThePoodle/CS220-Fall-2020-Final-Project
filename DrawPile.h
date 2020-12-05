#ifndef _DRAWPILE_H
#define _DRAWPILE_H

#include <iostream>
#include "Card.h"
#include "Pile.h"

class DrawPile {
 protected:
  Pile drawPile;
 public:
  drawPile() { }

  drawPile(Pile d) { drawPile = d; }

  virtual void display() const;
};

#endif
