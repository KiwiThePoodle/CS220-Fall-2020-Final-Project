#include <iostream>
#include "BuildPile.h"

void BuildPile::addCards(DrawPile* d) {

  for(int i = 0; i < pile.size(); i++) {
    Card c = pile.topCard();
    d->addcard(c);
  }
  cardNumber = 0;
}
