#ifndef CHESS_H
#define CHESS_H

#include "Game.h"
#include <iostream>

class Chess : public Game {
public:
    void foo()
    {
        std::cout << playersCount << std::endl;
    }

    /* Implementation of necessary concrete methods */
    void initGame() {
        std::cout << "Init chess game" << std::endl;
        // Initialize players
        // Put the pieces on the board
    }
    void makePlay(int player) {
        // Process a turn for the player
        std::cout << "Made chess play" << std::endl;
    }
    bool endOfGame() {
        // Return true if in Checkmate or 
        // Stalemate has been reached
        std::cout << "Chess end of game" << std::endl;
        return true;
    }
    void printWinner() {
        // Display the winning player
        std::cout << "Chess winner!" << std::endl;
    }
    /* Specific declarations for the chess game. */

    // ...
};


#endif