#ifndef START_SCREEN_H
#define START_SCREEN_H

#include "game_state.h"

void printStartScreen() {
    std::cout << "=== CARO ===\n";
    std::cout << "1. Start Game\n";
    std::cout << "2. Load Game\n";
    std::cout << "3. Settings\n";
    std::cout << "4. Quit\n";
    std::cout << "> ";
}

void inputStartScreen(GameState& game_state) {
    int user_choice{};
    std::cin >> user_choice;

    switch (user_choice) {
    case 1: 
        game_state.current_state = ChooseMode;
    case 2: case 3: break;
    case 4: 
        game_state.current_state = Exit;
    }
}

void processStartScreen(GameState& game_state) {
    printStartScreen();
    inputStartScreen(game_state);
}

#endif