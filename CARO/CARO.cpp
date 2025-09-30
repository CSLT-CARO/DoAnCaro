#include <iostream>
#include <stdlib.h>
#include "start_screen.h"
#include "choose_mode_screen.h"
#include "choose_difficulty_screen.h"
#include "choose_board_screen.h"
#include "main_game_screen.h"
#include "play_again_screen.h"

int main() {
    GameState game_state {};
    game_state.current_state = StartScreen;
    
    while (true) {
        system("cls");
        switch (game_state.current_state) {
            case StartScreen:
                std::cout << '\n';
                processStartScreen(game_state);
                break;
            case ChooseMode:
                std::cout << '\n';
                processChooseModeScreen(game_state);
                break;
            case ChooseDifficulty:
                std::cout << '\n';
                processChooseDifficulty(game_state);
                break;
            case ChooseBoardType:
                std::cout << '\n';
                processChooseBoardType(game_state);
                break;
            case MainGame:
                std::cout << '\n';
                processCurrentGame(game_state);
                break;
            case PlayAgain:
                std::cout << '\n';
                processPlayAgainScreen(game_state);
                break;
            case Exit:
                std::cout << "exited";
                exit(0);
        }
    }
    
    return 0;
}