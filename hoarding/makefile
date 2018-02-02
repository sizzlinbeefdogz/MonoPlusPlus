hoarding.out: main.o board.o dice.o game.o game_state.o move.o player.o property.o random.o rule.o
	g++ -g -Wall -Werror -std=c++14 -o hoarding.out main.o board.o dice.o game.o game_state.o move.o player.o property.o random.o rule.o

main.o: main.cpp game.h board.h game_state.h
	g++ -g -Wall -Werror -std=c++14 -c main.cpp 
board.o: board.cpp board.h game_state.h
	g++ -g -Wall -Werror -std=c++14 -c board.cpp
dice.o: dice.cpp dice.h game_state.h
	g++ -g -Wall -Werror -std=c++14 -c dice.cpp
game.o: game.cpp game.h rule.h board.h game_state.h
	g++ -g -Wall -Werror -std=c++14 -c game.cpp
game_state.o: game_state.cpp game_state.h
	g++ -g -Wall -Werror -std=c++14 -c game_state.cpp
move.o: move.cpp move.h game_state.h dice.h
	g++ -g -Wall -Werror -std=c++14 -c move.cpp
player.o: player.cpp player.h game_state.h
	g++ -g -Wall -Werror -std=c++14 -c player.cpp
rule.o: rule.cpp rule.h
	g++ -g -Wall -Werror -std=c++14 -c rule.cpp
clean:
	rm -f *.o *.out