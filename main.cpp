#include "board.h"

int main() {
    // Initialize default variables
    int userShipsLeft = 5;
    int computerShipsLeft = 5;

    // Create computers game board
    board gameBoard;

    // Create computers ships
    auto aircraft = board::ship("aircraft", 5);
    auto battleship = board::ship("battleship", 4);
    auto submarine = board::ship("submarine", 3);
    auto destroyer = board::ship("destroyer", 3);
    auto patrol = board::ship("patrol", 2);

    // Place computers ships
    aircraft.placeShip(gameBoard);
    battleship.placeShip(gameBoard);
    submarine.placeShip(gameBoard);
    destroyer.placeShip(gameBoard);
    patrol.placeShip(gameBoard);

    // TODO: Print out the board after all the ships have been randomly placed (not working)
    cout << "  | 1 2 3 4 5 6 7 8 9 10 " << endl;
    cout << "------------------------" << endl;
    char letter1 = 'A';
    for(int i = 0; i < 10; i++) {
        cout << letter1 << " | ";
        for (int j = 0; j < 10; j++) {
            cout << gameBoard.gameMatrix[i][j].taken << " ";
        }
        cout << endl;
        letter1++;
    }

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
    return 0;
}