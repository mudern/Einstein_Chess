//
// Created by 穆琰鑫 on 2023/9/26.
//

#ifndef EINSTEIN_CHESS_CHESS_H
#define EINSTEIN_CHESS_CHESS_H

#include <iostream>
#include <optional>
#include <vector>
#include "PieceAttributes.h"

/*
 * 该类为基础Chess类,用于提供Chess基础功能
 * 该类存储了棋子的阵营,序号,位置.提供了移动与检查移动的方法
 * 该类的构建和析构将在Board类内进行
 */
class Chess{
private:
    //有红蓝两种阵营
    Camp camp;
    //棋子序号1-6
    int serial_num;
    //棋子在棋盘上的位置(1,1)-(5,5)
    std::pair<int,int> position;
    //棋子状态
    bool is_alive= true;
public:
    //构造方法
    Chess(Camp _camp,int _serial_num,std::pair<int,int> _position);
    // Getter和Setter方法
     [[nodiscard]] Camp getCamp() const;
     [[nodiscard]] int getSerialNum() const;
     [[nodiscard]] std::pair<int, int> getPosition() const;
     [[nodiscard]] bool isAlive() const;
     void setIsAlive(bool status);
     void setPosition(const std::pair<int, int> &position);
    //棋子移动方法
    bool move(Move _move_kind);
    bool move(std::pair<int,int> _position);
    //返回预期的移动位置
    std::optional<std::pair<int,int>> getExpectedPosition(Move _move_kind);
    //生成指定阵营的指定棋子的所有走法
    std::vector<MoveChoice> generate_move_choice();
    //重新游玩方法
    void replay(std::pair<int,int> pos);

private:
    /*
     * 检测移动是否合法,可以接收移动类型和位置两种参数进行判断
     * 如果有棋子需要移动前做判断,且接收一个移动类型参数,需要使用getExpectedPosition方法
     * 如果有棋子需要移动前做判断,且接收一个位置参数,需要使用接收位置的canMove方法
     */
    bool canMove(Move _move_kind);
    bool canMove(std::pair<int,int> _position);
    //传入将要移动位置,返回移动类型
    std::optional<Move> getMoveKind(std::pair<int,int> _position);
};


#endif //EINSTEIN_CHESS_CHESS_H
