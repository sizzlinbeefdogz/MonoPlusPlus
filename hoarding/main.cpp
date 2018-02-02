#include <iostream>
#include "game.h"
#include "board.h"
#include "game_state.h"
#include "move.h"
using namespace std;

int main(int argc, char** argv) {

    struct GameState game_state = SetupGame(argv[1], argv[2], argv[3]);
    Move move;

    while(!is_game_over(&game_state)) {
        do {

            DisplayBoard(&game_state);

            move = get_move(&game_state);

            make_move(&game_state, &move);

        }while(!move.move_ended);
    }

    DisplayBoard(&game_state);
    declare_winners(&game_state);
//    delete_game_state(&game_state);
    return 0;
}