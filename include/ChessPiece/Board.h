//
// Created by 穆琰鑫 on 2023/9/26.
//

#ifndef Einstein_Chess_BOARD_H
#define Einstein_Chess_BOARD_H

#include <iostream>
#include <vector>
#include <optional>
#include <unordered_map>
#include <random>
#include "Chess.h"

struct ChessInfo {
    std::pair<int, int> position;
    bool isAlive;
};

using ChessMap = std::unordered_map<int, ChessInfo>;

/*
 * 该类为基础Board类,用于提供Board基础功能
 * 该类存储所有的棋子并且保存棋子判断逻辑
 * 在使用时,棋子无需显式构建,构建棋盘时将会构建对应棋子
 */
class Board {
private:
    //使用Vector存储所有棋子
    std::vector<Chess> chess_red_collection;
    std::vector<Chess> chess_blue_collection;
    std::optional<Camp> winner=std::nullopt;
    //设置初始位置信息
    std::unordered_map<int,std::pair<int,int>> red_init_position;
    std::unordered_map<int,std::pair<int,int>> blue_init_position;
    //存储当前被选中棋子信息
    int selected_chess=-1;
    //存储当前操作的阵营
    Camp now_camp=Camp::Red;
    Camp next_camp=Camp::Blue;
    //上一次的位置信息
    ChessMap red_last_info;
    ChessMap blue_last_info;
public:
    //默认无参初始化棋盘,按照较优的方式构建棋盘
    Board();
    //传入红蓝两个阵营棋子位置的Vector初始化棋盘
    Board(std::vector<int> red,std::vector<int> blue);
    // Getter 方法
    const std::vector<Chess> &getChessRedCollection() const;
    const std::vector<Chess> &getChessBlueCollection() const;
    Camp getNowCamp() const;
    void setSelectedChessNum(int selectedChess);
    void setRedLastInfo(const ChessMap &redLastInfo);
    void setBlueLastInfo(const ChessMap &blueLastInfo);
    int getSelectedChessNum() const;
    Chess & getSelectedChess();
    std::pair<ChessMap,ChessMap> get_now_info();
    //返回指定的棋子供上层操作
    Chess & getChess(Camp _camp,int _serial_num);
    void toNextCamp();
    //传入指定的棋子和移动方向进行移动,可以移动返回true,不能移动返回false
    bool moveChess(Camp _camp,int _serial_num,Move _move_kind);
    bool moveChess(MoveChoice _move_choice);
    //传入指定的棋子和移动方向进行移动,可以移动返回true,不能移动返回false
    bool moveChess(Camp _camp,int _serial_num,std::pair<int,int> _position);
    //检测棋子移动后是否会重叠
    std::optional<std::pair<Camp,int>> isOverlap(Chess *_chess,std::pair<int,int> _expected_position);
    std::optional<Camp> hasWinner();
    //发送所有存活棋子
    std::vector<int> send_alive_chess();
    //校验当前数字是否可选定棋子,不能则给出最近解
    std::optional<std::pair<int,int>> validate_and_get_choice(int chess_num);
    //随机移动一次
    void randomMove(std::random_device &rd);
    void replay();
    void regret(ChessMap red_info,
                ChessMap blue_info);
    void regret_once();
private:
    //作为两个构造函数调用的基函数
    void initializeBoard(std::vector<int> red,std::vector<int> blue);
};

#endif //Einstein_Chess_BOARD_H
