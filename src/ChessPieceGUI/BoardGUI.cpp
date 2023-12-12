//
// Created by 穆琰鑫 on 2023/10/14.
//

#include <utility>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <filesystem>

#include "../../include/ChessPieceGUI/BoardGUI.h"

bool BoardGUI::move(std::pair<int,int> _position) {
    if(this->game_status!=GameStatus::Running) return false;
    Chess &chess = getSelectedChess();
    // 尝试移动棋子到指定位置
    if (chess.move(_position)) {
        if(board->isOverlap(&chess,chess.getPosition())){
            auto chess_info=board->isOverlap(&chess,chess.getPosition()).value();
            Chess *over_lap_chess;
            over_lap_chess=&board->getChess(chess_info.first,chess_info.second);
            over_lap_chess->setIsAlive(false);
            if(chess_info.first==Camp::Red) red_chess_widgets[chess_info.second-1]->update();
            else blue_chess_widgets[chess_info.second-1]->update();
            display_move(now_camp,chess.getPosition(),selected_chess,chess_info.first,chess_info.second);
        }else {
            display_move(now_camp,chess.getPosition(),selected_chess);
        }
        // 如果移动成功，切换到下一个阵营并更新 ChessGUI 中的 Chess 引用
        if(now_camp==Camp::Red){
            red_chess_widgets[selected_chess-1]->update();
        }
        else{
            blue_chess_widgets[selected_chess-1]->update();
        }
        if(board->hasWinner()){
            end_game();
            return true;
        }
        toNextCamp();
        selected_chess=-1;
        return true;
    }
    return false;
}

bool BoardGUI::move(Move _move_kind) {
    if(this->game_status!=GameStatus::Running) return false;
    if(selected_chess<1||selected_chess>6) return false;
    Chess &chess = getSelectedChess();
    // 尝试移动棋子到指定位置
    if (chess.move(_move_kind)){
        if(board->isOverlap(&chess,chess.getPosition())){
            auto chess_info=board->isOverlap(&chess,chess.getPosition()).value();
            Chess *over_lap_chess;
            over_lap_chess=&board->getChess(chess_info.first,chess_info.second);
            over_lap_chess->setIsAlive(false);
            if(chess_info.first==Camp::Red) red_chess_widgets[chess_info.second-1]->update();
            else blue_chess_widgets[chess_info.second-1]->update();
            display_move(now_camp,chess.getPosition(),selected_chess,chess_info.first,chess_info.second);
        }else {
            display_move(now_camp,chess.getPosition(),selected_chess);
        }
        // 如果移动成功，切换到下一个阵营并更新 ChessGUI 中的 Chess 引用
        if(now_camp==Camp::Red){
            red_chess_widgets[selected_chess-1]->update();
        }
        else{
            blue_chess_widgets[selected_chess-1]->update();
        }
        if(board->hasWinner()){
            end_game();
            return true;
        }
        toNextCamp();
        selected_chess=-1;
        return true;
    }
    return false;
}

void BoardGUI::computer_move() {
    std::vector<Chess> red_chess=board->getChessRedCollection();
    std::vector<Chess> blue_chess=board->getChessBlueCollection();
    //move();
}

void BoardGUI::toNextCamp() {
    std::swap(now_camp,next_camp);
    gameGui->update_num();
    display_camp();
}

Chess & BoardGUI::getSelectedChess() {
    return board->getChess(now_camp,selected_chess);
}

BoardGUI::BoardGUI(GameGUI* game,std::vector<int> red_chess,std::vector<int> blue_chess){
    //建立与上层之间联系
    this->gameGui=game;
    // 构建6*6的棋盘网格
    const int gridSize = 5; // 棋盘大小为6x6
    const int squareSize = 100;
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            int x = col * squareSize+50;
            int y = row * squareSize+50;
            BoardPiece *square = new BoardPiece(col+1,row+1,x, y, squareSize, squareSize,this);
            square->color((row + col) % 2 == 0 ? FL_WHITE : fl_rgb_color(245 ,222 ,179)); // 交错的颜色表示棋盘
            board_pieces.push_back(square);
        }
    }
    this->board=new Board(std::move(red_chess),std::move(blue_chess));
    //设置红方ChessGUI
    for (int serial_num = 1; serial_num <= 6; ++serial_num) {
        ChessGUI *chessGui=new ChessGUI(&board->getChess(Camp::Red,serial_num));
        this->red_chess_widgets.push_back(chessGui);
    }
    //设置蓝方ChessGUI
    for (int serial_num = 1; serial_num <= 6; ++serial_num) {
        ChessGUI *chessGui=new ChessGUI(&board->getChess(Camp::Blue,serial_num));
        this->blue_chess_widgets.push_back(chessGui);
    }
}

