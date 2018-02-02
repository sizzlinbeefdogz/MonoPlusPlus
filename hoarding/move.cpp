#include "move.h"
#include "game_state.h"
#include <iostream>
#include <vector>
#include "dice.h"
#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include "player.h"

void print_action_options(int player_id, GameState gm);
int get_player_action();
int get_player_to_inspect(struct GameState gm);
void inspect_player(struct GameState *gm, int player_id);
void destroy_player(struct GameState **gm);
Property roll_dice_and_move_player(GameState **gm);
bool offer_to_buy_property(GameState **gm, Property p);
bool player_needs_to_pay_rent(GameState **gm, Property landed_on, int player_id);
void transfer_property_and_cash_from_player_to_player(GameState ***gm, int player1_id, int player2_id);
bool can_player_afford_to_buy_property(Player player, Property property);
void get_owner_of_property(GameState gm, Property p, Player *owner);
void check_if_owner_owns_whole_set(GameState gm, Property p, Player *owner, bool *player_owns_all_sets);

void make_move(struct GameState *gm, struct Move *move) {
    int action = move->action_id;

    if (action == 1) {
        // Action 1 either roll dice or end move
        if (gm->player_turn_made_move == true) {
            // End turn
            next_player_turn(&gm);
            move->move_ended = true;
            gm->num_moves += 1;
        }else{
            // player ID
            int player_id = gm->player_turn_id;

            // Roll dice & move player
            Property landed_on = roll_dice_and_move_player(&gm);

            // Landed on go, let's exit this
            if (landed_on.name == gm->board.go.name) {
                return;
            }

            // Check if player owes rent or not
            bool rent = player_needs_to_pay_rent(&gm,landed_on, player_id);
            if (!rent) {

                // Check if player can afford property
                bool afford = can_player_afford_to_buy_property(gm->players.at(player_id), landed_on);
                if (!afford) {
                    return;
                }

                // Offer to buy property
                offer_to_buy_property(&gm, landed_on);
            }else if (gm->players.at(player_id).cash < 0) {

                // Player went bankrupt
                destroy_player(&gm);
                next_player_turn(&gm);
                move->move_ended = true;
                gm->num_moves += 1;
                return;
            }
        }
    }else if (action == 2) {
        // Inspect player
        int player_id = get_player_to_inspect(*gm);
        inspect_player(gm, player_id);
    }else{
        // Leave game
        destroy_player(&gm);
        next_player_turn(&gm);
        move->move_ended = true;
        gm->num_moves += 1;
    }

    return;
}

bool can_player_afford_to_buy_property(Player player, Property property) {

    if (player.cash >= property.property_cost) {
        return true;
    }

    cout << "Player " << player.player_id;
    cout << " you do not have enough money to purchase ";
    cout << property.name;
    cout << endl;

    cout << property.name << " costs $" << property.property_cost << ", but you only have $" << player.cash;
    cout << endl;

    return false;
}

void transfer_property_and_cash_from_player_to_player(GameState ***gm, int player1_id, int player2_id) {
    // Transfer cash
    (**gm)->players.at(player2_id).cash += (**gm)->players.at(player1_id).cash;

    // Transfer property
    for (Property p: (**gm)->players.at(player1_id).properties) {
        (**gm)->players.at(player2_id).properties.push_back(p);
    }
}

void destroy_player(struct GameState **gm) {
    int player_to_leave = (*gm)->player_turn_id;
    (*gm)->players.at(player_to_leave).destroyed = true;
}

Property roll_dice_and_move_player(GameState **gm) {

    int player_id = (*gm)->player_turn_id;
    int player_pos = (*gm)->players.at(player_id).board_position;

    int num_moves = roll_dice_and_get_moves(&gm);

    cout << "You rolled a " << num_moves << "!" << endl;

    int new_pos = player_pos + num_moves;

    int num_prop = (*gm)->board.properties.size() + 1;

    int num_times_pass_go = new_pos / (num_prop);

    for (int i = 0; i < num_times_pass_go; i++) {
        if (i == (num_times_pass_go-1)) {
            break;// break if it's last one, then decide in move for last to either mul or
        }
        player_passed_go(&gm);
    }

    while(new_pos >= num_prop) {
        new_pos -= num_prop;
    }

    (*gm)->players.at(player_id).board_position = new_pos;
    (*gm)->player_turn_made_move = true;

    if (new_pos == 0) {
        if (num_times_pass_go != 0) {
            player_passed_go_mult(&gm);
        }
        Property p;
        p.name = (*gm)->board.go.name;
        return p;
    }else if (num_times_pass_go != 0) {
        player_passed_go(&gm);
    }

    Property p = (*gm)->board.properties.at(new_pos-1);
    return p;
}

