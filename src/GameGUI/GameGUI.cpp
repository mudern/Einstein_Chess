//
// Created by 穆琰鑫 on 2023/12/7.
//

#include <utility>

#include "../../include/GameGUI/GameGUI.h"
#include "../../include/ChessPieceGUI/BoardGUI.h"

GameGUI::GameGUI(std::vector<int> red_chess,std::vector<int> blue_chess) {
    window = new Fl_Window(1050, 600, "Game GUI");
    window->color(fl_rgb_color(255 ,240 ,245));

    // 上面的按钮
    Fl_Box *spacer1 = new Fl_Box(600, 0, 400, 50); // 顶部空白区域
    horizontalButton = new Fl_Button(600, 50, 100, 100, "Horizontal");
    horizontalButton->callback(horizontalButtonClick, this);
    horizontalButton->color(fl_rgb_color(191 ,239 ,255));
    verticalButton = new Fl_Button(750, 50, 100, 100, "Vertical");
    verticalButton->callback(verticalButtonClick,this);
    verticalButton->color(fl_rgb_color(191 ,239 ,255));
    diagonalButton = new Fl_Button(900, 50, 100, 100, "Diagonal");
    diagonalButton->callback(diagonalButtonClcik,this);
    diagonalButton->color(fl_rgb_color(191 ,239 ,255));
    // 中间的文本框和按钮
    Fl_Box *spacer2 = new Fl_Box(600, 150, 400, 50); // 中间空白区域
    numberInput = new Fl_Choice(600, 250, 100, 50, "Input:");
    numberInput->color(fl_rgb_color(255 ,250 ,250));

    sendButton = new Fl_Button(750, 200, 100, 100, "Send");
    sendButton->callback(sendButtonClcik,this);
    sendButton->color(fl_rgb_color(255 ,130 ,171));

    randomButton = new Fl_Button(900, 200, 100, 100, "Random");
    randomButton->callback(randomButtonClick,this);
    randomButton->color(fl_rgb_color(255 ,130 ,171));

    // 下面的信息显示文本框
    Fl_Box *spacer3 = new Fl_Box(0, 550, 1050, 50); // 底部空白区域
    infoTextDisplay = new Fl_Text_Display(600, 350, 200, 200, "Information");
    textBuffer = new Fl_Text_Buffer();
    infoTextDisplay->color(fl_rgb_color(240 ,255 ,240));
    infoTextDisplay->buffer(textBuffer);

    //下拉条选择模式
    modeChoice = new Fl_Choice(825, 350, 175, 50, "");
    modeChoice->add(" Player V Player ");
    modeChoice->add(" Player V Computer");
    modeChoice->add(" Computer V Computer");
    modeChoice->color(fl_rgb_color(240 , 255 , 240));

    //开始游戏按钮
    playButton = new Fl_Button(875,450,100,100,"Play");
    playButton->color(fl_rgb_color(144 ,238 ,144));
    playButton->callback(playButtonClick,this);

    Fl_Box *spacer4 = new Fl_Box(0, 0, 600, 50);//棋盘空白
    // 棋盘部分
    boardGroup = new Fl_Group(50, 50, 500, 500);
    boardGui=new BoardGUI(this,std::move(red_chess),std::move(blue_chess));
    boardGroup->end();

    update_num();

    // 控件部分
    controlGroup = new Fl_Group(600, 0, 400, 600);

    controlGroup->end();

    window->end();
}



void GameGUI::start() {
    window->show();
    Fl::run();
}

void GameGUI::horizontalButtonClick(Fl_Widget *widget, void *data) {
    GameGUI* instance = static_cast<GameGUI*>(data);
    if(instance->boardGui->getGameStatus()!=GameStatus::Running){
        instance->display("请先选择模式并开始游戏");
        return;
    }
    instance->horizontal_move();
}

void GameGUI::verticalButtonClick(Fl_Widget *widget, void *data) {
    GameGUI* instance = static_cast<GameGUI*>(data);
    if(instance->boardGui->getGameStatus()!=GameStatus::Running){
        instance->display("请先选择模式并开始游戏");
        return;
    }
    instance->vertical_move();
}

void GameGUI::diagonalButtonClcik(Fl_Widget *widget, void *data) {
    GameGUI* instance = static_cast<GameGUI*>(data);
    if(instance->boardGui->getGameStatus()!=GameStatus::Running){
        instance->display("请先选择模式并开始游戏");
        return;
    }
    instance->diagonal_move();
}

