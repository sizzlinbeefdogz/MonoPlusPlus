#include "player.h"
#include "board.h"

using namespace std;

#ifndef FIRST_HW_GAME_STATE_H
#define FIRST_HW_GAME_STATE_H

struct GameState {
    Board board;
    int num_players;
    vector<Player> players;
    int player_turn_id;
    bool player_turn_made_move;
    Rule rules;
    int num_moves;
    int random_file_index;
};

bool is_game_over(GameState *gm);

void next_player_turn(GameState **gm);

void declare_winners(GameState *gm);

#endif //FIRST_HW_GAME_STATE_H