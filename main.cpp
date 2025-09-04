#include "game.h"
#include <iostream>
#include <emscripten.h>
#include <emscripten/bind.h>

using namespace emscripten;

// This block exposes our C++ Game class to JavaScript
EMSCRIPTEN_BINDINGS(my_game_module) {
    class_<game>("Game")
        .constructor<>() // This exposes the constructor (e.g., new Game())
        .function("makeMove", &game::makeMove)
        .function("checkWinner", &game::checkWinner)
        .function("getBoardState", &game::getBoardState)
        .function("reset", &game::reset);
        // We can't easily use printBoard, since it prints to the C++ console.
        // Let's add a new function to get the board state instead!
};







// terminal game
// int main() {
//     game ticTacToe;
//     char currentPlayer = 'X';
    
//     // A simple game loop that runs forever (for now)
//     while (true) {
        
//         ticTacToe.printBoard();
//         // Ask currentPlayer for their move
//         std::cout<<"Enter your move(1-9) player "<<currentPlayer<<" :";
//         // Get input from std::cin
//         int position;
//         std::cin>>position;
//         // Try to make the move using ticTacToe.makeMove()
//         bool canMake = ticTacToe.makeMove(currentPlayer,position);
//         // If the move was valid
//         if(!canMake){
//             std::cout << "Can not make this move for player " <<currentPlayer<<'\n';
//             continue; // play again
//         }

//         // Check for a result
//         char result = ticTacToe.checkWinner();

//         // If the game is NOT ongoing, it's over!
//         if (result != '_') {
//             // Maybe print the final board one last time so they can see the win
//             ticTacToe.printBoard();
//             // Announce the winner or a draw based on 'result'
//             if(result != 'D'){
//                 std::cout << "Congratulation!! You won! "<< currentPlayer << std::endl;
//             }else
//             {
//                 std::cout << "Game DRAW" << std::endl;
//             }
//             //The most important part: escape the loop!
//             break;
//         }
//         // switch the player
//         currentPlayer = (currentPlayer == 'X') ? 'O': 'X';
//     }

//     return 0;
// }