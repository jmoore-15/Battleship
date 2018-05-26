#include "board.h"

int main() {
    // Initialize default variables
    int userShipsLeft = 5;
    int computerShipsLeft = 5;

    // Create computers game board
    board gameBoard;

    // Create computers ships
    auto aircraft = board::ship(5);
    auto battleship = board::ship(4);
    auto submarine = board::ship(3);
    auto destroyer = board::ship(3);
    auto patrol = board::ship(2);

    // Place computers ships
    aircraft.placeShip();
    battleship.placeShip();
    submarine.placeShip();
    destroyer.placeShip();
    patrol.placeShip();

    // Game Loop Start
        // Player X inputs valid attack grid
        // Check to see if attack is a hit
        // Remove/add damage to hit ships
        // Redraw game board
        // Check to see if game is over
            // If game over - exit loop/end program
        // Toggle next player's turn
    // Game Loop Return
    return 0;
}