//
// Created by 穆琰鑫 on 2023/12/7.
//

#ifndef EINSTEIN_CHESS_GAMEGUI_H
#define EINSTEIN_CHESS_GAMEGUI_H


#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Box.H>
#include <Fl/Fl_Choice.H>
#include <string>
#include <vector>

class BoardGUI;

class GameGUI {
private:
    Fl_Window *window;
    //BoardGUI通信
    BoardGUI *boardGui;
    // 棋盘部分
    Fl_Group *boardGroup;
    // 控件部分
    Fl_Group *controlGroup;
    // 水平、竖直、斜向按钮
    Fl_Button *horizontalButton;
    Fl_Button *verticalButton;
    Fl_Button *diagonalButton;
    // 输入数字的文本框和按钮
    Fl_Choice *numberInput;
    Fl_Choice *modeChoice;
    Fl_Button *sendButton;
    Fl_Button *randomButton;
    Fl_Button *playButton;
    // 显示信息的文本框
    Fl_Text_Display *infoTextDisplay;
    Fl_Text_Buffer *textBuffer;
    // 文本内容
    std::vector<std::string> strings;
    //选择棋子是否被接收
    bool accept=true;
public:
    [[nodiscard]] const std::vector<std::string> &getStrings() const;
private:
    //playButton状态
    bool is_play= true;
public:
    GameGUI(std::vector<int> red_chess,std::vector<int> blue_chess);
    //开始游戏
    void start();
    //传输信息事件
    void display(const std::string& str);
    //更新下拉条内容
    void update_num();
    //结束游戏
    void end_game();
    //重新开始游戏
    void replay_game();
private:
    static void horizontalButtonClick(Fl_Widget* widget, void* data);
    static void verticalButtonClick(Fl_Widget* widget, void* data);
    static void diagonalButtonClick(Fl_Widget* widget, void* data);
    static void sendButtonClcik(Fl_Widget* widget, void* data);
    static void randomButtonClick(Fl_Widget* widget, void* data);
    static void playButtonClick(Fl_Widget* widget, void* data);
    static void replayButtonClick(Fl_Widget* widget, void* data);

    void generate_num();
    void send_num();
    void send_game_mode();
    void horizontal_move();
    void vertical_move();
    void diagonal_move();
    void change_to_replay();
};

#endif //EINSTEIN_CHESS_GAMEGUI_H