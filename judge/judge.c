#include "judge.h"
#include <stdio.h>

// 1. 定义方向向量（水平、垂直、左斜、右斜）
static int dr[] = {0, 1, 1, 1};//行
static int dc[] = {1, 0, 1, -1};//列




 //基础扫描：计算在 (r, c) 落子后，某个方向上的连续同色棋子总数
 
 int count_continuous(int board[BOARD_SIZE][BOARD_SIZE], int r, int c, int dir, int color) {
    int count = 1;
    // 正向探测
    int nr = r + dr[dir], nc = c + dc[dir];
    while (nr >= 0 && nr < BOARD_SIZE && nc >= 0 && nc < BOARD_SIZE && board[nr][nc] == color) {
        count++; nr += dr[dir]; nc += dc[dir];
    }
    // 反向探测
    nr = r - dr[dir]; nc = c - dc[dir];
    while (nr >= 0 && nr < BOARD_SIZE && nc >= 0 && nc < BOARD_SIZE && board[nr][nc] == color) {
        count++; nr -= dr[dir]; nc -= dc[dir];
    }
    return count;
}


// 判定活四：四个子且两端均为空位
 
 int is_live_four(int board[BOARD_SIZE][BOARD_SIZE], int r, int c, int dir, int color) {
    int count = 1;
    // 正向搜寻
    int nr = r + dr[dir], nc = c + dc[dir];
    while (nr >= 0 && nr < BOARD_SIZE && nc >= 0 && nc < BOARD_SIZE && board[nr][nc] == color) { 
        count++; nr += dr[dir]; nc += dc[dir];
     }
    int end1_r = nr, end1_c = nc;

    // 反向搜寻
    nr = r - dr[dir]; nc = c - dc[dir];
    while (nr >= 0 && nr < BOARD_SIZE && nc >= 0 && nc < BOARD_SIZE && board[nr][nc] == color) { 
        count++; nr -= dr[dir]; nc -= dc[dir]; 
    }
    int end2_r = nr, end2_c = nc;

    if (count == 4) {
        // 两端必须都在界内且为空
        if (end1_r >= 0 && end1_r < BOARD_SIZE && end1_c >= 0 && end1_c < BOARD_SIZE && board[end1_r][end1_c] == EMPTY &&end2_r >= 0 && end2_r < BOARD_SIZE && end2_c >= 0 && end2_c < BOARD_SIZE && board[end2_r][end2_c] == EMPTY) {
            return 1;
        }
    }
    return 0;
}

// 判定在该方向是否可能成“五”（用于四四禁手判定）

int has_five_opportunity(int board[BOARD_SIZE][BOARD_SIZE], int r, int c, int dir, int color) {
    // 在该方向前后各 4 格范围内模拟落子
    for (int i = -4; i <= 4; i++) {
        int nr = r + i * dr[dir], nc = c + i * dc[dir];
        if (nr >= 0 && nr < BOARD_SIZE && nc >= 0 && nc < BOARD_SIZE && board[nr][nc] == EMPTY) {
            board[nr][nc] = color; // 模拟
            if (count_continuous(board, nr, nc, dir, color) >= 5) {
                board[nr][nc] = EMPTY; // 还原
                return 1;
            }
            board[nr][nc] = EMPTY;
        }
    }
    return 0;
}

// 判定在该方向是否可能成“活四”（用于三三禁手判定）

 int has_live_four_opportunity(int board[BOARD_SIZE][BOARD_SIZE], int r, int c, int dir, int color) {
    for (int i = -4; i <= 4; i++) {
        int nr = r + i * dr[dir], nc = c + i * dc[dir];
        if (nr >= 0 && nr < BOARD_SIZE && nc >= 0 && nc < BOARD_SIZE && board[nr][nc] == EMPTY) {
            board[nr][nc] = color;
            if (is_live_four(board, nr, nc, dir, color)) {
                board[nr][nc] = EMPTY;
                return 1;
            }
            board[nr][nc] = EMPTY;
        }
    }
    return 0;
}

//main函数需要调用的部分,前面的写好这里就简单了

int check_win(int board[BOARD_SIZE][BOARD_SIZE], Pos lastPos, int color) {
    for (int i = 0; i < 4; i++) {
        int count = count_continuous(board, lastPos.row, lastPos.col, i, color);
        if (color == WHITE) {
            if (count >= 5) return 1; // 白棋没有禁手，5个及以上都算赢
        } else {
            if (count == 5) return 1; // 黑棋必须恰好5个才算赢（6个算长连禁手）
        }
    }
    return 0;
}


int is_forbidden_move(int board[BOARD_SIZE][BOARD_SIZE], Pos lastPos, int color) {
    if (color == WHITE) return NOT_FORBIDDEN; // 只有黑棋有禁手

    int r = lastPos.row, c = lastPos.col;

    // 1. 长连禁手判定 (FORBIDDEN_6)
    for (int i = 0; i < 4; i++) {
        if (count_continuous(board, r, c, i, color) > 5) return FORBIDDEN_6;
    }

    // 2. 四四禁手判定 (FORBIDDEN_44)
    int four_count = 0;
    for (int i = 0; i < 4; i++) {
        if (has_five_opportunity(board, r, c, i, color)) four_count++;
    }
    if (four_count >= 2) return FORBIDDEN_44;

    // 3. 三三禁手判定 (FORBIDDEN_33)
    int live_three_count = 0;
    for (int i = 0; i < 4; i++) {
        if (has_live_four_opportunity(board, r, c, i, color)) live_three_count++;
    }
    if (live_three_count >= 2) return FORBIDDEN_33;

    return NOT_FORBIDDEN;
}