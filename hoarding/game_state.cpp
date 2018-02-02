#include "game_state.h"
#include <iostream>
#include "player.h"

bool is_game_over(struct GameState *gm) {

    int num_players = 0;

    for (Player p: gm->players) {
        if (!p.destroyed) {
            num_players += 1;
        }
    }

    if (num_players <= gm->rules.num_players_to_end_game) {
        return true;
    }

    if (gm->rules.turn_limit != -1) {
        if (gm->rules.turn_limit <= gm->num_moves) {
            return true;
        }
    }

    return false;
}

void next_player_turn(GameState **gm) {

    // Important!
    (*gm)->player_turn_made_move = false;

    Player old_player = (*gm)->players.at((*gm)->player_turn_id);

    // Handle if next player's turn is above current player
    int index = 0;
    for (Player p:(*gm)->players) {
        if (p.destroyed == true) {
            continue;
        }

        if (p.player_id > old_player.player_id) {
            (*gm)->player_turn_id = p.player_id;
            return;
        }

        index +=1;
    }

    // Handle if next players turn is behind current player
    // We restart searching the array and want the next avaible player
    for (Player p:(*gm)->players) {

        if (p.destroyed == true) {
            continue;
        }

        (*gm)->player_turn_id = p.player_id;
        break;
    }

    return;
}

void declare_winners(GameState *gm) {
    cout << "The winners are" << endl;
    for (Player p: gm->players) {
        if (p.destroyed) {
            continue;
        }
        cout << "Player " << p.player_id << endl;
    }
}