void BoardGUI::display(std::string content) {
    gameGui->display(content);
}

void BoardGUI::display_move(Camp _camp_1,std::pair<int,int> _position, int _chess_1,Camp _camp_2, int _chess_2) {
    std::string context;
    if(_camp_1==Camp::Red) context+="红方 ";
    else context+="蓝方 ";
    context+=std::to_string(_chess_1);
    context+=" 号棋子";
    context+="移动到位置";
    context+=(std::to_string(_position.first)+","+std::to_string(_position.second));
    context+=" 吃掉";
    if(_camp_2==Camp::Red) context+="红方";
    else context+="蓝方";
    context+=std::to_string(_chess_2);
    context+=" 号棋子";
    display(context);
}

void BoardGUI::display_move(Camp _camp_1,std::pair<int,int> _position, int _chess_1) {
    std::string context;
    if(_camp_1==Camp::Red) context+="红方 ";
    else context+="蓝方 ";
    context+=std::to_string(_chess_1);
    context+=" 号棋子";
    context+="移动到位置";
    context+=(std::to_string(_position.first)+","+std::to_string(_position.second));
    display(context);
}

void BoardGUI::display_camp() {
    std::string context;
    context+="当前为:";
    if(now_camp==Camp::Red) context+="红方";
    else context+="蓝方";
    display(context);
}

std::vector<int> BoardGUI::send_alive_chess() {
    std::vector<int> alive_chess;
    for (int serial_num = 1; serial_num <= 6; ++serial_num) {
        if(board->getChess(now_camp,serial_num).isAlive()) alive_chess.push_back(serial_num);
    }
    return alive_chess;
}

void BoardGUI::end_game() {
    if(board->hasWinner().value()==Camp::Red) display("红方获胜");
    else display("蓝方获胜");
    game_status=GameStatus::End;
    save_log();
    gameGui->end_game();
}

void BoardGUI::save_log() {
    // 创建写入内容
    std::string content;
    // 获取系统时间
    std::time_t now = std::time(nullptr);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now), "%Y%m%d%H%M%S");
    std::string time_buffer = ss.str();
    content += ("时间:" + time_buffer + "\n");
    content += "游戏模式:";
    if (game_mode == GameMode::PvP) {
        content += "Player V Player\n";
    } else if (game_mode == GameMode::PvAI) {
        content += "Player V Computer\n";
        content += "游戏先手:";
        if (player_first) {
            content += "玩家先手\n";
        } else {
            content += "电脑先手\n";
        }
    } else if (game_mode == GameMode::AIvAI) {
        content += "Computer V Computer\n";
    }
    std::vector<std::string> strings = gameGui->getStrings();
    for (auto str : strings) {
        content += (str+"\n");
    }
    // 构建文件夹的完整路径
    std::string folderpath = "game_log";

    try {
        // 尝试创建文件夹
        std::filesystem::create_directories(folderpath);

        // 构建文件的完整路径
        std::string filepath = folderpath + "/" + time_buffer + ".txt";

        // 创建并打开文件
        std::ofstream file(filepath);

        if (file.is_open()) {
            // 将内容写入文件
            file << content;
            display("Game log has been saved");
            file.close();
        } else {
            display("Game log can't be saved");
        }
    } catch (const std::exception& e) {
        display("Failed to create directory: " + std::string(e.what()));
    }
}

void BoardGUI::setSelectedChess(int selectedChess) {
    if(game_mode==GameMode::PvAI){
        if(player_first&&now_camp==Camp::Blue){
            computer_move();
        }
        else if(!player_first&&now_camp==Camp::Red){
            computer_move();
        }
    }
    else if(game_mode==GameMode::AIvAI){
        computer_move();
    }
    selected_chess = selectedChess;
}

void BoardGUI::setGameMode(GameMode gameMode) {
    game_mode = gameMode;
}

void BoardGUI::setGameStatus(GameStatus gameStatus) {
    display_camp();
    game_status = gameStatus;
}

void BoardGUI::setNowCamp(Camp nowCamp) {
    now_camp = nowCamp;
}

Camp BoardGUI::getNowCamp() const {
    return now_camp;
}

GameStatus BoardGUI::getGameStatus() const {
    return game_status;
}

void BoardGUI::setPlayerFirst(bool playerFirst) {
    player_first = playerFirst;
}

BoardPiece::BoardPiece(int a, int b, int x, int y, int w, int h, BoardGUI *board)
        : Fl_Button(x,y,w,h), board(board), position(std::pair<int,int>(a, b)){}

int BoardPiece::handle(int event) {
    if(event==FL_PUSH) {
        board->move(position);
        return 1;
    };
    return 0;
}