#ifndef MONOPOLY_H
#define MONOPOLY_H

#include "Game.h"
#include <iostream>

class Monopoly : Game {

    /* Implementation of necessary concrete methods */
    void initGame() {
        std::cout << "Init Monopoly game" << std::endl;
        // Initialize players
        // Put the pieces on the board
    }
    void makePlay(int player) {
        // Process a turn for the player
        std::cout << "Made Monopoly play" << std::endl;
    }
    bool endOfGame() {
        // Return true if in Checkmate or 
        // Stalemate has been reached
        std::cout << "Monopoly end of game" << std::endl;
        return true;
    }
    void printWinner() {
        // Display the winning player
        std::cout << "Monopoly winner!" << std::endl;
    }
    /* Specific declarations for the Monopoly game. */

    // ...
};

#endif