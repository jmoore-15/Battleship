#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
using namespace std;

class board {
    public:
        /******** Create the board. 10 x 10 ********/
        board() {
            for(int i = 0; i < 10; i++) {
                for(int j = 0; j < 10; j++) {
                    boardSlot slot;
                    slot.xAxis = i;
                    slot.yAxis = j;
                    slot.coordinate = to_string(slot.xAxis) + to_string(slot.yAxis);

                    gameMatrix[i][j] = slot;
                }
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
            bool taken;        // Is there a ship there
            bool hit;          // If there's a ship there, was it hit?
            int xAxis;         // e.g. 5
            int yAxis;         // e.g. 2 would be C
            string coordinate; // e.g. 52
            string shipName;   // Destroyer
        };

        /******** Each boat on the board ********/
        struct ship {
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
                while(true) {            // Until every spot in the ship has been placed on the board

                    int xAxisChoice = rand() % 9;
                    int yAxisChoice = rand() % 9;

                    if(!gameBoard.gameMatrix[xAxisChoice][yAxisChoice].taken) {          // If the board slot isn't taken

                        if(canBeHorizontal(xAxisChoice, yAxisChoice, gameBoard, size) || // Can it be placed somewhere on that coord?
                           canBeVertical(xAxisChoice, yAxisChoice, gameBoard, size))
                        {
                            bool isItHorizontal = rand() % 2 == 1;             // Should the ship be horizontal (1) or vertical (0)

                            if(isItHorizontal && canBeHorizontal(xAxisChoice, yAxisChoice, gameBoard, size)) {    // It can be horizontal

                                bool isItHorizontalLeft = rand() % 2 == 1;     // Should the ship be horizontalLeft (1) or right (0)

                                if(isItHorizontalLeft && canBeHorizontalLeft(xAxisChoice, yAxisChoice, gameBoard, size)) {
                                    for(int i = 0; i < size; i++) {
                                        gameBoard.gameMatrix[xAxisChoice - i][yAxisChoice].taken = true;          // Game slot is now used
                                        gameBoard.gameMatrix[xAxisChoice - i][yAxisChoice].shipName = this->name; // Type of ship
                                        string coordinate = to_string(xAxisChoice - i) + to_string(yAxisChoice);  // Coordinate
                                        this->locations.insert(pair<string, bool>(coordinate, false));            // Ship now has coord
                                    }
                                }
                                else {
                                    for(int i = 0; i < size; i++) {
                                        gameBoard.gameMatrix[xAxisChoice + i][yAxisChoice].taken = true;          // Game slot is now used
                                        gameBoard.gameMatrix[xAxisChoice + i][yAxisChoice].shipName = this->name; // Type of ship
                                        string coordinate = to_string(xAxisChoice + i) + to_string(yAxisChoice);  // Coordinate
                                        this->locations.insert(pair<string, bool>(coordinate, false));            // Ship now has coord
                                    }
                                }
                            }
                            else if(!isItHorizontal && canBeVertical(xAxisChoice, yAxisChoice, gameBoard, size)) {// It can be vertical

                                bool isItVerticalAbove = rand() % 2 == 1;     // Should the ship be verticalAbove (1) or below (0)

                                if(isItVerticalAbove && canBeVerticalAbove(xAxisChoice, yAxisChoice, gameBoard, size)) {
                                    for(int i = 0; i < size; i++) {
                                        gameBoard.gameMatrix[xAxisChoice][yAxisChoice - i].taken = true;          // Game slot is now used
                                        gameBoard.gameMatrix[xAxisChoice][yAxisChoice - i].shipName = this->name; // Type of ship
                                        string coordinate = to_string(xAxisChoice) + to_string(yAxisChoice - i);  // Coordinate
                                        this->locations.insert(pair<string, bool>(coordinate, false));            // Ship now has coord
                                    }
                                }
                                else {
                                    for(int i = 0; i < size; i++) {
                                        gameBoard.gameMatrix[xAxisChoice][yAxisChoice + i].taken = true;          // Game slot is now used
                                        gameBoard.gameMatrix[xAxisChoice][yAxisChoice + i].shipName = this->name; // Type of ship
                                        string coordinate = to_string(xAxisChoice) + to_string(yAxisChoice + i);  // Coordinate
                                        this->locations.insert(pair<string, bool>(coordinate, false));            // Ship now has coord
                                    }
                                }
                            }
                            return true;
                        }
                    }
                }
            }

            /* Can the ship be placed horizontally? */
            bool canBeHorizontal(int x, int y, board b, int size) {
                // gameMatrix array starting at [0, 0], so we see if > 9 instead of 10
                return (canBeHorizontalLeft(x, y, b, size) || canBeHorizontalRight(x, y, b, size));
            }

            /* Can the ship be placed horizontally to the left of the XY coordinate? */
            bool canBeHorizontalLeft(int x, int y, board b, int size) {
                for(int i = 0; i < size; i++) {
                    if(b.gameMatrix[x - i][y].xAxis < 0 || b.gameMatrix[x - i][y].taken)
                        return false;
                }
                return true;
            }

            /* Can the ship be placed horizontally to the right of the XY coordinate? */
            bool canBeHorizontalRight(int x, int y, board b, int size) {
                for(int i = 0; i < size; i++) {
                    if(b.gameMatrix[x + i][y].xAxis > 9 || b.gameMatrix[x + i][y].taken)
                        return false;
                }
                return true;
            }

            /* Can the ship be placed vertically? */
            bool canBeVertical(int x, int y, board b, int size) {
                // gameMatrix array starting at [0, 0], so we see if > 9 instead of 10
                return (canBeVerticalAbove(x, y, b, size) || canBeVerticalBelow(x, y, b, size));
            }

            /* Can the ship be placed vertically above the XY coordinate? */
            bool canBeVerticalAbove(int x, int y, board b, int size) {
                for(int i = 0; i < size; i++) {
                    if(b.gameMatrix[x][y - i].yAxis < 0 || b.gameMatrix[x][y - i].taken)
                        return false;
                }
                return true;
            }

            /* Can the ship be placed vertically below the XY coordinate? */
            bool canBeVerticalBelow(int x, int y, board b, int size) {
                for(int i = 0; i < size; i++) {
                    if(b.gameMatrix[x][y + i].yAxis < 9 || b.gameMatrix[x][y + i].taken)
                        return false;
                }
                return true;
            }
    };
    boardSlot gameMatrix[10][10];
};