#include <iostream>
using namespace std;

class gameBoard {
    private:
        // board dimensions
        static const int boardWidth = 7;
        static const int boardHeight = 6;
        // board characters
        static const char p1Char = 'X';
        static const char p2Char = 'O';
        static const char boardChar = '#';
        // game state & player turn
        bool gameState = true;
        bool p1turn = true;
        bool tieState = false;
        // arrays used
        char board[boardWidth][boardHeight];
        int columnHeight[boardWidth];

    public:
        gameBoard() {
            // Initializes all game slots to 0 to represent empty board
            for(int i = 0; i < boardWidth; i++) {
                for(int j = 0; j < boardHeight; j++) {
                    board[i][j] = boardChar;
                }
            }

            // Initializes each column's height 
            for(int i = 0; i < boardWidth; i++) {
                columnHeight[i] = -1;
            }
        }

        bool returnGameState() {
            return gameState;
        }

        bool returnTurnState() {
            return p1turn;
        }

        void drawBoard() {
            // Clears console
            clearConsole();
            
            // Draws title and top border
            cout << endl;
            cout << "-CONNECT FOUR-" << endl;
            cout << endl;
            cout << "-------------" << endl;

            // Draws board
            for(int i = boardHeight - 1; i >= 0; i--) {
                for(int j = 0; j < boardWidth; j++) {
                    cout << board[j][i] << " ";
                }

                cout << endl;
            }

            // Draws bottom border
            cout << "-------------" << endl;

            // Draws numbers under board
            for(int i = 0; i < boardWidth; i++) {
                cout << i + 1 << " ";
            }
            cout << endl << endl;
        }

        // Handles player movement
        void p1Move() {
            int inputColumn;

            // Asks player what column they would like inputted
            cout << "(Player 1) Insert your move: ";
            cin >> inputColumn;
            
            // Checks to make sure input is within the board
            while(inputColumn <= 0 || (inputColumn > boardWidth || columnHeight[inputColumn - 1] + 2 > boardHeight)) {
                cout << "Invalid placement, insert move: ";
                cin >> inputColumn;
            }
            
            move(inputColumn, p1Char);
            p1turn = false;
        }

        void p2Move() {
            int inputColumn;

            // Asks player what column they would like inputted
            cout << "(Player 2) Insert your move: ";
            cin >> inputColumn;
            
            // Checks to make sure input is within the board
            while(inputColumn <= 0 || (inputColumn > boardWidth || columnHeight[inputColumn - 1] + 2 > boardHeight)) {
                cout << "Invalid placement, insert move: ";
                cin >> inputColumn;
            }
            
            move(inputColumn, p2Char);
            p1turn = true;
        }

        // Input moves
        void move(int inputColumn, char inputCharacter) {
            // Iterates that array place in columnHeight
            inputColumn--;
            columnHeight[inputColumn]++;

            // Adjusts main array using new columnHeight value
            board[inputColumn][columnHeight[inputColumn]] = inputCharacter;
        }

        bool winningPosition() {
            int count = 0;
            char input;

            // Checks for character based on whose turn it is
            if(p1turn) {
                input = p2Char;
            } else {
                input = p1Char;
            }

            // Horizontal Check
            count = 0;
            for(int cookie = 0; cookie < boardHeight; cookie++) {
                for(int i = 0; i < boardWidth; i++) {
                    if(board[i][cookie] == input) {
                        count++;
                    } else {
                        count = 0;
                    }

                    // If four in a row found horizontally, return true
                    if(count >= 4) {
                        gameState = false;
                        return true;
                    }
                }
            }
            

            // Vertical Check
            count = 0;
            for(int j = 0; j < boardWidth; j++) {
                for(int i = 0; i < boardHeight; i++) {
                    if(board[j][i] == input) {
                        count++;
                    } else {
                        count = 0;
                    }

                    // If four in a row found vertically, return true
                    if(count >= 4) {
                        gameState = false;
                        return true;
                    }
                }
            }

            // Diagonal Check (bottom left to top right)
            for(int rowStart = 0; rowStart < boardWidth - 4; rowStart++) {
                count = 0;
                int row, col;
                for(row = rowStart, col = 0; row < boardWidth && col < boardHeight; row++, col++) {
                    if(board[row][col] == input) {
                        count++;
                        if(count >= 4) {
                            gameState = false;
                            return true;
                        }
                    } else {
                        count = 0;
                    }
                }
            }

            // Diagonal Check (bottom right to top left)
            for(int rowStart = boardWidth - 1; rowStart >= 0; rowStart--) {
                count = 0;
                int row, col;
                for(row = rowStart, col = 0; row >= 0 && col < boardHeight; row--, col++) {
                    if(board[row][col] == input) {
                        count++;
                        if(count >= 4) {
                            gameState = false;
                            return true;
                        }
                    } else {
                        count = 0;
                    }
                }
            }
            
            return false;
        }

        void clearConsole() {
            #if defined _WIN32
                system("cls");
            #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
                system("clear");
            #elif defined (__APPLE__)
                system("clear");
            #endif
        }
};