#include "game.h"
#include <iostream>
#include <vector>

game::game(){
    for(int i = 0; i < 9; i++){
        // Initialize with '1' through '9'
        // board[i / 3][i % 3] = (char)(i + 1 + '0');
        board[i / 3][i % 3] = DEFAULT;
    }
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
        && board[1][1] != '_'){
     
        return board[1][1];
    }
    if(hasEmptySpots){
        return '_';
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
  // Logic to fill the board with '_'
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      board[i][j] = '_';
    }
  }
}