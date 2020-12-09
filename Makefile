#
#

CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

skipbo: main.o SkipBoGame.o Card.o DrawPile.o FaceUpPile.o Hand.o Pile.o Player.o
	$(CC) -o skipbo main.o SkipBoGame.o Card.o DrawPile.o FaceUpPile.o Hand.o Player.o

main.o: main.cpp SkipBoGame.h
	$(CC) $(CFLAGS) -c main.cpp

SkipBoGame.o: SkipBoGame.cpp SkipBoGame.h DrawPile.h Pile.h Card.h Player.h FaceUpPile.h Hand.h 
	$(CC) $(CFLAGS) -c SkipBoGame.cpp

Card.o: Card.cpp Card.h
	$(CC) $(CFLAGS) -c Card.cpp
	
DrawPile.o: DrawPile.cpp DrawPile.h Card.h Pile.h
	$(CC) $(CFLAGS) -c DrawPile.cpp
	
FaceUpPile.o: FaceUpPile.cpp FaceUpPile.h Card.h Pile.h
	$(CC) $(CFLAGS) -c FaceUpPile.cpp
	
Hand.o: Hand.cpp Hand.h Card.h Pile.h
	$(CC) $(CFLAGS) -c Hand.cpp
	
Pile.o: Pile.cpp Pile.h Card.h
	$(CC) $(CFLAGS) -c Pile.cpp
	
Player.o: Player.cpp Player.h Card.h Pile.h DrawPile.h FaceUpPile.h Hand.h
	$(CC) $(CFLAGS) -c Player.cpp

.PHONY: clean

clean:
	rm -f *.o skipbo *~
