#include "game.h"
#include "rule.h"
#include "board.h"
#include "game_state.h"
#include <iostream>
#include <fstream>
#include "player.h"

using namespace std;

struct Rule LoadRules(string rule_dir, struct Rule rules);
struct Board LoadBoard(string board_dir);
vector<int> parse_random_file(string rand_dir);
int GetNumberOfPlayers();
vector<Player> CreatePlayers(int num_players, struct Rule rules);

struct GameState SetupGame(string rule_dir, string board_dir, string rand_dir) {

    struct Rule rules;
    rules = LoadRules(rule_dir, rules);

    struct Board board = LoadBoard(board_dir);
    board.random_file = parse_random_file(rand_dir);

    struct GameState gm;
    gm.player_turn_id = 0; // initial always 0
    gm.player_turn_made_move = false;
    gm.board = board;
    gm.rules = rules;
    gm.random_file_index = 0;
    gm.num_moves = 0;

    int num_players = GetNumberOfPlayers();
    gm.num_players = num_players;
    gm.players = CreatePlayers(num_players, rules);

    return gm;
}

struct Rule LoadRules(string rule_dir, struct Rule rules) {

    // Open rule file
    ifstream inFile;
    inFile.open(rule_dir);

    // Check rule file exists otherwise take matters into our own hands...
    if (!inFile) {
        cerr << "Unable to open rule file :(";
        exit(1);
    }

    // Read each line from file into rule struct
    string line_to_read;
    int counter = 0;
    while (getline(inFile, line_to_read)) {
        rules = set_property(rules, line_to_read, counter);
        counter += 1;
    }

    // Close rule file
    inFile.close();

    return rules;
}

struct Board LoadBoard(string board_dir) {

    return LoadCSV(board_dir);
}

vector<int> parse_random_file(string rand_dir) {
    vector<int> arr;

    // Open random file
    ifstream inFile;
    inFile.open(rand_dir);

    // Read each line from file into rule struct
    string line_to_read;
    while (getline(inFile, line_to_read)) {
        if (line_to_read[0] == ' ')
            continue;
        arr.push_back(stoi(line_to_read));
    }

    // Close rule file
    inFile.close();

    return arr;
}

int GetNumberOfPlayers() {

    cout << "How many players will be playing: ";

    int num_players;

    cin >> num_players;

    return num_players;
}

vector<Player> CreatePlayers(int num_players, struct Rule rules) {
    vector<Player> players;

    for (int i = 0; i < num_players; i++) {
        struct Player p = create_player(i, rules);
        players.push_back(p);
    }

    return  players;
}