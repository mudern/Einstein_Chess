//
// Created by 穆琰鑫 on 2023/9/26.
//

#ifndef Einstein_Chess_BOARD_H
#define Einstein_Chess_BOARD_H

#include <iostream>
#include <vector>
#include "Chess.h"

class Board {
private:
    //使用Vector存储所有棋子
    std::vector<Chess> chess_red_collection;
    std::vector<Chess> chess_blue_collection;
public:
    //默认无参初始化棋盘
    Board();
    //传入红蓝两个阵营棋子位置的Vector初始化棋盘
    Board(std::vector<int> red,std::vector<int> blue);
    //返回棋子供上层操作
    Chess getChess(Camp _camp,int _serial_num);
private:
    //作为两个构造函数调用的基函数
    void initializeBoard(std::vector<int> red,std::vector<int> blue);
};


#endif //Einstein_Chess_BOARD_H
