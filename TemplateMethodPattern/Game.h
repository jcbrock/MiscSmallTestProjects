#ifndef GAME_H
#define GAME_H

class Game
{
protected:
    int playersCount;

public:
    virtual void initGame();
    virtual void makePlay(int player);
    virtual bool endOfGame();
    virtual void printWinner();

    /* A template method : */
    void playOneGame(int playersCount) {
        this->playersCount = playersCount;
        initGame();
        int j = 0;
        while (!endOfGame()) {
            makePlay(j);
            j = (j + 1) % playersCount;
        }
        printWinner();
    }
};

#endif