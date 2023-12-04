//
// Created by 穆琰鑫 on 2023/10/14.
//

#include "../../include/ChessPieceGUI/ChessGUI.h"

//使用chess对ChessGUI进行初始化
ChessGUI::ChessGUI(Chess* _chess)
        :chess(_chess),
        Fl_Widget((_chess->getPosition().first-1)*20, (_chess->getPosition().second-1)*20, 80, 80){
}

//重新设置绘制逻辑
void ChessGUI::draw() {
    //绘制图形
    fl_pie(x(), y(), w(), h(), 0, 360);
    //根据阵营确定棋子颜色
    if(chess->getCamp()==Camp::Red) fl_color(FL_RED);
    else fl_color(FL_BLUE);
    //设置字体与字号
    fl_font(FL_HELVETICA, 20);
    //在棋子中心显示棋子序号
    fl_draw(std::to_string(chess->getSerialNum()).c_str(), x() + 40, y() + 40);
}

int ChessGUI::handle(int event) {
    //当棋子控件被按下,设置变量为棋子当前位置用于传输
    if (event==FL_PUSH) {
        selectedChess = chess->getPosition();
        return 1;
    }
    //当棋子控件没有被按下,设置当前变量为空
    if(event==FL_RELEASE){
        selectedChess=std::nullopt;
        return 0;
    }
    return 0;
}

//根据现在的棋子位置计算修改后GUI的位置
std::pair<int,int> ChessGUI::calcChessPosition() {
    int x= chess->getPosition().first;
    int y= chess->getPosition().second;
    std::pair<int,int> chess_position((x-1)*20,(y-1)*20);
    return chess_position;
}

void ChessGUI::move(Move _move_kind) {
    //如果不能移动则不移动
    if(!chess->move(_move_kind)) return;
    //如果能移动则移动,并修改相关GUI
    chess->move(_move_kind);
    Fl_Widget::x(calcChessPosition().first);
    Fl_Widget::y(calcChessPosition().second);
}

void ChessGUI::move(std::pair<int, int> _position) {
    //如果不能移动则不移动
    if(!chess->move(_position)) return;
    //如果能移动则移动,并修改相关GUI
    chess->move(_position);
    Fl_Widget::x(calcChessPosition().first);
    Fl_Widget::y(calcChessPosition().second);
}
