//
// Created by 穆琰鑫 on 2023/9/26.
//

#ifndef Einstein_Chess_BOARD_H
#define Einstein_Chess_BOARD_H

#include <iostream>
#include <vector>
#include <optional>
#include "Chess.h"

/*
 * 该类为基础Board类,用于提供Board基础功能
 * 该类存储所有的棋子并且保存棋子判断逻辑
 * 在使用时,棋子无需显式构建,构建棋盘时将会构建对应棋子
 */
class Board {
private:
    //使用Vector存储所有棋子
    std::vector<Chess> chess_red_collection;
    std::vector<Chess> chess_blue_collection;
    std::optional<Camp> winner=std::nullopt;
public:
    //默认无参初始化棋盘,按照较优的方式构建棋盘
    Board();
    //传入红蓝两个阵营棋子位置的Vector初始化棋盘
    Board(std::vector<int> red,std::vector<int> blue);
    // Getter 方法
    [[nodiscard]] const std::vector<Chess> &getChessRedCollection() const;
    [[nodiscard]] const std::vector<Chess> &getChessBlueCollection() const;
    //返回指定的棋子供上层操作
    Chess getChess(Camp _camp,int _serial_num);
    //传入指定的棋子和移动方向进行移动,可以移动返回true,不能移动返回false
    bool moveChess(Camp _camp,int _serial_num,Move _move_kind);
    //传入指定的棋子和移动方向进行移动,可以移动返回true,不能移动返回false
    bool moveChess(Camp _camp,int _serial_num,std::pair<int,int> _position);
    //检测棋子移动后是否会重叠
    std::optional<Chess> isOverlap(std::pair<int,int> _expected_position);
    std::optional<Camp> hasWinner();
private:
    //作为两个构造函数调用的基函数
    void initializeBoard(std::vector<int> red,std::vector<int> blue);
};


#endif //Einstein_Chess_BOARD_H
