#include<vector>
#include "property.h"
#include "rule.h"

using namespace std;

#ifndef FIRST_HW_PLAYER_H
#define FIRST_HW_PLAYER_H

struct Player {
    int player_id;
    int board_position;
    int cash;
    bool destroyed;
    vector<int> properties_owned_per_set;
    vector<Property> properties;
};

struct Player create_player(int player_id, struct Rule rules);
void player_passed_go(struct GameState ***gm);
void player_passed_go_mult(struct GameState ***gm);

#endif //FIRST_HW_PLAYER_H
