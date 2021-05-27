OBJS = Tile.o Node.o LinkedList.o qwirkle.o Menu.o GameManager.o TileBag.o GameState.o Player.o Board.o
DEPS := $(OBJS:.o=.d)
CXX = g++
CFLAGS = -Wall -Werror -std=c++14 -g -O

all: qwirkle

clean:
	rm -rf qwirkle *.o *.dSYM 
	rm -rf *.d

qwirkle: $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $^

-include $(DEPS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -MMD -c -o $@ $<