bool offer_to_buy_property(GameState **gm, Property p) {
    // Deal with buying
    cout << "Player " << (*gm)->player_turn_id << " would you like to buy ";
    cout << p.name << " for $" << p.property_cost << "?" << endl;
    cout << "The rent on this property is $" << p.rent << endl;
    cout << "You currently have $" << (*gm)->players.at((*gm)->player_turn_id).cash << endl;
    cout << "Y for yes, N for no: ";
    string buy_property;
    cin >> buy_property;
    if (tolower(buy_property[0]) == 'y') {
        (*gm)->players.at((*gm)->player_turn_id).cash -= p.property_cost;
        (*gm)->players.at((*gm)->player_turn_id).properties.push_back(p);
        return true;
    }else{
        return false;
    }
}

int get_player_to_inspect(struct GameState gm) {
    cout << "Which player would you like to inspect?" << endl;

    for (Player p: gm.players) {
        if (p.destroyed) {
            continue;
        }
        cout << p.player_id << " for Player " << p.player_id << endl;
    }

    cout << "Your choice: ";

    int player_id;
    cin >> player_id;
    return player_id;
}

void print_property_name_set(vector<Property> properties, int set_id) {

    // get names
    vector <string> names;
    for (Property p : properties) {
        if (p.set_id == set_id) {
            names.push_back(p.name);
        }
    }

    // sort names
    sort(names.begin(), names.end());

    // display names
    string separator = " | ";
    int j = 0;
    for (string name : names) {
        if (j > 0) {
            cout << separator;
        }
        cout << name;
        j += 1;
    }
}

void inspect_player(struct GameState *gm, int player_id) {

    cout << "Player " << player_id << endl;

    cout << "  Cash: $" << gm->players[player_id].cash << endl;

    cout << "  Properties owned" << endl;

    // Create set ids
    vector<int> set_ids;
    for (Property p:gm->board.properties) {
        if(!(find(set_ids.begin(), set_ids.end(), p.set_id) != set_ids.end())) {
            set_ids.push_back(p.set_id);
        }
    }

    for (int i:set_ids) {
        cout << "  " << i << ": ";

        print_property_name_set(gm->players.at(player_id).properties, i);

        cout << endl;
    }

    return;
}

struct Move get_move(struct GameState *gm) {

    print_action_options(gm->player_turn_id, (*gm));
    int action = get_player_action();

    struct Move move;
    move.move_ended = false;
    move.action_id = action;

    return move;
}

void print_action_options(int player_id, GameState gm) {
    cout << "Player " << player_id << " please choose an action" << endl;

    if (gm.player_turn_made_move == false) {
        cout << "1: Roll Dice" << endl;
    }else{
        cout << "1: End Turn" << endl;
    }

    cout << "2: Inspect Player" << endl << "3: Leave Game" << endl;
    cout << "Your action: ";
}

int get_player_action() {
    int action;
    cin >> action;
    return action;
}

bool player_needs_to_pay_rent(GameState **gm, Property landed_on, int player_id) {

    Player owner;
    owner.player_id = 99997; // sudo id
    get_owner_of_property((**gm), landed_on, &owner);

    if (owner.player_id != 99997) { // there a owner

        // property is owned by a owner
        if (owner.player_id != player_id) {

            // deduct rent if the owner is not itself
            int rent = landed_on.rent;

            // check if set is owned buy owner
            bool all_sets = false;

            check_if_owner_owns_whole_set((**gm), landed_on, &owner, &all_sets);

            if (all_sets) {
                //cout << endl << "Property multiplier activated!" << endl;
                rent = (landed_on.rent * (**gm).rules.property_set_mult); // update rent with multiplier
            }

            int new_cash = (*gm)->players.at(player_id).cash - rent;

            (*gm)->players.at(player_id).cash -= rent;
            (*gm)->players.at(owner.player_id).cash += rent;

            // Player went bankrupt
            if (new_cash < 0) {
                transfer_property_and_cash_from_player_to_player(&gm, player_id, owner.player_id);
                cout << "Player " << player_id << " went bankrupt to Player " << owner.player_id;
                cout << endl;
            }else{
                cout << "Player " << player_id << " payed Player " << owner.player_id << " $" << rent;
                cout << " for landing on " << landed_on.name << endl;
            }
        }

        return true;
    }

    return false;
}

void get_owner_of_property(GameState gm, Property p, Player *owner) {
    // See who the owner is
    for (Player player:gm.players) {
        for (Property prop:player.properties) {
            if (prop.set_id == p.set_id && prop.intraset_id == p.intraset_id && prop.name == p.name) {
                // Property is owned by player
                if (!player.destroyed) {
                    (*owner) = player;
                }
            }
        }
    }
}

void check_if_owner_owns_whole_set(GameState gm, Property p, Player *owner, bool *player_owns_all_sets) {

    int set_id_to_count = p.set_id;

    int num_prop_in_set = 0;
    int num_prop_owned = 0;

    for (Property prop:gm.board.properties) {
        if (prop.set_id == set_id_to_count) {
            num_prop_in_set += 1;
        }
    }

    for (Property prop: owner->properties) {
        if (prop.set_id == set_id_to_count) {
            num_prop_owned += 1;
        }
    }

    if (num_prop_in_set == num_prop_owned) {
        (*player_owns_all_sets) = true;
    }else{
        (*player_owns_all_sets) = false;
    }

}