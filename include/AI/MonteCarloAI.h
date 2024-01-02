//
// Created by 穆琰鑫 on 2023/12/30.
//

#ifndef EINSTEIN_CHESS_MONTECARLOAI_H
#define EINSTEIN_CHESS_MONTECARLOAI_H

#include "../ChessPieceGUI/BoardGUI.h"
#include "../ChessPiece/Chess.h"
#include "../ChessPiece/Board.h"
#include "../ChessPiece/PieceAttributes.h"

class MonteCarloAI {
public:
    static Decision decide(Board board,Camp camp,int chess,int simulation_times);
};

#endif //EINSTEIN_CHESS_MONTECARLOAI_H
