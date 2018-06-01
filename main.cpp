#include "board.h"

int main() {
    // Initialize default variables
    int userShipsLeft = 5;
    int computerShipsLeft = 5;

    // Create computers game board
    board gameBoard = board();

    // Create computers ships
    board::ship* aircraft = new board::ship("a", 5);
    board::ship* battleship = new board::ship("b", 4);
    board::ship* submarine = new board::ship("s", 3);
    board::ship* destroyer = new board::ship("d", 3);
    board::ship* patrol = new board::ship("p", 2);

    // Place computers ships
    aircraft->placeShip(gameBoard);
    battleship->placeShip(gameBoard);
    submarine->placeShip(gameBoard);
    destroyer->placeShip(gameBoard);
    patrol->placeShip(gameBoard);

    // gameBoard.printBoard();

    string userGuess;

    // Game Loop Start
    while(computerShipsLeft != 0) {

        // User guesses a place
        cout << "Guess (e.g. E4): ";
        cin >> userGuess;

        // Was it a hit or a miss?
        if(gameBoard.markHitOrMiss(userGuess)) {
            computerShipsLeft--;
        }

        // gameBoard.printBoard();

        // Redraw game board
        // Check to see if game is over
        // If game over - exit loop/end program
        // Toggle next player's turn
    }

    // Game Loop Return
    delete aircraft;
    delete battleship;
    delete submarine;
    delete destroyer;
    delete patrol;

    return 0;
}