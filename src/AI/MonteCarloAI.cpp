//
// Created by 穆琰鑫 on 2023/12/30.
//

#include <random>
#include "../../include/AI/MonteCarloAI.h"

Decision MonteCarloAI::decide(Board board, Camp camp, int chess,int simulation_times){
    std::vector<MoveChoice> choices=board.getChess(camp,chess).generate_move_choice();
    std::vector<long double> win_rates;
    std::random_device rd;
    for(auto choice:choices){
        Board board_temp=Board(board);
        Camp now_camp=board_temp.getNowCamp();
        board_temp.moveChess(choice);
        //上一次的位置信息
        auto [red_info,blue_info]=board_temp.get_now_info();
        //进行N轮有结果的游戏
        int win_rounds=0;
        int total_rounds=simulation_times;
        for(int rounds=0;rounds<total_rounds;rounds++){
            //棋盘随机移动到有结果为止
            while (!board_temp.hasWinner()){
                board_temp.randomMove(rd);
            }
            if(board_temp.hasWinner().value()==now_camp) win_rounds++;
            board_temp.regret(red_info,blue_info);
        }
        win_rates.push_back((long double)win_rounds/total_rounds);
    }
    //寻找胜率最高的Decision进行返回
    size_t max_index = 0;
    long double max_rate = 0.0;
    for (size_t i = 0; i < win_rates.size(); ++i) {
        if (win_rates[i] > max_rate) {
            max_rate = win_rates[i];
            max_index = i;
        }
    }
    // 返回具有最高胜率的决策
    return {choices[max_index],max_rate};
}
