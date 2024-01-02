//
// Created by 穆琰鑫 on 2023/12/7.
//

#include <utility>
#include <sstream>

#include "../../include/GameGUI/GameGUI.h"
#include "../../include/ChessPieceGUI/BoardGUI.h"

GameGUI::GameGUI(std::vector<int> red_chess,std::vector<int> blue_chess) {
    window = new Fl_Window(1050, 600, "Game GUI");
    window->color(fl_rgb_color(255 ,240 ,245));

    // 上面的按钮
    auto *spacer1 = new Fl_Box(600, 0, 400, 50); // 顶部空白区域
    horizontalButton = new Fl_Button(600, 50, 100, 100, "Horizontal");
    horizontalButton->callback(horizontalButtonClick, this);
    horizontalButton->color(fl_rgb_color(191 ,239 ,255));
    verticalButton = new Fl_Button(750, 50, 100, 100, "Vertical");
    verticalButton->callback(verticalButtonClick,this);
    verticalButton->color(fl_rgb_color(191 ,239 ,255));
    diagonalButton = new Fl_Button(900, 50, 100, 100, "Diagonal");
    diagonalButton->callback(diagonalButtonClick, this);
    diagonalButton->color(fl_rgb_color(191 ,239 ,255));
    // 中间的文本框和按钮
    auto *spacer2 = new Fl_Box(600, 150, 400, 50); // 中间空白区域
    numberInput = new Fl_Choice(600, 250, 100, 50, "Input:");
    numberInput->color(fl_rgb_color(255 ,250 ,250));

    sendButton = new Fl_Button(750, 200, 100, 100, "Send");
    sendButton->callback(sendButtonClcik,this);
    sendButton->color(fl_rgb_color(255 ,130 ,171));

    randomButton = new Fl_Button(900, 200, 100, 100, "Random");
    randomButton->callback(randomButtonClick,this);
    randomButton->color(fl_rgb_color(255 ,130 ,171));

    // 下面的信息显示文本框
    auto *spacer3 = new Fl_Box(0, 550, 1050, 50); // 底部空白区域
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

    auto *spacer4 = new Fl_Box(0, 0, 600, 50);//棋盘空白
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
    auto* instance = static_cast<GameGUI*>(data);
    if(instance->boardGui->getGameStatus()!=GameStatus::Running){
        instance->display("请先选择模式并开始游戏");
        return;
    }
    instance->horizontal_move();
}

void GameGUI::verticalButtonClick(Fl_Widget *widget, void *data) {
    auto* instance = static_cast<GameGUI*>(data);
    if(instance->boardGui->getGameStatus()!=GameStatus::Running){
        instance->display("请先选择模式并开始游戏");
        return;
    }
    instance->vertical_move();
}

void GameGUI::diagonalButtonClick(Fl_Widget *widget, void *data) {
    auto* instance = static_cast<GameGUI*>(data);
    if(instance->boardGui->getGameStatus()!=GameStatus::Running){
        instance->display("请先选择模式并开始游戏");
        return;
    }
    instance->diagonal_move();
}

void GameGUI::sendButtonClcik(Fl_Widget *widget, void *data) {
    auto* instance = static_cast<GameGUI*>(data);
    if(instance->boardGui->getGameStatus()!=GameStatus::Running){
        instance->display("请先选择模式并开始游戏");
        return;
    }
    instance->send_num();
}

void GameGUI::randomButtonClick(Fl_Widget *widget, void *data) {
    auto* instance = static_cast<GameGUI*>(data);
    if(instance->boardGui->getGameStatus()!=GameStatus::Running){
        instance->display("请先选择模式并开始游戏");
        return;
    }
    instance->generate_num();
}

void GameGUI::playButtonClick(Fl_Widget *widget, void *data) {
    auto* instance = static_cast<GameGUI*>(data);
    instance->send_game_mode();
}

void GameGUI::replayButtonClick(Fl_Widget *widget, void *data) {
    auto* instance = static_cast<GameGUI*>(data);
    instance->replay_game();
}

void GameGUI::display(const std::string& str) {
    strings.push_back(str);
    std::string combined_string;
    auto startIdx = strings.size() > 11 ? strings.size() - 11U : 0U;

    for (size_t i = startIdx; i < strings.size(); ++i) {
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
    int selected_num=str[0]-'0';
    //如果校验通过,则选择并广播结果,否则进入重选择
    std::optional<std::pair<int,int>> check_result=boardGui->validate_and_get_choice(selected_num);
    if(!check_result){
        sendButton->label("Send");
        std::stringstream context;
        context << "当前选择" << ((boardGui->getNowCamp() == Camp::Red) ? "红方" : "蓝方") << str << "号棋子";
        display(context.str());
        boardGui->setSelectedChess(str[0]-'0');
    }else{
        sendButton->label("Resend");
        numberInput->value(-1);
        numberInput->clear();
        int smaller=check_result->first;
        auto smaller_str=std::to_string(smaller);
        int bigger=check_result->second;
        auto bigger_str=std::to_string(bigger);
        std::stringstream context;
        if(smaller!=-1) numberInput->add(std::to_string(smaller).c_str());
        if(bigger!=-1) numberInput->add(std::to_string(bigger).c_str());
        context << "随机数字无效,可以选择";
        if(smaller!=-1&&bigger!=-1) context<<smaller_str<<"或"<<bigger_str<<"棋子";
        else{
            if(smaller!=-1) context<<smaller<<"棋子";
            if(bigger!=-1) context<<bigger<<"棋子";
        }
        display(context.str());
    }
}

void GameGUI::generate_num() {
    std::random_device rd; // 创建真正的随机数生成器
    std::mt19937 gen(rd()); // 使用 random_device 作为种子

    std::uniform_int_distribution<int> distribution(0, numberInput->size() - 2);

    int random_index = distribution(gen); // 生成随机索引
    numberInput->value(random_index);
    std::string random_num = numberInput->text(numberInput->value());
    display("随机数字为:" + random_num);
}

void GameGUI::update_num() {
    numberInput->clear();
    for(int chess=1;chess<=6;chess++){
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
            change_to_replay();
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
            change_to_replay();
        }
    }
    else{
        if(modeChoice->value()==-1){
            display("未选择先手,无法开始游戏");
            return;
        }
        if(modeChoice->value()==0){
            boardGui->setGameMode(GameMode::PvAI);
            display("当前选择:Player先手");
            boardGui->setPlayerFirst(true);
            boardGui->setGameStatus(GameStatus::Running);
            change_to_replay();
        }
        if(modeChoice->value()==1){
            boardGui->setGameMode(GameMode::PvAI);
            display("当前选择:Computer先手");
            boardGui->setPlayerFirst(false);
            boardGui->setGameStatus(GameStatus::Running);
            change_to_replay();
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
    change_to_replay();
}

const std::vector<std::string> &GameGUI::getStrings() const {
    return strings;
}

void GameGUI::replay_game() {
    //启用按钮
    horizontalButton->activate();
    verticalButton->activate();
    diagonalButton->activate();
    sendButton->activate();
    randomButton->activate();
    //清除文本内容
    while (!strings.empty()) strings.pop_back();
    //调用棋盘replay方法
    boardGui->replay();
}

void GameGUI::change_to_replay() {
    playButton->label("Replay");
    playButton->callback(replayButtonClick);
    playButton->activate();
    update_num();
}