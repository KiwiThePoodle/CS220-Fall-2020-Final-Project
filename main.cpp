//
//

#include <iostream>
#include <fstream>
#include "SkipBoGame.h"
#include <string>
#include <cstdlib>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
  bool shuffle; //fields for skipbogame
  int numPlayers;
  int stockPileSize;

  if(argc <= 2 || argc == 4) {
    cout << "invalid program usage: invalid number of arguments" << endl;
    return 0;
  }

  if(std::string(argv[1]) == "false") {
    shuffle = false;
  }
  else if(std::string(argv[1]) == "true") {
    shuffle = true;
  }
  else {
    cout << "invalid program usage: invalid first argument" << endl;
    return 1;
  }

  if(argc == 3) {
    std::ifstream savedGame(argv[2]);
    if(!savedGame.is_open()) {
      cout << "invalid program usage: can't open input game file" << endl;
      return 1;
    }
    else {
      //continue the game, not sure how to do this
      SkipBoGame game = SkipBoGame(shuffle, argv[2]); //creation of skipbogame object for resuming play

      while(!game.checkWin()) {
        cout << "\n >> " << game.getCurrentPlayer() << " turn next" << endl; //playing the game out
        cout << "(p)lay, (s)ave, or (q)uit ? ";
        std::string psq;
        std::cin >> psq;
        if(psq == "q") {
          //delete game;
          cout << "thanks for playing" << endl;
          return 0;
        }
        else if(psq == "s") {
          std::string saveFile;
          cout << "save filename: ";
          std::cin >> saveFile;
          game.save(saveFile);
          //delete game;
          return 0;
        }
        else if(psq == "p") {
          game.playTurn();
        }
      }
      cout << "\nGAME OVER - " << game.getCurrentPlayer() << " wins!" << endl;
      //delete game;
    }
    return 0;
  }

  if(argc == 5) {
    if(atoi(argv[2]) > 6 || atoi(argv[2]) < 2) {
      cout << "invalid program usage: num players must be 2-6" << endl;
      return 1;
    }
    else {
      numPlayers = atoi(argv[2]);
      cout << "num players is " << numPlayers << endl;
    }

    if((numPlayers == 6 && atoi(argv[3]) > 20) || (numPlayers <= 5 && atoi(argv[3]) > 30) || (atoi(argv[3]) < 1)) {
      cout << "invalid program usage: bad stock size" << endl;
      return 1;
    }
    else {
      stockPileSize = atoi(argv[3]);
      cout << "stock size is " << stockPileSize << endl;
    }

    std::ifstream deckStartFile(argv[4]);
    if(!deckStartFile.is_open()) {
      cout << "invalid program usage: can't open deck file" << endl;
      return 1;
    }
    else {
      //create a skipbogame object
      SkipBoGame game = SkipBoGame(shuffle, numPlayers, stockPileSize, argv[4]); //creation of skipbogame object for new game
      
      while(!game.checkWin()) {
	cout << "\n >> " << game.getCurrentPlayer() << " turn next" << endl; //playing the game out
	cout << "(p)lay, (s)ave, or (q)uit ? ";
	std::string psq;
	std::cin >> psq;
	if(psq == "q") {
	  //delete game;
	  cout << "thanks for playing" << endl;
	  return 0;
	}
	else if(psq == "s") {
	  std::string saveFile;
	  cout << "save filename: ";
	  std::cin >> saveFile;
	  game.save(saveFile);
	  //delete game;
	  return 0;
	}
	else if(psq == "p") {
	  game.playTurn();
	}
      }
      cout << "\nGAME OVER - " << game.getCurrentPlayer() << " wins!" << endl;
      //delete game;
    }
    return 1;
  }
}
