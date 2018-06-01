#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <vector>
using namespace std;

/* e.g. '4' turns into 'E' */
string intCoordToString(int num) {
    char letter = 'A';
    for(int i = 0; i < num; i++)
        letter++;

    string inStringForm = "";
    return inStringForm += letter;
}

/* Guess can only have first as character A to J and second as integer 1 - 10 */
bool isItValidGuess(string guess) {
    if(guess.size() < 2 || guess.size() > 3) // e.g. not E4 or E10
        return false;

    bool validChoice = true;

    // e.g. This would be the 'E' in 'E4'
    char charChoices[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    char first = guess[0];
    for(int i = 0; i < 10; i++) {
        if(first != charChoices[i])        // Doesn't match
            validChoice = false;
        else if(first == charChoices[i]) { // Matches and is valid
            validChoice = true;
            break;
        }
    }

    // e.g. This would be the '4' in 'E4'
    if(guess.size() == 2) {
        char second = guess[1];
        char numChoices[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        for(int i = 0; i < 10; i++) {
            if(second != numChoices[i])        // Doesn't match
                validChoice = false;
            else if(second == numChoices[i]) { // Matches and is valid
                validChoice = true;
                break;
            }
        }
    }
    //  e.g. This would be the '10' in 'E10'
    else {
        if(guess[1] == '1' && guess[2] == '0')
            validChoice = true;
        else
            validChoice = false;
    }

    return validChoice;
}

class board {
public:
    /******** Create the board. 10 x 10 ********/
    board() {
        for(int row = 0; row < 10; row++) {
            for(int col = 0; col < 10; col++) {
                string coordinate = intCoordToString(row) + to_string(col);
                boardSlot* slot = new boardSlot(col, row, coordinate);
                gameMatrix[row][col] = slot;
            }
        }
    }

    /* Current state of the board */
    void printBoard() {
        cout << "  | 1 2 3 4 5 6 7 8 9 10 " << endl;
        cout << "------------------------" << endl;
        char letter = 'A';
        for(int i = 0; i < 10; i++) {
            cout << letter << " | ";
            for(int j = 0; j < 10; j++) {
                if(gameMatrix[i][j]->taken || gameMatrix[i][j]->shipName == "X")
                    cout << gameMatrix[i][j]->shipName << " ";
                else
                    cout << "• ";
            }
            cout << endl;
            letter++;
        }
    }

    /* Did the guess hit a ship? */
    bool markHitOrMiss(string guess) {
        if(!isItValidGuess(guess)) {
            cout << "That coordinate does not exist. Please guess a letter from A to J and a number from 1 to 10" << endl;
            return false;
        }

        char r = toupper(guess[0]);
        char c = guess[1];
        int row = r - 65;
        int col = c - 49;

        if(gameMatrix[row][col]->hit) {
            cout << "You already guessed " << gameMatrix[row][col]->coordinate << endl;
            return false;
        }
        else if(gameMatrix[row][col]->taken) {
            cout << "Hit!" << endl << endl;
            gameMatrix[row][col]->hit = true;
            string coordinate = gameMatrix[row][col]->coordinate;
            gameMatrix[row][col]->currentShip->locations[coordinate] = true;

            if(gameMatrix[row][col]->currentShip->isItSunk()) {
                cout << "You sunk the ship!" << endl << endl;
                return true;
            }
            return false;
        }
        else {
            gameMatrix[row][col]->shipName = "X";
            cout << "Miss" << endl << endl;
            return false;
        }
    }

    /******** Each boat on the board ********/
    struct ship {
        ship() {
            name = "";
            size = 0;
            sunk = false;
        }

        ship(string n, int s) {
            name = n;
            size = s;
            sunk = false;
        }

        map<string, bool> locations; // e.g. 5C, has it been hit?
        bool sunk;                   // Is this ship sunk?
        int size;                    //    5   ,     4     ,    3   ,     3    ,     2
        string name;                 // Carrier, Battleship, Cruiser, Submarine, Destroyer

        /* Pick computer ship location */
        void placeShip(board gameBoard) {
            while (true)   // Until every spot in the ship has been placed on the board
            {
                int row = rand() % 9;
                int col = rand() % 9;

                if (!gameBoard.gameMatrix[row][col]->taken) {        // If the board slot isn't taken
                    if (canBeHorizontal(row, col, gameBoard, size) || canBeVertical(row, col, gameBoard, size)) {

                        bool isItHorizontal = rand() % 2 == 1;             // Should the ship be horizontal (1) or vertical (0)

                        if(isItHorizontal && canBeHorizontal(row, col, gameBoard, size))
                        {
                            bool isItHorizontalLeft = rand() % 2 == 1;     // Should the ship be horizontalLeft (1) or right (0)

                            if(isItHorizontalLeft && canBeHorizontalLeft(row, col, gameBoard, size)) {
                                for (int i = 0; i < size; i++) {
                                    gameBoard.gameMatrix[row][col - i]->taken = true;                   // Game slot is used
                                    gameBoard.gameMatrix[row][col - i]->shipName = name;                // Type of ship
                                    gameBoard.gameMatrix[row][col - i]->currentShip = this;             // Pointer to the ship
                                    string coordinate = gameBoard.gameMatrix[row][col - i]->coordinate; // Coordinate
                                    locations[coordinate] = false;
                                }
                                return;
                            }
                            else if(!isItHorizontalLeft && canBeHorizontalRight(row, col, gameBoard, size)) {
                                for (int i = 0; i < size; i++) {
                                    gameBoard.gameMatrix[row][col + i]->taken = true;
                                    gameBoard.gameMatrix[row][col + i]->shipName = name;
                                    gameBoard.gameMatrix[row][col + i]->currentShip = this;
                                    string coordinate = gameBoard.gameMatrix[row][col + i]->coordinate;
                                    locations[coordinate] = false;
                                }
                                return;
                            }
                        }
                        else if(!isItHorizontal && canBeVertical(row, col, gameBoard, size))
                        {
                            bool isItVerticalAbove = rand() % 2 == 1;     // Should the ship be verticalAbove (1) or below (0)

                            if(isItVerticalAbove && canBeVerticalAbove(row, col, gameBoard, size)) {
                                for (int i = 0; i < size; i++) {
                                    gameBoard.gameMatrix[row - i][col]->taken = true;
                                    gameBoard.gameMatrix[row - i][col]->shipName = name;
                                    gameBoard.gameMatrix[row - i][col]->currentShip = this;
                                    string coordinate = gameBoard.gameMatrix[row - i][col]->coordinate;
                                    locations[coordinate] = false;
                                }
                                return;
                            }
                            else if(!isItVerticalAbove && canBeVerticalBelow(row, col, gameBoard, size)) {
                                for (int i = 0; i < size; i++) {
                                    gameBoard.gameMatrix[row + i][col]->taken = true;
                                    gameBoard.gameMatrix[row + i][col]->shipName = name;
                                    gameBoard.gameMatrix[row + i][col]->currentShip = this;
                                    string coordinate = gameBoard.gameMatrix[row + i][col]->coordinate;
                                    locations[coordinate] = false;
                                }
                                return;
                            }
                        }
                    }
                }
            }
        }

        /* Is the ship sunk */
        bool isItSunk() {
            int numSpotsHit = 0;
            for (map<string, bool>::iterator it = locations.begin(); it != locations.end(); it++) {
                if(it->second == false)
                    return false;
            }
            return true;
        }

        /* Where on the board is the ship */
        void printShipCoords() {
            for (map<string, bool>::iterator it = locations.begin(); it != locations.end(); it++)
                cout << it->first << " ";
            cout << endl;
        }

        /* Can the ship be placed horizontally? */
        bool canBeHorizontal(int row, int col, board b, int size) {
            return canBeHorizontalLeft(row, col, b, size) || canBeHorizontalRight(row, col, b, size);
        }

        /* Can the ship be placed horizontally to the left of the XY coordinate? */
        bool canBeHorizontalLeft(int row, int col, board b, int size) {
            for (int i = 0; i < size; i++) {
                if (col - i < 0 || b.gameMatrix[row][col - i]->taken)
                    return false;
            }
            return true;
        }

        /* Can the ship be placed horizontally to the right of the XY coordinate? canBeVerticalBelow */
        bool canBeHorizontalRight(int row, int col, board b, int size) {
            for (int i = 0; i < size; i++) {
                if (col + i > 9 || b.gameMatrix[row][col + i]->taken)
                    return false;
            }
            return true;
        }

        /* Can the ship be placed vertically? */
        bool canBeVertical(int row, int col, board b, int size) {
            return canBeVerticalAbove(row, col, b, size) || canBeVerticalBelow(row, col, b, size);
        }

        /* Can the ship be placed vertically above the XY coordinate? */
        bool canBeVerticalAbove(int row, int col, board b, int size) {
            for (int i = 0; i < size; i++) {
                if (row - i < 0 || b.gameMatrix[row - i][col]->taken)
                    return false;
            }
            return true;
        }

        /* Can the ship be placed vertically below the XY coordinate? */
        bool canBeVerticalBelow(int row, int col, board b, int size) {
            for (int i = 0; i < size; i++) {
                if (row + i > 9 || b.gameMatrix[row + i][col]->taken)
                    return false;
            }
            return true;
        }
    };

    /******** Each slot in the board ********/
    struct boardSlot {
        boardSlot() {
            taken = false;
            hit = false;
            xAxis = -1;
            yAxis = -1;
            coordinate = "";
            shipName = "";
            currentShip = nullptr;
        }
        boardSlot(int x, int y, string c) {
            taken = false;
            hit = false;
            xAxis = x;
            yAxis = y;
            coordinate = c;
            shipName = "";
            currentShip = nullptr;
        }
        bool taken;        // Is there a ship there
        bool hit;          // If there's a ship there, was it hit?
        int xAxis;         // e.g. 5
        int yAxis;         // e.g. 2 would be C
        string coordinate; // e.g. 52
        string shipName;   // Destroyer
        ship* currentShip; // Current ship at a boardSlot
    };

    boardSlot* gameMatrix[10][10]; // gameMatrix[row][column]
};