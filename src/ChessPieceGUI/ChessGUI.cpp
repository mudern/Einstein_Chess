//
// Created by 穆琰鑫 on 2023/10/14.
//

#include "../../include/ChessPieceGUI/ChessGUI.h"
#include <string>
#define BoardSize 100
#define ChessSize 75
#define WordSize 30

//使用chess对ChessGUI进行初始化
ChessGUI::ChessGUI(Chess* _chess)
        :chess(_chess),
        Fl_Widget((_chess->getPosition().first-1)*BoardSize+(BoardSize - ChessSize) / 2+50, (_chess->getPosition().second-1)*BoardSize+(BoardSize - ChessSize) / 2+50, ChessSize,ChessSize){
}

//重新设置绘制逻辑
void ChessGUI::draw() {
    //根据阵营确定棋子颜色
    if(chess->getCamp()==Camp::Red) fl_color(fl_rgb_color(255,64,64));
    else fl_color(fl_rgb_color(0,191,255));
    //绘制图形
    fl_pie(x(), y(), w(), h(), 0, 360);
    // 设置字体颜色、字体和字号
    fl_color(FL_BLACK); // 改变字体颜色为黑色，可以选择其他颜色
    fl_font(FL_HELVETICA, WordSize);
    // 获取序号并确保有效值
    int serialNum = chess->getSerialNum();
    std::string serialStr = (serialNum != 0) ? std::to_string(serialNum) : "";

    // 计算序号文本的宽度和高度
    int textWidth = 0, textHeight = 0;
    fl_measure(serialStr.c_str(), textWidth, textHeight);

    // 计算将序号放置在棋子中心的坐标位置
    int centerX = x() + (w() - textWidth) / 2;
    int centerY = y() + (h() + textHeight)*0.45;

    // 在棋子中心显示棋子序号
    fl_draw(serialStr.c_str(), centerX, centerY);
}

void ChessGUI::update() {
    if(!chess->isAlive()){
        hide();
        return;
    }
    int x= chess->getPosition().first-1;
    int y= chess->getPosition().second-1;
    position(x*BoardSize+(BoardSize - ChessSize) / 2+50,y*BoardSize+(BoardSize - ChessSize) / 2+50);
    hide();
    redraw();
    show();
}