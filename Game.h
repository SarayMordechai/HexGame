#ifndef __GAME_H
#define __GAME_H

const int N = 11;

class Game
{
private:
    int beeHive[N][N];
    enum PlayerColor
    {
        Blue,
        Red
    };
    PlayerColor curPlayerColor;
public:
    Game();
    virtual ~Game();
    bool ExecNextMove(int moveRowInd, int moveColIn);
    bool getNextMove(int& moveRowInd, int& moveColInd);
    bool checkIfAnybodyWon(int row, int col, PlayerColor playerColor);
    bool checkIfAnybodyWon(int row, int col, bool markedCells[N][N], PlayerColor playerColor);
    void printBeeHive(int beeHiveArr[N][N]);
    void printMarkedCells(bool markedCells[N][N]);
    void Play();
};


#endif
