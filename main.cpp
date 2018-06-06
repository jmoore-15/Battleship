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

    // Computer check hit
    string lastHitOnUser = "none";

    // Spots a computer can guess
    vector<string> potentialGuesses = {
        "A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "A10",
        "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9", "B10",
        "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C10",
        "D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10",
        "E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "E10",
        "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10",
        "G1", "G2", "G3", "G4", "G5", "G6", "G7", "G8", "G9", "G10",
        "H1", "H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9", "H10",
        "I1", "I2", "I3", "I4", "I5", "I6", "I7", "I8", "I9", "I10",
        "J1", "J2", "J3", "J4", "J5", "J6", "J7", "J8", "J9", "J10"
    };

    // Create users game board
    board uGameBoard = board();

    // Create users ships
    board::ship* uAircraft = new board::ship("a", 5);
    board::ship* uBattleship = new board::ship("b", 4);
    board::ship* uSubmarine = new board::ship("s", 3);
    board::ship* uDestroyer = new board::ship("d", 3);
    board::ship* uPatrol = new board::ship("p", 2);

    uAircraft->placeShip(uGameBoard);
    uBattleship->placeShip(uGameBoard);
    uSubmarine->placeShip(uGameBoard);
    uDestroyer->placeShip(uGameBoard);
    uPatrol->placeShip(uGameBoard);

    /*
    // Place the aircraft
    uGameBoard.printCompleteBoard();
    string A1, A2, A3, A4, A5;
    cout << "Please enter a valid 5 spaces for the aircraft. Example is A1 A2 A3 A4 A5:  ";
    cin >> A1 >> A2 >> A3 >> A4 >> A5;
    cout << endl;
    string air[5] = { A1, A2, A3, A4, A5 };
    uGameBoard.placeUserShips(air, "a", uAircraft);

    // Place the battleship
    uGameBoard.printCompleteBoard();
    string B1, B2, B3, B4;
    cout << "Please enter a valid 4 spaces for the battleship. Example is A1 A2 A3 A4:  ";
    cin >> B1 >> B2 >> B3 >> B4;
    cout << endl;
    string battle[4] = { B1, B2, B3, B4 };
    uGameBoard.placeUserShips(battle, "b", uBattleship);

    // Place the submarine
    uGameBoard.printCompleteBoard();
    string S1, S2, S3;
    cout << "Please enter a valid 3 spaces for the submarine. Example is A1 A2 A3:  ";
    cin >> S1 >> S2 >> S3;
    cout << endl;
    string sub[3] = { S1, S2, S3 };
    uGameBoard.placeUserShips(sub, "s", uSubmarine);

    // Place the destroyer
    uGameBoard.printCompleteBoard();
    string D1, D2, D3;
    cout << "Please enter a valid 3 spaces for the destroyer. Example is A1 A2 A3:  ";
    cin >> D1 >> D2 >> D3;
    cout << endl;
    string destroy[3] = { D1, D2, D3 };
    uGameBoard.placeUserShips(destroy, "d", uDestroyer);

    // Place the patrol
    uGameBoard.printCompleteBoard();
    string P1, P2;
    cout << "Please enter a valid 2 spaces for the patrol. Example is A1 A2:  ";
    cin >> P1 >> P2;
    cout << endl;
    string pat[2] = { P1, P2 };
    uGameBoard.placeUserShips(pat, "p", uPatrol);
    */

    uGameBoard.printCompleteBoard();

    // Game Loop Start
    string userGuess;
    string computerGuess;
    while(computerShipsLeft != 0 && userShipsLeft != 0) {

        /**** User section ****/
        cout << "Guess (e.g. E4): ";
        cin >> userGuess;

        // Was it a hit or a miss for the user?
        string wasCompShipSunk = cGameBoard.checkHitOrMiss(userGuess); // Could return s, h, m
        if(wasCompShipSunk == "s")
            computerShipsLeft--;

        /**** If the computers last guess was a hit and they didn't sink a ship ****/
        if(lastHitOnUser != "none") {
            string wasUserShipSunk = uGameBoard.makeGuessIfPreviousHit(lastHitOnUser, &potentialGuesses); // Could return s, h, m, or coord
            if(wasUserShipSunk == "s") {
                lastHitOnUser = "none";          // We sunk a ship, so set the lastHitOnUser to none so we don't check
                userShipsLeft--;
            }
            else if(wasUserShipSunk != "m")      // We hit a ship, so set the lastHitOnUser to the current coordinate
                lastHitOnUser = wasUserShipSunk; // Returns the guessed coordinate
        }
        /**** If the computers last guess was not a hit ****/
        else {
            auto pGuessSize = (int)potentialGuesses.size(); // The size of the potentialGuesses vector
            int randomIndex = rand() % pGuessSize;          // A random index in that vector
            computerGuess = potentialGuesses[randomIndex];  // Obtain that coordinate

            cout << "The computer guesses " << computerGuess << endl;
            potentialGuesses.erase(potentialGuesses.begin() + randomIndex);

            string wasUserShipSunk = uGameBoard.checkHitOrMiss(computerGuess); // Could return s, h, m
            if(wasUserShipSunk == "s") {
                lastHitOnUser = "none";      // We sunk a ship, so set the lastHitOnUser to none so we don't check
                userShipsLeft--;
            }
            else if(wasUserShipSunk == "h")  // We hit a ship, so set the lastHitOnUser to the current coordinate
                lastHitOnUser = computerGuess;
        }

        cout << endl << "Users Board" << endl;
        uGameBoard.printCompleteBoard();
        cout << endl << "Computers board" << endl;
        cGameBoard.printEnemyBoard();
        cout << endl;
    }

    if(userShipsLeft == 0) {
        cout << "Unfortunately the computer won, but thanks for playing!" << endl;
    }
    else {
        cout << "You won! Thanks for playing!" << endl;
    }

    // Delete anything that was dynamically allocated
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

    for(int row = 0; row < 10; row++) {
        for(int col = 0; col < 10; col++) {
            delete uGameBoard.gameMatrix[row][col];
            delete cGameBoard.gameMatrix[row][col];
        }
    }

    return 0;
}