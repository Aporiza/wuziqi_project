#include<stdio.h>
#include"config.h"//<>去系统库里查找，是犯法的
#include"draw.h"
#include"judge.h"
#include <stdlib.h>//system


//转换函数，坐标转换为数组
int input_to_pos(char *input,Pos *p){
    char col_char;
    int row_num;
    if (sscanf(input, "%c%d", &col_char, &row_num) != 2){//scanf是错误的
        return 0;//wrong
    }
    if (col_char<='z'&&col_char>='a'){
        col_char+='A'-'a';
    }//统一大写
    p->col=col_char-'A';
    p->row=row_num-1;
    if (p->col < 0 || p->col >= BOARD_SIZE || p->row < 0 || p->row >= BOARD_SIZE) {
        return 0; // 超出棋盘范围
    }

    return 1; // 转换成功

}

int main() {
    system("chcp 65001");//UTF-8
    int board[BOARD_SIZE][BOARD_SIZE] = {0};
    int currentPlayer = BLACK;
    char input_str[10];
    Pos nextMove;

    while (1) {
        clear_screen();
        print_board(board);

        printf("\n%s 方落子 (请输入如 H8): ", (currentPlayer == BLACK ? "黑" : "白"));
        scanf("%s", input_str);

        // 调用转换函数
        if (input_to_pos(input_str, &nextMove)) {
            // 检查该位置是否已经有子
            if (board[nextMove.row][nextMove.col] == EMPTY) {
                board[nextMove.row][nextMove.col] = currentPlayer;
            // 此时应该判断胜负
                
                if (check_win(board, nextMove, currentPlayer)) {
                     clear_screen();
                     print_board(board);
                     printf("\n恭喜！%s 获胜！\n", (currentPlayer == BLACK ? "黑棋" : "白棋"));
                      break; // 跳出 while 循环，结束游戏
                     }
                // 如果是黑棋，判断是否触发禁手
                if (currentPlayer == BLACK) {
                    int forbiddenType = is_forbidden_move(board, nextMove, BLACK);
                    if (forbiddenType != NOT_FORBIDDEN) {
                        // 触发禁手，强行撤回落子
                        board[nextMove.row][nextMove.col] = EMPTY;
                        
                        // 给出具体的错误提示
                        if (forbiddenType == FORBIDDEN_33) printf("\n【禁手】黑棋三三禁手！请重新落子。\n");
                        else if (forbiddenType == FORBIDDEN_44) printf("\n【禁手】黑棋四四禁手！请重新落子。\n");
                        else if (forbiddenType == FORBIDDEN_6) printf("\n【禁手】黑棋长连禁手！请重新落子。\n");
                        
                        printf("按回车键继续...");
                        getchar(); getchar(); 
                        continue; // 跳过换人逻辑，黑棋重新输入
                    }
                }


                // 交换选手
                currentPlayer = (currentPlayer == BLACK ? WHITE : BLACK);
            } 
            else {
                printf("错误：该位置已有棋子！按回车重试...");
                getchar(); getchar();//清理缓冲
            }
        } else {
            printf("错误：无效坐标！格式应为 字母+数字（如 A1）。按回车重试...");
            getchar(); getchar();
        }
    }
    return 0;
}
    

