#ifndef CONFIG_H
#define CONFIG_H


// 五子棋项目全局配置文件

 

//  棋盘基础参数
#define BOARD_SIZE 15  // 棋盘大小：15x15
#define WIN_COUNT  5   // 连成 5 子即胜利

//  棋子状态定义 
// 使用数字表示状态，便于在数组中存储
#define EMPTY 0  // 空位
#define BLACK 1  // 黑子（通常先手）
#define WHITE 2  // 白子

// 游戏模式定义 
#define MODE_PVP 1  // 人人对战
#define MODE_PVE 2  // 人机对战

//  通用数据结构 
// 定义一个坐标结构体，方便在函数之间传递“落子位置”
typedef struct {
    int row; // 行坐标 (0-14)
    int col; // 列坐标 (0-14)
} Pos;
//禁手
#define NOT_FORBIDDEN 0
#define FORBIDDEN_33  1
#define FORBIDDEN_44  2
#define FORBIDDEN_6   3

#endif 