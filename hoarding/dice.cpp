#include "dice.h"
#include <iostream>
#include <random>
#include "game_state.h"

using namespace std;

int roll_dice_and_get_moves(GameState ***gm) {

    unsigned int index = (**gm)->random_file_index;
    int diceOne = 0;
    int diceTwo = 0;

    if (index > (**gm)->board.random_file.size()) {
        index -= (**gm)->board.random_file.size();
    }

    diceOne = (**gm)->board.random_file.at(index);
    (**gm)->random_file_index++;
    diceTwo = (**gm)->board.random_file.at(index+1);
    (**gm)->random_file_index++;


    return ((diceOne % 6) + 1) + ((diceTwo % 6) + 1);
}