#include "player.h"
#include "rule.h"
#include "game_state.h"
#include <iostream>

struct Player create_player(int player_id, struct Rule rules) {
    struct Player p;
    p.player_id = player_id;
    p.cash = rules.starting_cash;
    p.board_position = 0;
    p.destroyed = false;
    return p;
}

void player_passed_go(GameState ***gm) {
    int p_id = (**gm)->player_turn_id;

    int raw_go_cash = ((**gm)->board.go.amount_of_cash_gained);

//    int go_mult = ((**gm)->rules.salary_mult);
//    int cash = raw_go_cash * go_mult;

    (**gm)->players.at(p_id).cash += raw_go_cash;

    return;
}

void player_passed_go_mult(GameState ***gm) {
    int p_id = (**gm)->player_turn_id;

    int raw_go_cash = ((**gm)->board.go.amount_of_cash_gained);
    int go_mult = ((**gm)->rules.salary_mult);

    int cash = raw_go_cash * go_mult;

    (**gm)->players.at(p_id).cash += cash;

    return;
}