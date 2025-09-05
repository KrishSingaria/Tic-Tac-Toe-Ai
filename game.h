#pragma once // prevents the compiler from including this file multiple times
#include <utility>
#include <vector>

class game
{
private:
    char board[3][3];
    char DEFAULT = '_';
    char playerSymbol = 'X';
    char aiSymbol = 'O';
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
    // score for ai part 
    int getScore(char playerSymbol,char winner);
    // ai algo
    int minimax(bool isMaximizing, int depth); // Add the depth parameter
    // for best ai moves
    std::pair<int, int> findBestMove();
};
