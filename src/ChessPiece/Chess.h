//
// Created by 穆琰鑫 on 2023/9/26.
//

#ifndef EINSTEIN_CHESS_CHESS_H
#define EINSTEIN_CHESS_CHESS_H

#include <iostream>
#include "PieceAttributes.h"

class Chess{
private:
    //有红蓝两种阵营
    Camp camp;
    //棋子序号1-6
    int serial_num;
    //棋子在棋盘上的位置(1,1)-(5,5)
    std::pair<int,int> position;
public:
    //构造方法
    Chess(Camp _camp,int _serial_num,std::pair<int,int> _position);
    // Getter 方法
    [[nodiscard]] Camp getCamp() const;
    [[nodiscard]] int getSerialNum() const;
    [[nodiscard]] std::pair<int, int> getPosition() const;
    //棋子移动方法
    bool move(Move _move_kind);
    //检测移动是否合法
    bool canMove(Move _move_kind);
    //返回预期的移动位置
    std::pair<int,int> getExpectedPosition(Move _move_kind);
};


#endif //EINSTEIN_CHESS_CHESS_H
