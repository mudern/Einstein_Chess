//
// Created by 穆琰鑫 on 2023/10/14.
//

#include "../../include/ChessPieceGUI/BoardGUI.h"

bool BoardGUI::handleClick(std::pair<int, int> _position) {
    Chess chess=getSelectedChess();
    //如果可以移动则移动
    if(!chess.move(_position)){
        //修改chess
        chess.move(_position);
        //todo 通过修改ChessGUI中的Chess引用控制Chess
        return true;
    }
    return false;
}

void BoardGUI::toNextCamp() {
    std::swap(now_camp,next_camp);
}

Chess BoardGUI::getSelectedChess() {
    board->getChess(now_camp,selected_chess);
}