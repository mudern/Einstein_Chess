//
// Created by 穆琰鑫 on 2023/9/26.
//

#include <algorithm>
#include "../../include/ChessPiece/Board.h"

Board::Board(std::vector<int> red, std::vector<int> blue) {
    //注意:这里使用move语法,red和blue最后会被清理销毁
    initializeBoard(std::move(red), std::move(blue));
}

//以{1, 3, 6, 2, 5, 4}作为初始化列表委托构造
Board::Board() {
    initializeBoard({1, 3, 6, 2, 5, 4}, {1, 3, 6, 2, 5, 4});
}

const std::vector<Chess> &Board::getChessRedCollection() const {
    return chess_red_collection;
}

const std::vector<Chess> &Board::getChessBlueCollection() const {
    return chess_blue_collection;
}

//将棋子的序号作为排序依据,用于初始化棋盘
bool chess_sort(Chess chess_1, Chess chess_2) {
    return chess_1.getSerialNum() <= chess_2.getSerialNum();
}

void Board::initializeBoard(std::vector<int> red, std::vector<int> blue) {
    for (size_t i = 0; i < red.size(); i++) {
        std::pair<int,int> chess_pos;
        switch (i) {
            case 0:chess_pos={1,1};break;
            case 1:chess_pos={1,2};break;
            case 2:chess_pos={1,3};break;
            case 3:chess_pos={2,1};break;
            case 4:chess_pos={2,2};break;
            case 5:chess_pos={3,1};break;
        }
        Chess chess(Camp::Red, red[i],
                    chess_pos);
        this->chess_red_collection.push_back(chess);
    }
    for (size_t i = 0; i < blue.size(); i++) {
        std::pair<int,int> chess_pos;
        switch (i) {
            case 0:chess_pos={5,5};break;
            case 1:chess_pos={5,4};break;
            case 2:chess_pos={5,3};break;
            case 3:chess_pos={4,5};break;
            case 4:chess_pos={4,4};break;
            case 5:chess_pos={3,5};break;
        }
        Chess chess(Camp::Blue, blue[i],
                    chess_pos);
        this->chess_blue_collection.push_back(chess);
    }
    //按照棋子标号进行排列
    std::sort(this->chess_red_collection.begin(), this->chess_red_collection.end(), chess_sort);
    std::sort(this->chess_blue_collection.begin(), this->chess_blue_collection.end(), chess_sort);
}

Chess & Board::getChess(Camp _camp, int _serial_num) {
    if(_camp==Camp::Red) return chess_red_collection[_serial_num-1];
    else return chess_blue_collection[_serial_num-1];
}

std::optional<std::pair<Camp,int>> Board::isOverlap(Chess *_chess,std::pair<int,int> _expected_position){
    //遍历棋子位置,判断是否有重叠棋子,如果有,返回该棋子
    for(int serial_num=0;serial_num<6;serial_num++){
        Chess &chess=chess_red_collection[serial_num];
        if(chess.isAlive()&&chess.getPosition()==_expected_position&& &chess!=_chess){
            return std::make_pair(Camp::Red,serial_num+1);
        }
    }
    for(int serial_num=0;serial_num<6;serial_num++){
        Chess &chess=chess_blue_collection[serial_num];
        if(chess.isAlive()&&chess.getPosition()==_expected_position&& &chess!=_chess){
            return std::make_pair(Camp::Blue,serial_num+1);
        }
    }
    return std::nullopt;
}

//移动棋盘上的棋子.检测移动后的位置是否存在棋子,检测是否会移出棋盘
bool Board::moveChess(Camp _camp, int _serial_num, Move _move_kind) {
    //获取棋子信息,得到需要移动的棋子
    Chess &chess = getChess(_camp,_serial_num);
    //如果棋子不能移动到指定位置,getExpectedPosition将返回空值
    if(!chess.move(_move_kind)) return false;
    std::pair<int,int> expected_position =*chess.getExpectedPosition(_move_kind);
    //如果棋子重叠则需要标记对方为死亡
    if(!isOverlap(&chess,expected_position)){
        auto chess_info=isOverlap(&chess,expected_position);
        Chess *over_lap_chess;
        if(chess_info->first==Camp::Red)over_lap_chess=&chess_red_collection[chess_info->second];
        else over_lap_chess=&chess_blue_collection[chess_info->second];
        over_lap_chess->setIsAlive(false);
    }
    //棋子正常移动
    bool move_result=chess.move(_move_kind);
    winner=hasWinner();
    return move_result;
}

bool Board::moveChess(Camp _camp, int _serial_num, std::pair<int, int> _position) {
    //获取棋子信息,得到需要移动的棋子
    Chess &chess = getChess(_camp,_serial_num);
    //如果棋子不能移动到指定位置,getExpectedPosition将返回空值
    if(!chess.move(_position)) return false;
    //如果棋子重叠则需要标记对方为死亡
    if(!isOverlap(&chess,_position)){
        auto chess_info=isOverlap(&chess,_position);
        Chess *over_lap_chess;
        if(chess_info->first==Camp::Red)over_lap_chess=&chess_red_collection[chess_info->second];
        else over_lap_chess=&chess_blue_collection[chess_info->second];
        over_lap_chess->setIsAlive(false);
    }
    bool move_result=chess.move(_position);
    winner=hasWinner();
    return move_result;
}

std::optional<Camp> Board::hasWinner() {
    if(chess_red_collection.empty()) return Camp::Blue;
    if(chess_blue_collection.empty()) return Camp::Red;
    for(auto chess:chess_red_collection){
        if(chess.getPosition() == std::pair<int,int>{5, 5}) return Camp::Red;
    }
    for(auto chess:chess_blue_collection){
        if(chess.getPosition() == std::pair<int,int>{1, 1}) return Camp::Blue;
    }
    return std::nullopt;
}