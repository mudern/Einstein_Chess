//
// Created by 穆琰鑫 on 2023/10/14.
//

#ifndef EINSTEIN_CHESS_BOARDGUI_H
#define EINSTEIN_CHESS_BOARDGUI_H


#include <vector>
#include <memory>
#include <FL/Fl_Button.H>
#include <Fl/Fl_Choice.H>
#include "ChessGUI.h"
#include "../ChessPiece/Board.h"
#include "../GameGUI/GameGUI.h"
#include "../AI/MonteCarloAI.h"

class BoardPiece;

enum GameStatus{
    Ready,
    Running,
    End,
};

enum GameMode{
    PvP,
    PvAI,
    AIvAI,
};

/*
 * 该类表示棋局本身,通过引入ChessGUI指针间接引入棋子,通过存储Board指针简介引入棋盘
 * 该类初始化时,将接收一个已经初始化包含了Chess类的Board类指针和ChessPiece类,实现了棋盘的GUI化
 * 存储棋子控件的vector将初始化ChessGUI类实例,并将实例所有指针指向Board类中包含的Chess类,实现棋子GUI化
 * 通过操控Board类和已经实例化的ChessGUI类可以实现对棋盘和棋子的控制
 */
class BoardGUI{
private:
    //存储棋子控件
    std::vector<ChessGUI*> red_chess_widgets;
    std::vector<ChessGUI*> blue_chess_widgets;
    //存储Board
    Board *board;
    //存储BoardPiece
    std::vector<BoardPiece*> board_pieces;
    //修改游戏下拉框选项
    GameGUI *gameGui;
    //判断游戏模式和游戏状态
    GameStatus game_status=GameStatus::Ready;
    GameMode game_mode;
    //人机模式是否人先
    bool player_first;
public:
    BoardGUI(GameGUI* game,std::vector<int> red_chess,std::vector<int> blue_chess);
    void setGameMode(GameMode gameMode);
    void setGameStatus(GameStatus gameStatus);
    void setSelectedChess(int selectedChess);
    [[nodiscard]] GameStatus getGameStatus() const;
    [[nodiscard]] Camp getNowCamp() const;
    void toNextCamp();
    void setPlayerFirst(bool humanFirst);
    bool move(std::pair<int,int> _position);
    bool move(Move _move_kind);
    std::optional<std::pair<int,int>> validate_and_get_choice(int chess_num);
    void replay();
private:
    //AI移动棋子
    void computer_move();
    //当前是否为AI操作
    bool isComputer();
    void display_move(Camp _camp_1,std::pair<int,int> _position,int _chess_1,Camp _camp_2, int _chess_2);
    void display_move(Camp _camp_1,std::pair<int,int> _position,int _chess_1);
    void display_camp();
    void display(std::string content);
    void end_game();
    void save_log();
};

class BoardPiece : public Fl_Button{
//使用Board引用与Board类进行通信
    BoardGUI *board;
    std::pair<int,int> position;
public:
    BoardPiece(int a,int b,int x,int y,int w,int h,BoardGUI* board);
    int handle(int event) override;
};

#endif //EINSTEIN_CHESS_BOARDGUI_H
