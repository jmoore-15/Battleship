#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
using namespace std;

class board {
public:
    /******** Create the board. 10 x 10 ********/
    board() {
        for(int row = 0; row < 10; row++) {
            for(int col = 0; col < 10; col++) {
                string coordinate = "[" + to_string(col + 1) + ", " + to_string(row + 1) + "]";
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
                if(gameMatrix[i][j]->taken)
                    cout << gameMatrix[i][j]->shipName << " ";
                else
                    cout << "0 ";
            }
            cout << endl;
            letter++;
        }
    }

    /******** Each slot in the board ********/
    struct boardSlot {
        boardSlot() {
            taken = false;
            hit = false;
            xAxis = -1;
            yAxis = -1;
            coordinate = "";
            shipName = "";
        }
        boardSlot(int x, int y, string c) {
            taken = false;
            hit = false;
            xAxis = x;
            yAxis = y;
            coordinate = c;
            shipName = "";
        }
        bool taken;        // Is there a ship there
        bool hit;          // If there's a ship there, was it hit?
        int xAxis;         // e.g. 5
        int yAxis;         // e.g. 2 would be C
        string coordinate; // e.g. 52
        string shipName;   // Destroyer
    };

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
        bool placeShip(board gameBoard) {
            while (true)   // Until every spot in the ship has been placed on the board
            {
                int row = rand() % 9;
                int col = rand() % 9;

                if (!gameBoard.gameMatrix[row][col]->taken) {        // If the board slot isn't taken
                    if (canBeHorizontal(row, col, gameBoard, size) || canBeVertical(row, col, gameBoard, size)) {
                        cout << "Current coordinates are: [X = " << gameBoard.gameMatrix[row][col]->xAxis + 1;
                        cout << ", Y = " << gameBoard.gameMatrix[row][col]->yAxis + 1 << "]" << endl;
                        cout << "This is ship " << name << " of size " << size << endl;
                        
                        bool isItHorizontal = rand() % 2 == 1;             // Should the ship be horizontal (1) or vertical (0)
                        
                        if (isItHorizontal && canBeHorizontal(row, col, gameBoard, size))
                        {
                            bool isItHorizontalLeft = rand() % 2 == 1;     // Should the ship be horizontalLeft (1) or right (0)
                            
                            if (isItHorizontalLeft && canBeHorizontalLeft(row, col, gameBoard, size)) {
                                for (int i = 0; i < size; i++) {
                                    gameBoard.gameMatrix[row][col - i]->taken = true;                   // Game slot is used
                                    gameBoard.gameMatrix[row][col - i]->shipName = this->name;          // Type of ship
                                    string coordinate = gameBoard.gameMatrix[row][col - i]->coordinate; // Coordinate
                                    locations[coordinate] = false;
                                }
                            }
                            else {
                                for (int i = 0; i < size; i++) {
                                    gameBoard.gameMatrix[row][col + i]->taken = true;
                                    gameBoard.gameMatrix[row][col + i]->shipName = this->name;
                                    string coordinate = gameBoard.gameMatrix[row][col + i]->coordinate;
                                    locations[coordinate] = false;
                                }
                            }
                        }
                        else if (!isItHorizontal && canBeVertical(row, col, gameBoard, size))
                        {
                            bool isItVerticalAbove = rand() % 2 == 1;     // Should the ship be verticalAbove (1) or below (0)
                            
                            if (isItVerticalAbove && canBeVerticalAbove(row, col, gameBoard, size)) {
                                for (int i = 0; i < size; i++) {
                                    gameBoard.gameMatrix[row - i][col]->taken = true;
                                    gameBoard.gameMatrix[row - i][col]->shipName = this->name;
                                    string coordinate = gameBoard.gameMatrix[row - i][col]->coordinate;
                                    locations[coordinate] = false;
                                }
                            }
                            else {
                                for (int i = 0; i < size; i++) {
                                    gameBoard.gameMatrix[row + i][col]->taken = true;
                                    gameBoard.gameMatrix[row + i][col]->shipName = this->name;
                                    string coordinate = gameBoard.gameMatrix[row + i][col]->coordinate;
                                    locations[coordinate] = false;
                                }
                            }
                        }
                        return true;
                    }
                }
            }
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
                if (b.gameMatrix[row][col - i]->yAxis < 0 || b.gameMatrix[row][col - i]->taken)
                    return false;
            }
            return true;
        }

        /* Can the ship be placed horizontally to the right of the XY coordinate? canBeVerticalBelow */
        bool canBeHorizontalRight(int row, int col, board b, int size) {
            for (int i = 0; i < size; i++) {
                if (b.gameMatrix[row][col + i]->yAxis > 9 || b.gameMatrix[row][col + i]->taken)
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
                if (b.gameMatrix[row - i][col]->xAxis < 0 || b.gameMatrix[row - i][col]->taken)
                    return false;
            }
            return true;
        }

        /* Can the ship be placed vertically below the XY coordinate? */
        bool canBeVerticalBelow(int row, int col, board b, int size) {
            for (int i = 0; i < size; i++) {
                if (b.gameMatrix[row + i][col]->xAxis > 9 || b.gameMatrix[row + i][col]->taken)
                    return false;
            }
            return true;
        }
    };

    boardSlot* gameMatrix[10][10]; // gameMatrix[row][column]
};
