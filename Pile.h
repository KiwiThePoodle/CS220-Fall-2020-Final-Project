#ifndef _PILE_H
#define _PILE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Card.h"

using std::vector;

class Pile {
 protected:
  vector<Card> pile;

 public:
  Pile() { }
 
  Pile(vector<Card> p) { pile = p; }
 
  ~Pile(){
     /*for(int i = 0; i < pile.size(); i ++){
        delete pile.at(i);
     }*/
   //delete (pile);
  }
 
 vector<Card> getPile() { 
  vector<Card>r;
  for (int i = 0; i < (int)pile.size(); i ++){
   r.push_back(pile.at(i));
   
  }
  return r;
  }

  void shuffle(){
     std::random_shuffle(pile.begin(), pile.end());
  }
 
  int size() const { return pile.size(); }

  virtual void addCard(const Card& c) { pile.push_back(c); }

  std::string toString() const;  // for saving state

  Card removeCard(int cardIndex){
     Card c = pile.at(cardIndex);
     //delete pile.at(cardIndex);
    pile.erase(pile.begin() + cardIndex);  
   return c;
  }
 
  void readIn(std::istream & is){

    while(!is.eof()){
      int n;
      is >> n;
      Card* c = new Card(n);
      //pile.push_back(*c);
      pile.insert(pile.begin(), 1, *c);
    }
    
  }// students to write this, companion to toString()

  virtual void display() const = 0;  // for live game play, must override

  Card topCard();
};


#endif
