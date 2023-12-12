#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "include/GameGUI/GameGUI.h"

int main(int argc, char *argv[]) {
    std::cout << "Input Y to use default settings, or n to decline:" << std::endl;
    std::string is_default;
    std::cin >> is_default;
    if (is_default == "Y") {
        GameGUI *game = new GameGUI({1, 3, 6, 2, 5, 4}, {1, 3, 6, 2, 5, 4});
        game->start();
    } else {
        std::cout << "Please enter the layout of red chess pieces from top to bottom, left to right: " << std::endl;
        std::vector<int> red_chess;
        std::vector<bool> red_check = {false, false, false, false, false, false};
        for (int i = 0; i < 6; i++) {
            int temp;
            std::cin >> temp;
            if (temp >= 1 && temp <= 6 && !red_check[temp]) {
                std::cout << "Red piece " << temp << " verification passed" << std::endl;
                red_chess.push_back(temp);
                red_check[temp] = true;
            } else {
                std::cout << "Red piece " << temp << " verification failed" << std::endl;
                i--;
            }
        }
        std::cout << "Final input for red pieces: " << std::endl;
        for (auto chess : red_chess) {
            std::cout << chess << " ";
        }
        std::cout << std::endl;
        std::cout << "Please enter the layout of blue chess pieces from from bottom to top, right to left: "<< std::endl;
        std::vector<int> blue_chess;
        std::vector<bool> blue_check = {false, false, false, false, false, false};
        for (int i = 0; i < 6; i++) {
            int temp;
            std::cin >> temp;
            if (temp >= 1 && temp <= 6 && !blue_check[temp]) {
                std::cout << "Blue piece " << temp << " verification passed" << std::endl;
                blue_chess.push_back(temp);
                blue_check[temp] = true;
            } else {
                std::cout << "Blue piece " << temp << " verification failed" << std::endl;
                i--;
            }
        }
        std::cout << "Final input for blue pieces: " << std::endl;
        for (auto chess : blue_chess) {
            std::cout << chess << " ";
        }
        GameGUI *game = new GameGUI(red_chess, blue_chess);
        game->start();
    }
}