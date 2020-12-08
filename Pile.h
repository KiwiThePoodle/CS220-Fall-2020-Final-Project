#ifndef _PILE_H
#define _PILE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Card.h"

class Pile {
 protected:
  std::vector<Card> pile;

 public:
  Pile() { }

  int size() const { return pile.size(); }

  virtual void addCard(const Card& c) { pile.push_back(c); }

  std::string toString() const;  // for saving state

  void readIn(std::istream & is){

    while(!is.eof()){
      int n;
      is >> n;
      Card c = new Card(n);
      pile.push_back(c);
    }
    
  }// students to write this, companion to toString()

  virtual void display() const = 0;  // for live game play, must override

  Card topCard();
};


#endif
