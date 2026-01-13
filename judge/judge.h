#ifndef JUDGE_H
#define JUDGE_H

#include "config.h"

int check_win(int board[BOARD_SIZE][BOARD_SIZE], Pos lastPos, int color);

int is_forbidden_move(int board[BOARD_SIZE][BOARD_SIZE], Pos lastPos, int color);

#endif