//
// Created by 穆琰鑫 on 2023/9/26.
//

#include <vector>
#include "../../include/ChessPiece/Chess.h"
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
bool Chess::isAlive() const {
    return is_alive;
}
// Setter方法
void Chess::setIsAlive(bool _status) {
    is_alive = _status;
}
void Chess::setPosition(const std::pair<int, int> &position) {
    Chess::position = position;
}

//棋子移动方法
bool Chess::move(Move _move_kind){
    if(!canMove(_move_kind)) return false;
    position= getExpectedPosition(_move_kind).value();
    return true;
}
bool Chess::move(std::pair<int, int> _position) {
    if(!canMove(_position)) return false;
    position=_position;
    return true;
}

/*
 * 获取棋子的移动类型,通过棋子所在位置和移动类型返回是否可以移动
 */
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
        //红色方到达最右侧无法水平移动
        if(position.first==5&&camp==Camp::Red) return false;
        //蓝色方到达最左侧无法水平移动
        if(position.first==1&&camp==Camp::Blue) return false;
        //红色方到达最下侧无法垂直移动
        if (position.second == 5 && camp == Camp::Red) return false;
        //蓝色方到达最上侧无法垂直移动
        if (position.second == 1 && camp == Camp::Blue) return false;
    }
    return true;
}

/*
 * 获取棋子想要移动的位置,返回是否可以进行该移动
 */
bool Chess::canMove(std::pair<int, int> _position) {
    if(getMoveKind(_position)){
        Move move_kind=getMoveKind(_position).value();
        return canMove(move_kind);
    }else{
        return false;
    }
}

/*
 * 获取棋子移动类型,通过移动类型和当前位置,推断移动后的位置
 * 如果不能移动则返回nullopt,如果可以移动则返回移动后位置
 */
std::optional<std::pair<int, int>> Chess::getExpectedPosition(Move _move_kind) {
    // 如果不能移动则不移动,返回nullopt
    if(!canMove(_move_kind)) return std::nullopt;
    // 红色方向右下角移动
    if (camp == Camp::Red) {
        if (_move_kind == Move::Horizontal) {
            return std::pair<int,int>{position.first+1,position.second};// 向右移动
        }
        else if(_move_kind==Move::Vertical){
            return std::pair<int,int>{position.first,position.second+1}; //向下移动
        }
        else if(_move_kind==Move::Diagonal){
            //向右向下移动
            return std::pair<int,int>{position.first+1,position.second+1};
        }
    }
    // 蓝色方向左上角移动
    else if (camp == Camp::Blue) {
        if (_move_kind == Move::Horizontal) {
            return std::pair<int,int>{position.first-1,position.second};// 向左移动
        }
        else if(_move_kind==Move::Vertical){
            return std::pair<int,int>{position.first,position.second-1};//向上移动
        }
        else if(_move_kind==Move::Diagonal){
            //向左向上移动
            return std::pair<int,int>{position.first-1,position.second-1};
        }
    }
}

//获得棋子当前位置,通过计算其与预期位置的差值,以此判断棋子移动类型
std::optional<Move> Chess::getMoveKind(std::pair<int, int> _position) {
    //获得棋子当前位置与预期位置的差值
    std::pair<int, int> difference
            = std::pair<int, int>(_position.first - position.first, _position.second - position.second);
    std::optional<Move> move_kind = std::nullopt;
    //如果是红方则差值为正数
    if (camp == Camp::Red) {
        if (difference == std::pair<int, int>(1, 0))move_kind = Horizontal;
        if (difference == std::pair<int, int>(0, 1))move_kind = Vertical;
        if (difference == std::pair<int, int>(1, 1))move_kind = Diagonal;
    }
    //如果是蓝方则差值为负数
    if (camp == Camp::Blue) {
        if (difference == std::pair<int, int>(-1, 0))move_kind = Horizontal;
        if (difference == std::pair<int, int>(0, -1))move_kind = Vertical;
        if (difference == std::pair<int, int>(-1, -1))move_kind = Diagonal;
    }
    return move_kind;
}

void Chess::replay(std::pair<int,int> pos) {
    this->setIsAlive(true);
    this->position=pos;
}

std::vector<MoveChoice> Chess::generate_move_choice() {
    std::vector<MoveChoice> choices;
    if(canMove(Move::Horizontal)) choices.push_back(MoveChoice{camp,serial_num,Horizontal});
    if(canMove(Move::Vertical)) choices.push_back(MoveChoice{camp,serial_num,Vertical});
    if(canMove(Move::Diagonal)) choices.push_back(MoveChoice{camp,serial_num,Diagonal});
    return choices;
}