//
// Created by 穆琰鑫 on 2023/9/26.
//

#ifndef EINSTEIN_CHESS_PIECE_ATTRIBUTES_H
#define EINSTEIN_CHESS_PIECE_ATTRIBUTES_H

/*
 * 该文件用于提供标识棋子状态的两种enum类型
 * Move标识移动的类型,包括水平移动,垂直移动和斜向移动
 * Camp标识棋子的阵营,包括先手处于左上角的红方和后手处于右下角的蓝方
 */
enum Move{
    //水平移动
    Horizontal,
    //垂直移动
    Vertical,
    //斜向移动
    Diagonal,
};

enum Camp{
    //红色在左上角
    Red,
    //蓝色在右下角
    Blue,
};

struct MoveChoice {
    Camp camp;
    int selected_num;
    Move move_kind;
};

struct Decision {
    Camp camp;
    int chess_num;
    Move move_kind;
    long double win_rates;

    Decision(const MoveChoice& _move_choice, long double _win_rates)
            : camp(_move_choice.camp), chess_num(_move_choice.selected_num),
              move_kind(_move_choice.move_kind), win_rates(_win_rates) {}
};
#endif //EINSTEIN_CHESS_PIECE_ATTRIBUTES_H
