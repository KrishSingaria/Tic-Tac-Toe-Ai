#include "game.h"
#include <iostream>
#include <vector>
#include <utility> 

game::game(){
    this->playerSymbol = 'X';
    this->aiSymbol = 'O';
    this->DEFAULT = '_';
    this->reset();
}

void game::printBoard(){
    std::cout<<'\n';
    for(int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
        {
            std::cout<<board[i][j]<<" ";
        }
        std::cout<<'\n';
    }
}

bool game::makeMove(std::string playerStr, int position){
    if(playerStr.empty()){
        return false;
    }
    int row = (position - 1)/ 3, col = (position-1)%3;
    if(board[row][col] != DEFAULT){
        return false; // not valid move
    }
    board[row][col] = playerStr[0];
    return true; // valid move
}

char game::checkWinner(){
    // count check {X,O} for both
    std::vector<std::pair<int,int>> rows(3,std::make_pair(0,0)),cols(3,std::make_pair(0,0));
    bool hasEmptySpots = false;
    for(int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
        {
            if(board[i][j] == 'X'){
                if(++rows[i].first == 3 || ++cols[j].first == 3)
                    return 'X';
            }else if (board[i][j] == 'O'){
                if(++rows[i].second == 3 || ++cols[j].second == 3)
                    return 'O';
            }else{
                hasEmptySpots = true; // game going on
            }
        }
    }
    //diagonal checks
    if(((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || 
        (board[2][0] == board[1][1] && board[1][1] == board[0][2])) 
        && board[1][1] != this->DEFAULT){
     
        return board[1][1];
    }
    if(hasEmptySpots){
        return this->DEFAULT;
    }
    return 'D'; // Draw
}

std::string game::getBoardState(){
    std::string str = "";
    for (int i = 0; i < 9; i++)
    {
        str += board[i/3][i%3];
    }
    return str;
}

void game::reset() {
  // Logic to fill the board with this->DEFAULT
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      board[i][j] = this->DEFAULT;
    }
  }
}

int game::getScore(char playerSymbol,char winner){
    if(winner == playerSymbol){
        return -10;
    }else if (winner == 'D'){
        return 0;
    }else{
        return 10;
    }
}

int game::minimax(bool isMaximizing, int depth) {
    char winner = this->checkWinner();
    if (winner != this->DEFAULT) {
        int score = this->getScore(this->playerSymbol, winner);

        if (score == 10) { // AI Win
            return score - depth; // We want to win fast
        } else if (score == -10) { // Player Win (AI Loss)
            return score + depth; // We want to lose slow
        } else { 
            return 0;
        }
    }
    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (board[i][j] == this->DEFAULT) {
                    board[i][j] = this->aiSymbol;
                    bestScore = std::max(bestScore, minimax(false, depth + 1));
                    board[i][j] = this->DEFAULT;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;

        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (board[i][j] == this->DEFAULT) {
                    board[i][j] = this->playerSymbol;
                    bestScore = std::min(bestScore, minimax(true, depth + 1));
                    board[i][j] = this->DEFAULT;
                }
            }
        }
        return bestScore;
    }
}

std::pair<int, int> game::findBestMove(){
    // --- OPENING BOOK MOVE ---
    // If it's the AI's first move of the game, check for the optimal opening.
    int emptySquares = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == this->DEFAULT) {
                emptySquares++;
            }
        }
    }
    if (emptySquares == 9 && board[1][1] == this->DEFAULT) {
        return {1, 1}; // Instantly return the center move {row, col}
    }

    int bestScore = -1000;
    std::pair<int, int> bestMove = {-1, -1};

    // Loop through all cells, just like in minimax
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            // Check if the spot is empty
            if (board[i][j] == this->DEFAULT) {
                board[i][j] = this->aiSymbol;
                int moveScore = this->minimax(false,0); // 'false' because it's player's turn
                board[i][j] = this->DEFAULT;
    
                if(moveScore > bestScore){
                    bestScore = moveScore;
                    bestMove = std::make_pair(i,j);
                }
            }
        }
    }

    return bestMove;
}