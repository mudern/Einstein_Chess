//
// Created by 穆琰鑫 on 2023/10/17.
//

#include "../../include/ChessPieceGUI/BoardPiece.h"

BoardPiece::BoardPiece(int a,int b,int x, int y, int w, int h, BoardGUI* board)
    : Fl_Widget(x,y,w,h), board(board), position(std::pair<int,int>(a, b)){};

int BoardPiece::handle(int event) {
    if(event==FL_PUSH) {
        board->handleClick(position);
        return 1;
    };
    return 0;
}

