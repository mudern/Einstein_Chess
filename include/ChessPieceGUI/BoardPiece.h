//
// Created by 穆琰鑫 on 2023/10/17.
//

#ifndef EINSTEIN_CHESS_BOARDPIECE_H
#define EINSTEIN_CHESS_BOARDPIECE_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "BoardGUI.h"
#include "../ChessPiece/Board.h"

/*
 * 该类表示棋盘上的棋盘格子
 * 该类接收棋盘位置进行初始化,通过Board指针与Board进行通信
 * 该类对El_Wodget控件进行重载以支持GUI功能
 */
class BoardPiece : public Fl_Widget{
private:
    //使用Board引用与Board类进行通信
    BoardGUI *board;
    std::pair<int,int> position;
public:
    BoardPiece(int a,int b,int x,int y,int w,int h,BoardGUI* board);
    int handle(int event) override;
};


#endif //EINSTEIN_CHESS_BOARDPIECE_H
