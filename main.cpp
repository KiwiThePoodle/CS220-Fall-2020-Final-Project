//
//

#include <iostream>

int main(int argc, char *argv[]) {
  bool shuffle;
  int numPlayers;
  int stockPileSize;
  std::ifstream deckStartFile;


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
    std::ifstream ifile(argv[2]);
    if(!ifile.is_open()) {
      std::cout << "invalid program usage: can't open input game file" << std::endl;
      return 1;
    }
    else {
      deckStartFile = argv[2];
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

    if(int(argv[4]) >  5 ) {//stock size confused how to implement
      stockPileSize = argv[4];
      std::cout << "stock size is " << stockPileSize << std::endl;
    }
    else {
    }

    //open file to check it
    
  }

  
      
