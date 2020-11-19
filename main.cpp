#include "board.h"

int main() {
    // Create Board
    gameBoard game = gameBoard();
    game.drawBoard();

    // Starts game
    while(game.returnGameState()) {
        // Inputs player moves, draws board, and then checks for winning position
        game.p1Move();
        game.drawBoard();
        game.winningPosition();

        // Checks if player won, if not then does computer move, draws the board, and then checks if won
        if(game.returnGameState()) {
            game.p2Move();
            game.drawBoard();
            game.winningPosition();
        } 
        
    }
    
    // Handles game ending
    cout << "GAME END" << endl;
    if(!game.returnTurnState()) {
        cout << "Player 1 has won!" << endl;;
    } else {
        cout << "Player 2 has won!" << endl;
    }
    
}