//
// Created by 穆琰鑫 on 2023/9/26.
//

#include "Chess.h"
#include "PieceAttributes.h"
Chess::Chess(Camp _camp,int _serial_num,std::pair<int,int> _position){
    camp=_camp;
    serial_num=_serial_num;
    position=_position;
}

// Getter 方法
Camp Chess::getCamp() const {
    return camp;
}
int Chess::getSerialNum() const {
    return serial_num;
}
std::pair<int, int> Chess::getPosition() const {
    return position;
}

//棋子移动方法
bool Chess::move(Move move_kind){
    if(!can_move(move_kind)) return false;
    // 红色方向右下角移动
    if (camp == Camp::Red) {
        if (move_kind == Move::Horizontal) {
            position.first++; // 向右移动
        } else { // Move::Vertical
            position.second++; // 向下移动
        }
    }
        // 蓝色方向左上角移动
    else if (camp == Camp::Blue) {
        if (move_kind == Move::Horizontal) {
            position.first--; // 向左移动
        } else { // Move::Vertical
            position.second--; // 向上移动
        }
    }
    return true;
}
//检测移动是否合法
bool Chess::can_move(Move move_kind){
    if(move_kind==Move::Horizontal){
        //红色方到达最右侧无法水平移动
        if(position.first==5&&camp==Camp::Red) return false;
        //蓝色方到达最左侧无法水平移动
        if(position.first==1&&camp==Camp::Blue) return false;
    }
    else{
        //红色方到达最下侧无法垂直移动
        if(position.second==5&&camp==Camp::Red) return false;
        //蓝色方到达最上侧无法垂直移动
        if(position.second==1&&camp==Camp::Blue) return false;
    }
    return true;
}