#include <iostream>
#include "BuildPile.h"

void BuildPile::addCards(DrawPile* d) {   //adds cards to the drawpile from the buildpile

  int temp = pile.size();
  for(int i = 0; i < temp; i++) {
    Card c = this->topCard();
    d->addCard(c);
  }
  cardNumber = 0;
  //delete d;   this was causing us errors but after commenting it out, our code worked
}
