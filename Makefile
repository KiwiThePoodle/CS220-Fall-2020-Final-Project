#
#

CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

skipbo: main.o SkipBoGame.o
	$(CC) -o skipbo main.o SkipBoGame.o

main.o: main.cpp SkipBoGame.h
	$(CC) $(CFLAGS) -c main.cpp

SkipBoGame.o: SkipBoGame.cpp SkipBoGame.h DrawPile.h Pile.h Card.h Player.h FaceUpPile.h Hand.h 
	$(CC) $(CFLAGS) -c SkipBoGame.cpp

.PHONY: clean

clean:
	rm -f *.o skipbo *~
