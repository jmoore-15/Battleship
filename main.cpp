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

    gameBoard.printBoard();

    // Game Loop Start
    while(userShipsLeft != 0 && computerShipsLeft != 0) {
        // Player X inputs valid attack grid
        // Check to see if attack is a hit
        // Remove/add damage to hit ships
        // Redraw game board
        // Check to see if game is over
        // If game over - exit loop/end program
        // Toggle next player's turn

        userShipsLeft--;
        computerShipsLeft--;
    }

    // Game Loop Return
    delete aircraft;
    delete battleship;
    delete submarine;
    delete destroyer;
    delete patrol;

    return 0;
}