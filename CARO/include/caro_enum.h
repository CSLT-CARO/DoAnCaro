#ifndef CARO_ENUM_H
#define CARO_ENUM_H

enum PlayerMark {
    Empty, X, O
};

enum Mode {
    PVE, PVP
};

enum Difficulty {
    Easy, Normal, Hard, Null
};

enum BoardType {
    Classic, Ultimate
};

enum State {
    StartScreen,
    ChooseMode,
    ChooseDifficulty,
    ChooseBoardType,
    MainGame,
    PlayAgain,
    Exit
};

#endif