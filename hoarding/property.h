#include <string>

using namespace std;

#ifndef FIRST_HW_PROPERTY_H
#define FIRST_HW_PROPERTY_H

struct Property {
    string name;
    int property_cost;
    int hotel_cost;
    int house_cost;
    int rent;
    int rent_with_house;
    int rent_with_hotel;
    int set_id;
    int intraset_id;
};

struct GO_space {
    string name;
    int amount_of_cash_gained;
};

#endif //FIRST_HW_PROPERTY_H
