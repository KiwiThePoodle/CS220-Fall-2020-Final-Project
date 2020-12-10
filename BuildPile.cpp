#include <iostream>
#include "BuildPile.h"

void BuildPile::addCards(DrawPile* d) {

  for(int i = 0; i < (int)pile.size(); i++) {
    Card c = this->topCard();
    d->addCard(c);
  }
  cardNumber = 0;
}
