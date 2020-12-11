#include <iostream>
#include "BuildPile.h"

void BuildPile::addCards(DrawPile* d) {

  int temp = pile.size();
  for(int i = 0; i < temp; i++) {
    Card c = this->topCard();
    d->addCard(c);
  }
  cardNumber = 0;
  //delete d;
}
