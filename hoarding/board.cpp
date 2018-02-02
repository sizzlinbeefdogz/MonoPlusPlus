#include "board.h"
#include <iostream>
#include <fstream>
#include "property.h"
#include <string>
#include <sstream>
#include <iomanip>
#include "game_state.h"
#include "player.h"

using namespace std;

int max_character_in_name(struct Board board);
void print_string_name_for_board(struct Board board, int i);

vector<string> parse_comma_string(string string_to_parse) {
    stringstream ss(string_to_parse);
    vector<string> result;

    while( ss.good() ) {
        string sub_string;
        getline( ss, sub_string, ',' );
        result.push_back( sub_string );
    }

    return  result;
}

struct Board LoadCSV(string board_dir) {

    // Board struct
    struct Board board;

    // Open CSV file
    ifstream inFile;
    inFile.open(board_dir);

    string line_to_read;
    int counter = 0;
    while (getline(inFile, line_to_read)) {
        counter += 1;

        // Skip first few unimportant lines
        if (counter < 5) {
            continue;
        }

        line_to_read = line_to_read.substr(line_to_read.find(",") + 1);

        // Go property
        if (counter == 5) {
            // Go cash amount
            string go_cash = line_to_read.substr(0, line_to_read.find(","));

            // Go name
            string name = line_to_read;
            name.erase(0, line_to_read.find(",") + 1);
            name = name.substr(0, name.find(",,,,,,,"));

            // Chuck it all in a struct
            struct GO_space go_space;
            go_space.amount_of_cash_gained = stoi(go_cash);
            go_space.name = name;
            board.go = go_space;

            continue;
        }

        struct Property prop;
        vector<string> array_of_strings = parse_comma_string(line_to_read);
        prop.set_id = stoi(array_of_strings[0]);
        prop.intraset_id = stoi(array_of_strings[1]);
        prop.name = array_of_strings[2];
        prop.property_cost = stoi(array_of_strings[3]);
        prop.house_cost = stoi(array_of_strings[4]);
        prop.hotel_cost = stoi(array_of_strings[5]);
        prop.rent = stoi(array_of_strings[6]);
        prop.rent_with_house = stoi(array_of_strings[7]);
        prop.rent_with_hotel = stoi(array_of_strings[8]);
        board.properties.push_back(prop);
    }

    // Close rule file
    inFile.close();

    return board;
}

void DisplayBoard(struct GameState *gm) {
    int x = gm->board.properties.size() + 1; // +1 for go file

    for (int i = 0; i < x; i++) {
        // Print name
        print_string_name_for_board(gm->board, i);

        // Print any players at position
        vector<int> player_pos;
        for (Player p : gm->players) {

            if (p.destroyed) {
                continue;
            }

            if (p.board_position == i) {

                bool first = true;

                for (int pos : player_pos) {
                    if (pos == i) {
                        first = false;
                    }
                }

                if (first == true) {
                    cout << "     ";
                }else{
                    cout << " ";
                }

                cout << p.player_id;

                player_pos.push_back(i);
            }
        }

        // End with new line
        cout << endl;
    }
}

void print_string_name_for_board(struct Board board, int i) {
    int max_char = max_character_in_name(board);

    // Display name
    int current_name_length = 0;

    cout << i;
    cout << " | ";

    if (i == 0) {
        cout << board.go.name;
        current_name_length = board.go.name.length();
    } else {
        cout << board.properties.at(i - 1).name;
        current_name_length = board.properties.at(i - 1).name.length();
    }

    cout << setw(max_char - current_name_length + 2) << right << " |";

    return;
}


/** Returns the max amount of chars from properities and go space in a board */
int max_character_in_name(struct Board board) {
    int char_length = 0;

    int x = board.properties.size() + 1; // +1 for go file
    for (int i = 0; i < x; i++) {
        int temp_length = 0;

        if (i == 0) {
            temp_length = board.go.name.length();
        }else{
            temp_length = board.properties.at(i-1).name.length();
        }

        if (temp_length > char_length) {
            char_length = temp_length;
        }
    }

    return  char_length;
}