#include <string>

using namespace std;

#ifndef FIRST_HW_RULE_H
#define FIRST_HW_RULE_H

struct Rule {
    int starting_cash;
    int turn_limit;
    int num_players_to_end_game;
    int property_set_mult;
    int num_houses_before_hotel;
    bool must_build_houses_evenly;
    bool put_money_in_free_parking;
    bool auction_properties;
    int salary_mult;
};

struct Rule set_property(struct Rule rules, string line_to_read, int index);
int ExtractRuleInt(string rule);
bool ExtractRuleBool(string rule);

#endif //FIRST_HW_RULE_H
