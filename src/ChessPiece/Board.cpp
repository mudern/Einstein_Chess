//
// Created by 穆琰鑫 on 2023/9/26.
//

#include <algorithm>
#include <random>
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

Camp Board::getNowCamp() const {
    return now_camp;
}

void Board::setSelectedChessNum(int selectedChess) {
    selected_chess = selectedChess;
}

Chess &Board::getSelectedChess() {
    return getChess(now_camp,selected_chess);
}

void Board::toNextCamp() {
    std::swap(now_camp,next_camp);
}

int Board::getSelectedChessNum() const {
    return selected_chess;
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
        red_init_position.insert(std::make_pair(red[i],chess_pos));
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
        blue_init_position.insert(std::make_pair(blue[i],chess_pos));
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
    toNextCamp();
    winner=hasWinner();
    return move_result;
}

bool Board::moveChess(MoveChoice _move_choice) {
    bool move_result= moveChess(_move_choice.camp,
                                _move_choice.selected_num,
                                _move_choice.move_kind);
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

void Board::randomMove(std::random_device &rd) {
    // 设定随机数引擎和种子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎

    // 生成随机数
    std::uniform_int_distribution<int> distribution(1, 6);
    int random_chess_num = distribution(gen);

    // 获取随机选择
    auto random_chess_pair = validate_and_get_choice(random_chess_num);

    // 获取随机棋子
    Chess random_chess = Chess(now_camp, 0, std::make_pair(-1,-1));
    //如果只有一种选择,直接选择;如果有两种选择则随机选择;
    if (!random_chess_pair) {
        random_chess = getChess(now_camp, random_chess_num);
    } else {
        int first_choice = random_chess_pair->first;
        int second_choice = random_chess_pair->second;

        if (first_choice!=-1 && second_choice!=-1) {
            std::uniform_int_distribution<int> coin_flip(0, 1);
            int random_index = coin_flip(gen); // 随机选择两个中的一个

            random_chess = getChess(now_camp, (random_index == 0) ? first_choice : second_choice);
        }
        if (first_choice==-1) {
            random_chess = getChess(now_camp, second_choice);
        }
        if (second_choice==-1) {
            random_chess = getChess(now_camp, first_choice);
        }
    }
    // 获取当前可以移动的所有棋子
    std::vector<MoveChoice> all_possible_moves=random_chess.generate_move_choice();

    // 随机选择一个移动并执行
    std::uniform_int_distribution<int> move_distribution(0, all_possible_moves.size() - 1);
    int random_index = move_distribution(gen);
    moveChess(all_possible_moves[random_index]);
}

//重新开始游戏方法
void Board::replay() {
    //遍历红方,设置初始状态
    for(Chess &chess:chess_red_collection){
        chess.replay(red_init_position[chess.getSerialNum()]);
    }
    //遍历蓝方,设置初始状态
    for(Chess &chess:chess_blue_collection) {
        chess.replay(blue_init_position[chess.getSerialNum()]);
    }
}

std::optional<std::pair<int,int>> Board::validate_and_get_choice(int chess_num) {
    std::vector<int> alive_chess=send_alive_chess();
    for(auto alive:alive_chess){
        if(alive==chess_num) return std::nullopt;
    }
    std::vector<int> smaller_chess,bigger_chess;
    for(auto alive:alive_chess){
        if(alive<chess_num) smaller_chess.push_back(alive);
        else bigger_chess.push_back(alive);
    }
    auto res=std::make_pair(-1,-1);
    if (!smaller_chess.empty()) res.first = *(--smaller_chess.end());
    if (!bigger_chess.empty()) res.second = *(bigger_chess.begin());
    return res;
}

std::vector<int> Board::send_alive_chess() {
    std::vector<int> alive_chess;
    for (int serial_num = 1; serial_num <= 6; ++serial_num) {
        if(getChess(now_camp,serial_num).isAlive()) alive_chess.push_back(serial_num);
    }
    return alive_chess;
}

void Board::regret(ChessMap red_info,
                   ChessMap blue_info) {
    for (int serial_num=1;serial_num<=6;serial_num++){
        Chess &chess=chess_red_collection[serial_num-1];
        chess.setPosition(red_info[serial_num].position);
        chess.setIsAlive(red_info[serial_num].isAlive);
    }
    for (int serial_num=1;serial_num<=6;serial_num++){
        Chess &chess=chess_blue_collection[serial_num-1];
        chess.setPosition(blue_info[serial_num].position);
        chess.setIsAlive(blue_info[serial_num].isAlive);
    }
}

std::pair<ChessMap, ChessMap> Board::get_now_info() {
    ChessMap red_chess_map,blue_chess_map;
    for(int serial_num=1;serial_num<=6;serial_num++){
        Chess chess=chess_red_collection[serial_num-1];
        red_chess_map[serial_num]=ChessInfo{chess.getPosition(),chess.isAlive()};
    }
    for(int serial_num=1;serial_num<=6;serial_num++){
        Chess chess=chess_blue_collection[serial_num-1];
        blue_chess_map[serial_num]=ChessInfo{chess.getPosition(),chess.isAlive()};
    }
    return std::make_pair(red_chess_map,blue_chess_map);
}