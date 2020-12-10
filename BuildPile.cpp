#include <iostream>
#include "BuildPile.h"

void BuildPile::addCards(Drawpile* d) {

  for(int i = 0; i < pile.size(); i++) {
    Card c = pile.topCard();
    d->addcard(c);
  }
  cardNumber = 0;
}
