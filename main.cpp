#include "board.h"

int main() {
    // Initialize default variables
    int userShipsLeft = 5;
    int computerShipsLeft = 5;

    // Create computers game board
    board cGameBoard = board();

    // Create computers ships
    board::ship* cAircraft = new board::ship("a", 5);
    board::ship* cBattleship = new board::ship("b", 4);
    board::ship* cSubmarine = new board::ship("s", 3);
    board::ship* cDestroyer = new board::ship("d", 3);
    board::ship* cPatrol = new board::ship("p", 2);

    // Place computers ships
    cAircraft->placeShip(cGameBoard);
    cBattleship->placeShip(cGameBoard);
    cSubmarine->placeShip(cGameBoard);
    cDestroyer->placeShip(cGameBoard);
    cPatrol->placeShip(cGameBoard);

    // Spots a computer can guess
    vector<string> potentialGuesses = {
            "A10", "A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9",
            "B10", "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9",
            "C10", "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9",
            "D10", "D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9",
            "E10", "E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9",
            "F10", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9",
            "G10", "G1", "G2", "G3", "G4", "G5", "G6", "G7", "G8", "G9",
            "H10", "H1", "H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9",
            "I10", "I1", "I2", "I3", "I4", "I5", "I6", "I7", "I8", "I9",
            "J10", "J1", "J2", "J3", "J4", "J5", "J6", "J7", "J8", "J9",
    };

    // Create users game board
    board uGameBoard = board();

    // Create users ships
    board::ship* uAircraft = new board::ship("a", 5);
    board::ship* uBattleship = new board::ship("b", 4);
    board::ship* uSubmarine = new board::ship("s", 3);
    board::ship* uDestroyer = new board::ship("d", 3);
    board::ship* uPatrol = new board::ship("p", 2);

    // Place users ships (Until I figure out how best to place user inputted ships, have it be random)
    uAircraft->placeShip(uGameBoard);
    uBattleship->placeShip(uGameBoard);
    uSubmarine->placeShip(uGameBoard);
    uDestroyer->placeShip(uGameBoard);
    uPatrol->placeShip(uGameBoard);

    cout << endl << "Users Board" << endl;
    uGameBoard.printBoard();
    cout << endl << "Computers board" << endl;
    cGameBoard.printBoard();
    cout << endl;

    // Game Loop Start
    string userGuess;
    string computerGuess;
    while(computerShipsLeft != 0 && userShipsLeft != 0) {

        // User guesses a place
        cout << "Guess (e.g. E4): ";
        cin >> userGuess;

        // Was it a hit or a miss for the user?
        if(cGameBoard.markHitOrMiss(userGuess))
            computerShipsLeft--;

        // Computer guesses a place
        auto pGuessSize = (int)potentialGuesses.size(); // The size of the potentialGuesses vector
        int randomIndex = rand() % pGuessSize;          // A random index in that vector
        computerGuess = potentialGuesses[randomIndex];

        cout << "The computer guesses " << computerGuess << endl;
        potentialGuesses.erase(potentialGuesses.begin() + randomIndex);

        // Was it a hit or a miss for the computer?
        if(uGameBoard.markHitOrMiss(computerGuess))
            userShipsLeft--;
    }

    if(userShipsLeft == 0) {
        cout << "Unfortunately the computer won, but thanks for playing!" << endl;
    }
    else {
        cout << "You won! Thanks for playing!" << endl;
    }

    // Game Loop Return
    delete cAircraft;
    delete cBattleship;
    delete cSubmarine;
    delete cDestroyer;
    delete cPatrol;

    delete uAircraft;
    delete uBattleship;
    delete uSubmarine;
    delete uDestroyer;
    delete uPatrol;

    return 0;
}