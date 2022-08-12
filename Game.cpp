#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Game.h"

const char* ErrorMessage = "Invalid move; the game awaits a valid move.\n";
const char* QuitMessage = "QUIT";
const char* WinnerMsg = " wins the game.";

using namespace std;

Game::Game()
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            beeHive[i][j] = 0;
        }

    }
    curPlayerColor = Blue;
}

Game::~Game()
{

}

// return true if no won the game and we can do the next move.
// return false if someone won the game.
bool Game::ExecNextMove(int moveRowInd, int moveColInd)
{
    beeHive[moveRowInd][moveColInd] = curPlayerColor == Blue ? 1 : 2;

    printBeeHive(beeHive);

    if (checkIfAnybodyWon(0, 0, curPlayerColor))
    {
        return false;
    }
    curPlayerColor = curPlayerColor == Blue ? Red : Blue;
    return true;
}

//A function that receives the input and checks if it is correct
bool Game::getNextMove(int& moveRowInd, int& moveColInd)
{
    string move;
    while (true)
    {
        cout << (curPlayerColor == Blue ? "B:" : "R:") << endl;
        getline(cin, move);
        int moveStrLen = move.size();
        if (move == QuitMessage)
        {
            cout << (curPlayerColor == Blue ? "B: " : "R: ") << QuitMessage << endl;
            break;
        }
        else if (moveStrLen >= 2 && moveStrLen <= 3)
        {
            string rowNumStr = move.substr(1, 2);
            int rowNum = atoi(rowNumStr.c_str());
            if (move[0] < 'A' || move[0] > 'K' || rowNum < 1 || rowNum > 11)
            {
                cout << ErrorMessage;
            }
            else
            {
                moveColInd = move[0] - 'A';
                moveRowInd = rowNum - 1;
                if (beeHive[moveRowInd][moveColInd] == 0)
                {
                    return true;
                }
                else
                {
                    cout << ErrorMessage<<endl;
                }

            }
        }
        else
        {
            cout << ErrorMessage<<endl;
        }
    }
    return false;
}


bool Game::checkIfAnybodyWon(int row, int col, PlayerColor playerColor)
{
    bool markedCells[N][N];
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            markedCells[i][j] = false;
        }
    }
    return checkIfAnybodyWon(row, col, markedCells, playerColor);
}

//Neighborhood check to find out who completed a line
bool Game::checkIfAnybodyWon(int row, int col, bool markedCells[N][N], PlayerColor playerColor)
{
    if (row >= 0 && row < N && col >= 0 && col < N
        && (beeHive[row][col] == (curPlayerColor == Blue ? 1 : 2))
        && !markedCells[row][col])
    {
        markedCells[row][col] = true;

        if ((playerColor == Blue && col == (N - 1)) ||
            (playerColor == Red && row == (N - 1)))
            return true;
        if (checkIfAnybodyWon(row - 1, col, markedCells, playerColor))
            return true;
        if (checkIfAnybodyWon(row, col - 1, markedCells, playerColor))
            return true;
        if (checkIfAnybodyWon(row + 1, col, markedCells, playerColor))
            return true;
        if (checkIfAnybodyWon(row, col + 1, markedCells, playerColor))
            return true;
        if (checkIfAnybodyWon(row - 1, col + 1, markedCells, playerColor))
            return true;
        if (checkIfAnybodyWon(row + 1, col - 1, markedCells, playerColor))
            return true;
    }
    return false;
}

void Game::printBeeHive(int beeHiveArr[N][N])
{
    for (size_t i = 0; i < N; i++)
    {
        cout << string(i, ' ');
        for (size_t j = 0; j < N; j++)
        {
            char curCellSign;
            if (beeHiveArr[i][j] == 0)
            {
                curCellSign ='O';
            }
            else if (beeHiveArr[i][j] == 1)
            {
                curCellSign ='B';
            }
            else if (beeHiveArr[i][j] == 2)
            {
                curCellSign ='R';
            }
            cout << curCellSign;
            if (j != N - 1)
            {
                cout << " ";
            }
        }
        cout << "\n";
    }
}
 //Board printing
void Game::printMarkedCells(bool markedCells[N][N])
{
    for (size_t i = 0; i < N; i++)
    {
        cout << string(i, ' ');
        for (size_t j = 0; j < N; j++)
        {
            char curCellSign;
            if (markedCells[i][j] == 0)
            {
                curCellSign = '0';
            }
            else if (markedCells[i][j] == 1)
            {
                curCellSign = 'B';
            }
            else if (markedCells[i][j] == 2)
            {
                curCellSign = 'R';
            }
            cout << curCellSign <<" ";
        }
        cout << endl;
    }
}

//A function that activates the game
void Game::Play()
{
    bool shouldStay = true;
    int moveRowInd, moveColInd;
    printBeeHive(beeHive);
    while (shouldStay)
    {
        shouldStay = getNextMove(moveRowInd, moveColInd);
        if (shouldStay)
        {
            shouldStay = ExecNextMove(moveRowInd, moveColInd);
            if (!shouldStay)
            {
                cout << (curPlayerColor == Blue ? "B" : "R") << WinnerMsg<<endl;
            }
        }
        else
        {
            printBeeHive(beeHive);
            cout << (curPlayerColor == Blue ? "R" : "B") << WinnerMsg<<endl;
        }
    }
}
