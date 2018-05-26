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
                    slot.yAxis = i;
                    slot.xAxis = j;
                    slot.coordinate = to_string(slot.xAxis) + to_string(slot.yAxis);

                    gameMatrix[i][j] = boardSlot();
                }
            }
        }

        /******** Each slot in the board ********/
        class boardSlot {
            public:
            boardSlot() {
                    hit = false;
                }
            private:
                bool taken;        // Is there a ship there
                bool hit;          // If there's a ship there, was it hit?
                int xAxis;         // e.g. 5
                int yAxis;         // e.g. 3 would be C
                string coordinate; // e.g. 5C
        };

        /******** Each boat on the board ********/
        class ship {
            public:
                ship(int s) {
                    size = s;
                    sunk = false;
                }
            /* Pick computer ship location */
            bool placeShip() {
                int xAxisChoice = rand() % 9;
                int yAxisChoice = rand() % 9;

                if(!gameMatrix[xAxisChoice][yAxisChoice].taken) { // If the board slot isn't taken

                    if(canBeHorizontal(xAxisChoice, yAxisChoice, size) || canBeVertical(xAxisChoice, yAxisChoice, size)) {
                        bool isItHorizontal = rand() % 2 == 1;    // Should the chip be horizontal (1) or vertical (0)

                        if(isItHorizontal && canBeHorizontal(xAxisChoice, yAxisChoice, size)) {
                            if(canBeHorizontalLeft()) {
                                for(int i = 0; i < size; i++) {
                                    
                                }
                            }
                            else {

                            }
                        }
                        else {
                            if(canBeVerticalAbove()) {

                            }
                            else {

                            }
                        }
                    }
                }
                return true;
            }

            /* Can the ship be placed horizontally? */
            bool canBeHorizontal(int x, int y, int size) {
                // gameMatrix array starting at [0, 0], so we see if > 9 instead of 10
                return (canBeHorizontalLeft(x, y, size) || canBeHorizontalRight(x, y, size));
            }

            /* Can the ship be placed horizontally to the left of the XY coordinate? */
            bool canBeHorizontalLeft(int x, int y, int size) {
                for(int i = 0; i < size; i++) {
                    if(gameMatrix[x - i][y] < 0 || gameMatrix[x - i][y].taken)
                        return false;
                }
                return true;
            }

            /* Can the ship be placed horizontally to the right of the XY coordinate? */
            bool canBeHorizontalRight(int x, int y, int size) {
                for(int i = 0; i < size; i++) {
                    if(gameMatrix[x + i][y] > 9 || gameMatrix[x + i][y].taken)
                        return false;
                }
                return true;
            }

            /* Can the ship be placed vertically? */
            bool canBeVertical(int x, int y, int size) {
                // gameMatrix array starting at [0, 0], so we see if > 9 instead of 10
                return (canBeVerticalAbove(x, y, size) || canBeVerticalBelow(x, y, size));
            }

            /* Can the ship be placed vertically above the XY coordinate? */
            bool canBeVerticalAbove(int x, int y, int size) {
                for(int i = 0; i < size; i++) {
                    if(gameMatrix[x][y - i] < 0 || gameMatrix[x][y - i].taken)
                        return false;
                }
            }

            /* Can the ship be placed vertically below the XY coordinate? */
            bool canBeVerticalBelow(int x, int y, int size) {
                for(int i = 0; i < size; i++) {
                    if(gameMatrix[x][y + i] < 9 || gameMatrix[x][y + i].taken)
                        return false;
                }
                return true;
            }

            private:
                map<string, bool> locations; // e.g. 5C, has it been hit?
                int size;
                bool sunk;                   // Is this ship sunk?
        };

    private:
        boardSlot gameMatrix[10][10];
};