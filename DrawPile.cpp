#include <iostream>
#include "DrawPile.h"

// for live game play - must not change!
void DrawPile::display() const {
  std::cout << "[XX]/" << size();
}

~DrawPile() {
  delete drawPile;
}

Card topCard() {
  //gets top card from drawPile
}
