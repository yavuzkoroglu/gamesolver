#ifndef GAMES_H
    #define GAMES_H
    #include "padkit/preprocessor.h"

    #ifndef GAMES_DIR
        #define GAMES_DIR           games
    #endif

    #ifndef POSINFO_HDR
        #define POSINFO_HDR         posinfo.h
    #endif

    #ifndef GAME_ID
        #define GAME_ID             0
        #define GAME_NAME           chess1d
    #elif GAME_ID==0
        #define GAME_NAME           chess1d
    #elif GAME_ID==1
        #define GAME_NAME           rubiks2by2
    #elif GAME_ID==2
        #define GAME_NAME           tictactoe
    #elif GAME_ID==3
        #define GAME_NAME           upsidedown
    #else
        #error Unknown GAME_ID
    #endif

    #ifndef GAME_POSINFO_HDR
        #define GAME_POSINFO_HDR    STR(GAMES_DIR/GAME_NAME/POSINFO_HDR)
    #endif
#endif
