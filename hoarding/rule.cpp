#include "rule.h"
#include <string>

using namespace std;

struct Rule set_property(struct Rule rules, string line_to_read, int index) {

    switch(index) {
        case 0:
            rules.starting_cash = ExtractRuleInt(line_to_read);
            break;
        case 1:
            rules.turn_limit = ExtractRuleInt(line_to_read);
            break;
        case 2:
            rules.num_players_to_end_game = ExtractRuleInt(line_to_read);
            break;
        case 3:
            rules.property_set_mult = ExtractRuleInt(line_to_read);
            break;
        case 4:
            rules.num_houses_before_hotel = ExtractRuleInt(line_to_read);
            break;
        case 5:
            rules.must_build_houses_evenly = ExtractRuleBool(line_to_read);
            break;
        case 6:
            rules.put_money_in_free_parking = ExtractRuleBool(line_to_read);
            break;
        case 7:
            rules.auction_properties = ExtractRuleBool(line_to_read);
            break;
        case 8:
            rules.salary_mult = ExtractRuleInt(line_to_read);
            break;
    }

    return rules;
}

int ExtractRuleInt(string rule) {
    string value = rule.substr(rule.find(": ") + 1);
    return stoi(value);
}

bool ExtractRuleBool(string rule) {
    string value = rule.substr(rule.find(": ") + 1);
    if (value == "Yes") {
        return true;
    }else{
        return false;
    }
}