#pragma once // prevents the compiler from including this file multiple times

#include <vector>

class game
{
private:
    char board[3][3];
    char DEFAULT = '_';
public:
    game();
    // prints the board
    void printBoard();
    // act as print for javascript
    std::string getBoardState();
    // make moves postition 1-9
    bool makeMove(std::string playerStr, int position);
    // check the winner
    char checkWinner();
    // reset
    void reset();
};
