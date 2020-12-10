#include <iostream>
#include "BuildPile.h"

void BuildPile::addCards(DrawPile* d) {

  for(int i = 0; i < cardNumber; i++) {
    Card c = this->removeCard(0);
    d->addCard(c);
  }
  cardNumber = 0;
}
