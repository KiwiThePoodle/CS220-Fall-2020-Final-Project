//
//

#include <iostream>
#include "SkipBoGame.h"

int main(int argc, char *argv[]) {
  bool shuffle;
  int numPlayers;
  int stockPileSize;


  if(argc <= 2 || argc == 4) {
    std::cout << "invalid program usage: invalid number of arguments" << std::endl;
    return 0;
  }

  if(string(argv[1]) == "false") {
    shuffle = false;
  }
  else if(string(argv[1]) == "true") {
    shuffle = true;
  }
  else {
    std::cout << "invalid program usage: invalid first argument" << std::endl;
    return 1;
  }

  if(argc == 3) {
    std::ifstream savedGame(argv[2]);
    if(!ifile.is_open()) {
      std::cout << "invalid program usage: can't open input game file" << std::endl;
      return 1;
    }
    else {
      //continue the game, not sure how to do this
    }
  }

  if(argc == 5) {
    if(int(argv[3]) > 6 || int(argv[3]) < 2) {
      std::cout << "invalid program usage: num players must be 2-6" << std::endl;
      return 1;
    }
    else {
      numPlayers = int(argv[3]);
      std::cout << "num players is " << numPlayers << std::endl;
    }

    if(int(argv[4]) * numPlayers > 162 || int(argv[4]) < 0) { //not exactly sure its supposed to be 162
      std::cout << "invalid program usage: bad stock size" << std::endl;
      return 1;
    }
    else {
      stockSize = int(argv[4]);
      std::cout << "stock size is " << stockSize << std::endl;
    }

    std::ifstream deckStartFile(argv[5]);
    if(!deckStartFile.is_open()) {
      std::cout << "invalid program usage: can't open deck file" << std::endl;
      return 1;
    }
    else {
      //create a skipbogame object
    }
    return 0;
  }
