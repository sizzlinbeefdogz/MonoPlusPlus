#include "property.h"
#include <vector>
#include <string>

using namespace std;

#ifndef FIRST_HW_BOARD_H
#define FIRST_HW_BOARD_H

struct Board {
    vector<Property> properties;
    vector<int> random_file;
    GO_space go;
};

struct Board LoadCSV(string board_dir);

void DisplayBoard(struct GameState *gm);

#endif //FIRST_HW_BOARD_H
