//
// Created by 穆琰鑫 on 2023/9/26.
//

#include <algorithm>
#include "Board.h"

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
    //通过特殊映射(x/3+x/5,x%3+1-x/5)将vector表示的棋子位置初始化棋盘
    for (size_t i = 0; i < red.size(); i++) {
        Chess chess(Camp::Red, red[i],
                    std::pair<int, int>(i / 3 + i / 5, i % 3 + 1 - i / 5));
        this->chess_red_collection.push_back(chess);
    }
    for (size_t i = 0; i < blue.size(); i++) {
        Chess chess(Camp::Blue, blue[i],
                    std::pair<int, int>(7 - (i / 3 + i / 5), 7 - (i % 3 + 1 - i / 5)));
        this->chess_blue_collection.push_back(chess);
    }
    //按照棋子标号进行排列
    std::sort(this->chess_red_collection.begin(), this->chess_red_collection.end(), chess_sort);
    std::sort(this->chess_blue_collection.begin(), this->chess_blue_collection.end(), chess_sort);
}

Chess Board::getChess(Camp _camp, int _serial_num) {
    if(_camp==Camp::Red) return chess_red_collection[_serial_num-1];
    else return chess_blue_collection[_serial_num-1];
}

bool Board::isOverlap(std::pair<int,int> _expected_position){
    auto red_target=std::find_if(chess_red_collection.begin(), chess_red_collection.end(),
                                 [_expected_position](Chess chess){return chess.getPosition()==_expected_position;});
    auto blue_target=std::find_if(chess_blue_collection.begin(), chess_blue_collection.end(),
                                 [_expected_position](Chess chess){return chess.getPosition()==_expected_position;});
    return red_target!=chess_red_collection.end()||blue_target!=chess_blue_collection.end();
}

//移动棋盘上的棋子.检测移动后的位置是否存在棋子,检测是否会移出棋盘
bool Board::moveChess(Camp _camp, int _serial_num, Move _move_kind) {
    Chess chess = getChess(_camp,_serial_num);
    std::pair<int,int> expected_position =chess.getExpectedPosition(_move_kind);
    //如果棋子重叠则不能进行移动,返回false
    if(isOverlap(expected_position)) return false;
    return chess.move(_move_kind);
}