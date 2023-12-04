//
// Created by 穆琰鑫 on 2023/10/14.
//

#ifndef EINSTEIN_CHESS_BOARDGUI_H
#define EINSTEIN_CHESS_BOARDGUI_H


#include <vector>
#include <memory>
#include "ChessGUI.h"
#include "BoardPiece.h"
#include "../ChessPiece/Board.h"

/*
 * 该类表示棋局本身,通过引入ChessGUI指针间接引入棋子,通过存储Board指针简介引入棋盘
 * 该类初始化时,将接收一个已经初始化包含了Chess类的Board类指针和ChessPiece类,实现了棋盘的GUI化
 * 存储棋子控件的vector将初始化ChessGUI类实例,并将实例所有指针指向Board类中包含的Chess类,实现棋子GUI化
 * 通过操控Board类和已经实例化的ChessGUI类可以实现对棋盘和棋子的控制
 */
class BoardGUI:Fl_Group{
private:
    //存储棋子控件
    std::vector<std::unique_ptr<ChessGUI>> red_chess_widgets;
    std::vector<std::unique_ptr<ChessGUI>> blue_chess_widgets;
    //存储Board
    Board *board;
    //存储BoardPiece
    std::vector<BoardPiece> board_pieces;
    //存储当前被选中棋子信息
    int selected_chess;
    //存储当前操作的阵营
    Camp now_camp=Camp::Red;
    Camp next_camp=Camp::Blue;
    //存储当前输入的值
    std::optional<int> input_chess_serial_num=std::nullopt;
public:
    bool handleClick(std::pair<int,int> _position);
    void toNextCamp();
    Chess getSelectedChess();
};

#endif //EINSTEIN_CHESS_BOARDGUI_H
