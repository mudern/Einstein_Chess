//
// Created by 穆琰鑫 on 2023/10/14.
//

#ifndef EINSTEIN_CHESS_CHESSGUI_H
#define EINSTEIN_CHESS_CHESSGUI_H

#include "../ChessPiece/Chess.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <vector>
#include <optional>

/*
 * 该类表示棋盘上的棋子
 * 该类引用一般棋子Chess类
 * 通过对Chess类的修改和对自身GUI属性的维护实现功能
 * 该类对El_Wodget控件进行重载以支持GUI功能
 */
class ChessGUI:Fl_Widget{
private:
    Chess* chess;
public:
    ChessGUI(Chess *_chess);
    void draw() override;
    void update();
};


#endif //EINSTEIN_CHESS_CHESSGUI_H
