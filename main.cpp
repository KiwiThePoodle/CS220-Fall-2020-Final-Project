//
//

#include <iostream>
#include <fstream>
#include "SkipBoGame.h"
#include <string>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
  bool shuffle;
  int numPlayers;
  int stockPileSize;

  if(argc <= 2 || argc == 4) {
    cout << "invalid program usage: invalid number of arguments" << endl;
    return 0;
  }

  if(string(argv[1]) == "false") {
    shuffle = false;
  }
  else if(string(argv[1]) == "true") {
    shuffle = true;
  }
  else {
    cout << "invalid program usage: invalid first argument" << endl;
    return 1;
  }

  if(argc == 3) {
    std::ifstream savedGame(argv[2]);
    if(!ifile.is_open()) {
      cout << "invalid program usage: can't open input game file" << endl;
      return 1;
    }
    else {
      //continue the game, not sure how to do this
      SkipBoGame game = new SkipBoGame(shuffle, argv[2]);

      while(!game.checkWin()) {
        cout << " >> " >> game.getCurrentPlayer << " turn next" << endl;
        cout << "(p)lay, (s)ave, or (q)uit ? ";
        std::string psq;
        std::cin >> psq;
        if(psq == "q") {
          delete game;
          cout << "thanks for playing" << endl;
          return 0;
        }
        else if(psq == "s") {
          std::string saveFile;
          cout << "save filename: ";
          std::cin >> saveFile;
          game.save(saveFile);
          delete game;
          return 0;
        }
        else if(psq == "p") {
          game.playTurn();
        }
      }
      cout << "GAME OVER - " << game.getCurrentPlayer() << " wins!" << endl;
      delete game;
    }
    return 0;
  }

  if(argc == 5) {
    if(int(argv[3]) > 6 || int(argv[3]) < 2) {
      cout << "invalid program usage: num players must be 2-6" << endl;
      return 1;
    }
    else {
      numPlayers = int(argv[3]);
      cout << "num players is " << numPlayers << endl;
    }

    if((numPlayers == 6 && int(argv[4]) > 20) || (numPlayers <= 5 && int(argv[4]) > 30)) { //not exactly sure its supposed to be 162
      cout << "invalid program usage: bad stock size" << endl;
      return 1;
    }
    else {
      stockSize = int(argv[4]);
      cout << "stock size is " << stockSize << endl;
    }

    std::ifstream deckStartFile(argv[5]);
    if(!deckStartFile.is_open()) {
      cout << "invalid program usage: can't open deck file" << endl;
      return 1;
    }
    else {
      //create a skipbogame object
      SkipBoGame game = new SkipBoGame(shuffle, numPlayers, stockPileSize, argv[5]);
      
      while(!game.checkWin()) {
	cout << " >> " >> game.getCurrentPlayer << " turn next" << endl;
	cout << "(p)lay, (s)ave, or (q)uit ? ";
	std::string psq;
	std::cin >> psq;
	if(psq == "q") {
	  delete game;
	  cout << "thanks for playing" << endl;
	  return 0;
	}
	else if(psq == "s") {
	  std::string saveFile;
	  cout << "save filename: ";
	  std::cin >> saveFile;
	  game.save(saveFile);
	  delete game;
	  return 0;
	}
	else if(psq == "p") {
	  game.playTurn();
	}
      }
      cout << "GAME OVER - " << game.getCurrentPlayer() << " wins!" << endl;
      delete game;
    }
    return 0;
  }
}
