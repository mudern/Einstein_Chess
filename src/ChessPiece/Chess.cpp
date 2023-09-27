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
bool Chess::move(Move _move_kind){
    if(!canMove(_move_kind)) return false;
    position= getExpectedPosition(_move_kind);
    return true;
}
//检测移动是否合法
bool Chess::canMove(Move _move_kind){
    if(_move_kind==Move::Horizontal){
        //红色方到达最右侧无法水平移动
        if(position.first==5&&camp==Camp::Red) return false;
        //蓝色方到达最左侧无法水平移动
        if(position.first==1&&camp==Camp::Blue) return false;
    }
    else if(_move_kind==Move::Vertical) {
        //红色方到达最下侧无法垂直移动
        if (position.second == 5 && camp == Camp::Red) return false;
        //蓝色方到达最上侧无法垂直移动
        if (position.second == 1 && camp == Camp::Blue) return false;
    }
    else if(_move_kind==Move::Diagonal){
        //只有既能水平移动也能垂直移动才能斜向移动
        return canMove(Move::Horizontal) && canMove(Move::Vertical);
    }
    return true;
}

std::pair<int, int> Chess::getExpectedPosition(Move _move_kind) {
    // 红色方向右下角移动
    if (camp == Camp::Red) {
        if (_move_kind == Move::Horizontal) {
            return {position.first+1,position.second};// 向右移动
        }
        else if(_move_kind==Move::Vertical){
            return {position.first,position.second-1}; //向下移动
        }
        else if(_move_kind==Move::Diagonal){
            //向右向下移动
            return {position.first+1,position.second-1};
        }
    }
        // 蓝色方向左上角移动
    else if (camp == Camp::Blue) {
        if (_move_kind == Move::Horizontal) {
            return {position.first-1,position.second};// 向左移动
        }
        else if(_move_kind==Move::Vertical){
            return {position.first,position.second+1};//向上移动
        }
        else if(_move_kind==Move::Diagonal){
            //向左向上移动
            return {position.first-1,position.second+1};
        }
    }
}
