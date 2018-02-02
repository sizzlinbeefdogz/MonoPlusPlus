#ifndef FIRST_HW_MOVE_H
#define FIRST_HW_MOVE_H

struct Move {
    int action_id;
    bool move_ended;
    bool dice_rolled;
};

struct Move get_move(struct GameState *gm);
void make_move(struct GameState *gm, struct Move *move);



#endif //FIRST_HW_MOVE_H
