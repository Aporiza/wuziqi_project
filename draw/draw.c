#include <stdio.h>
#include <stdlib.h>
#include "draw.h"

void clear_screen(){
    system("cls");
}

void print_board(int board[BOARD_SIZE][BOARD_SIZE]){
     //打印顶部的ABC....
     printf("  ");
     for (int i=0;i<BOARD_SIZE;i++){
        printf(" %c",'A'+i);
     }
     printf("\n");
     
     //打印每一行
    for(int i=0;i<BOARD_SIZE;i++){
        printf("%2d",i+1);

        for(int j=0;j<BOARD_SIZE;j++){
            if (board[i][j]==BLACK){
                printf(" X");
            }
            else if (board[i][j]==WHITE){
                printf(" O");

            }
            else{
                printf(" +");
            }
        }

        printf(" %d\n",i+1);
    }
     
    //底部行号
    printf("  ");
     for (int i=0;i<BOARD_SIZE;i++){
        printf(" %c",'A'+i);
     }
     printf("\n");



}