void GameGUI::sendButtonClcik(Fl_Widget *widget, void *data) {
    GameGUI* instance = static_cast<GameGUI*>(data);
    if(instance->boardGui->getGameStatus()!=GameStatus::Running){
        instance->display("请先选择模式并开始游戏");
        return;
    }
    instance->send_num();
}

void GameGUI::randomButtonClick(Fl_Widget *widget, void *data) {
    GameGUI* instance = static_cast<GameGUI*>(data);
    if(instance->boardGui->getGameStatus()!=GameStatus::Running){
        instance->display("请先选择模式并开始游戏");
        return;
    }
    instance->generate_num();
}

void GameGUI::playButtonClick(Fl_Widget *widget, void *data) {
    GameGUI* instance = static_cast<GameGUI*>(data);
    instance->send_game_mode();
}

void GameGUI::display(std::string str) {
    strings.push_back(str);
    std::string combined_string;
    int startIdx = strings.size() > 11 ? strings.size() - 11 : 0;

    for (int i = startIdx; i < strings.size(); ++i) {
        combined_string += strings[i];
        if (i < strings.size() - 1) {
            combined_string += "\n";
        }
    }
    textBuffer->text(combined_string.c_str());
}

void GameGUI::send_num() {
    int index=numberInput->value();
    if(index==-1) return;
    auto str=numberInput->text(index);
    boardGui->setSelectedChess(str[0]-'0');
    std::string context;
    context+="当前选择";
    if(boardGui->getNowCamp()==Camp::Red)context+="红方";
    else context+="蓝方";
    context+=str;
    context+="号棋子";
    display(context);
}

void GameGUI::generate_num() {
    srand(static_cast<unsigned>(time(nullptr)));
    int random_index = rand() % (numberInput->size()-1);
    numberInput->value(random_index);
    std::string random_num=numberInput->text(numberInput->value());
    display("随机数字为:"+random_num);
}

void GameGUI::update_num() {
    std::vector<int> alive_chess=boardGui->send_alive_chess();
    numberInput->clear();
    for(auto chess:alive_chess){
        numberInput->add(std::to_string(chess).c_str());
    }
}

enum GameMode;
void GameGUI::send_game_mode() {
    if(is_play){
        if(modeChoice->value()==-1){
            display("未选择模式,无法开始游戏");
            return;
        }
        if(modeChoice->value()==0){
            display("当前选择:Player V Player");
            boardGui->setGameMode(GameMode::PvP);
            boardGui->setGameStatus(GameStatus::Running);
            playButton->deactivate();
        }
        if(modeChoice->value()==1){
            display("当前选择:Player V Computer");
            boardGui->setGameMode(GameMode::PvAI);
            playButton->label("FirstMove");
            modeChoice->clear();
            modeChoice->add(const_cast<char*>("Player First"));
            modeChoice->add(const_cast<char*>("Computer First"));
            is_play= false;
        }
        if(modeChoice->value()==2){
            display("当前选择:Computer V Computer");
            boardGui->setGameMode(GameMode::AIvAI);
            boardGui->setGameStatus(GameStatus::Running);
            playButton->deactivate();
        }
    }
    else{
        if(modeChoice->value()==-1){
            display("未选择先手,无法开始游戏");
            return;
        }
        if(modeChoice->value()==0){
            boardGui->setGameMode(GameMode::PvP);
            display("当前选择:Player V Player");
            boardGui->setPlayerFirst(true);
            boardGui->setGameStatus(GameStatus::Running);
            playButton->deactivate();
        }
        if(modeChoice->value()==1){
            boardGui->setGameMode(GameMode::PvP);
            display("当前选择:Player V Player");
            boardGui->setPlayerFirst(false);
            boardGui->setGameStatus(GameStatus::Running);
            playButton->deactivate();
        }
    }
}

void GameGUI::horizontal_move() {
    boardGui->move(Move::Horizontal);
}

void GameGUI::vertical_move() {
    boardGui->move(Move::Vertical);
}

void GameGUI::diagonal_move() {
    boardGui->move(Move::Diagonal);
}

void GameGUI::end_game() {
    horizontalButton->deactivate();
    verticalButton->deactivate();
    diagonalButton->deactivate();
    sendButton->deactivate();
    randomButton->deactivate();
}

const std::vector<std::string> &GameGUI::getStrings() const {
    return strings;
}
