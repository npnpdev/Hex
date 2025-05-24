#ifndef AISD_PROJEKT2_HEX_CONSTANTS_H
#define AISD_PROJEKT2_HEX_CONSTANTS_H

#include "vector"
#include <string>
#include <array>
#include "cmath"

using namespace std;

#define numOfQueries 15

const char redPlayer = 'r';
const char bluePlayer = 'b';
const char nullPlayer = 'n';
const int MAX_SIZE = 11;

const array<string, numOfQueries> queries = {
        "BOARD_SIZE",
        "PAWNS_NUMBER",
        "IS_BOARD_CORRECT",
        "IS_GAME_OVER",
        "IS_BOARD_POSSIBLE",
        "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT",
        "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT",
        "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT",
        "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT",
        "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT",
        "CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT",
        "CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT",
        "CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT",
};

#endif //AISD_PROJEKT2_HEX_CONSTANTS_H