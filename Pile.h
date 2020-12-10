#ifndef _PILE_H
#define _PILE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Card.h"

class Pile {
 protected:
  std::vector<Card> pile;

 public:
  Pile() { }
 
  Pile(std::vector<Card> p) { pile = p; }
 
  ~Pile(){
     /*for(int i = 0; i < pile.size(); i ++){
        delete pile.at(i);
     }*/
   //delete (pile);
  }
 
 std::vector<Card> getPile() {   //returns the pile
  std::vector<Card>r;
  for (int i = 0; i < (int)pile.size(); i ++){
   r.push_back(pile.at(i));
   
  }
  return r;
  }

  void shuffle(){  //for shuffling the deck if random is on
     std::random_shuffle(pile.begin(), pile.end());
  }
 
  int size() const { return pile.size(); }

  virtual void addCard(const Card& c) { pile.push_back(c); }

  std::string toString() const;  // for saving state

  Card removeCard(int cardIndex){  //removes and returns a card at a given index
     Card c = pile.at(cardIndex);
     pile.erase(pile.begin() + cardIndex);  
   return c;
  }
 
  void readIn(std::istream & is){

    while(!is.eof()){
      int n;
      is >> n;
      Card* c = new Card(n);
      pile.insert(pile.begin(), 1, *c);   //instead of push_back so the cards are not read-in backwards
    }
    
  }// students to write this, companion to toString()

  virtual void display() const = 0;  // for live game play, must override

  Card topCard();   //function returns the top card of a pile
};


#endif
