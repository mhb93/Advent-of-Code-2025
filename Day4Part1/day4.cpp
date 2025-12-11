// Advent of Code 2025, Day , Puzzle 1
// Mary Bolling
// December 9th, 2025

#include "QOL.hpp"

// global variables and structs and all that
enum Side{
    UP,
    DOWN,
    LEFT,
    RIGHT
};


// fuunction declarations
int countMoveableRolls(const vector<string> &board);
int sideChecker(const vector<string> &board, int boardIndex, int stringIndex, bool corner, int leftOrRight);
int normalChecker(const vector<string> &board, int boardIndex, int stringIndex);


// functions
int countMoveableRolls(vector<string> &board){
    // Find the rolls with fewer than four rolls in the eight adjacent spaces
    // The first line is going to be an edge case because there are only five
        // adjacent spaces
    bool cornerTracker;
    int LRUD, surroundingRolls;
    int moveableRolls = 0;
    int oldMoveables = 0;
    for(int boardIndex = 0; boardIndex < board.size(); boardIndex++){
        cout << "Board index: " << boardIndex << endl;
        cout << board[boardIndex] << endl;
        for(int lineIndex = 0; lineIndex < board[boardIndex].length(); lineIndex++){
            if(board[boardIndex][lineIndex] == '@'){
                // If we're on an edge, use the sideChecker function
                if(boardIndex == 0 || boardIndex == (board.size() - 1) ||
                   lineIndex == 0 || lineIndex == (board[boardIndex].length() - 1)){
                    // Left corner
                    if(lineIndex == 0 && (boardIndex == 0 || boardIndex == (board.size() - 1))){
                        cornerTracker = true;
                        LRUD = LEFT;
                    }
                    // Right corner
                    // This is so terribly ugly
                    else if(lineIndex == (board[boardIndex].length() - 1) && (boardIndex == 0 || boardIndex == (board.size() - 1))){
                        cornerTracker = true;
                        LRUD = RIGHT;
                    }
                    // No corner
                    else{
                        cornerTracker = false;
                        // Check for which edge we're on
                        if(boardIndex == 0) LRUD = UP;
                        else if (boardIndex == board.size() - 1) LRUD = DOWN;

                        if(lineIndex == 0) LRUD = LEFT;
                        else if(lineIndex == board[boardIndex].size() - 1) LRUD = RIGHT;
                    }
                    surroundingRolls = sideChecker(board, boardIndex, lineIndex, cornerTracker, LRUD);
                    // cout << "Side " << rollsAroundUs << endl;
                }
                else{
                    // Otherwise, count the surrounding eight squares
                    surroundingRolls = normalChecker(board, boardIndex, lineIndex);
                }
                if(surroundingRolls < 4){
                    cout << "Index " << lineIndex << " is moveable" << endl;
                    moveableRolls++;
                    oldMoveables++;
                }
                surroundingRolls = 0;
            }
        }
        cout << "Moveable rolls this row: " << oldMoveables << "\n" << endl;
        oldMoveables = 0;
    }

    return moveableRolls;
}

int sideChecker(const vector<string> &board, int boardIndex, int stringIndex, bool corner, int leftOrRight){
    // Check up on our edge cases
    // adjacentTiles is the number of adjacent tiles we need to check
    // corner is whether or not the square is in a corner
    // leftOrRight indicates whether the element is on the lelft or right side of the board
    int rollsAroundUs = 0;

    switch(leftOrRight){
        case LEFT:
            // Always check the tile to the right
            if(board[boardIndex][stringIndex + 1] == '@') rollsAroundUs++;
            // If we're in a corner, check whether it's the top or bottom one
            if(corner){
                if(boardIndex == 0){
                    // We're in the top left corner
                    // Check the one below, and the one to the right of that
                    if(board[boardIndex + 1][stringIndex] == '@') rollsAroundUs++;
                    if(board[boardIndex + 1][stringIndex + 1] == '@') rollsAroundUs++;
                }
                else{
                    // We must be in the bottom left corner
                    // Check the one above, and the one to the right of that
                    if(board[boardIndex - 1][stringIndex] == '@') rollsAroundUs++;
                    if(board[boardIndex - 1][stringIndex + 1] == '@') rollsAroundUs++;
                }
            }
            else{
                // Since we're not in a corner, check the surrounding five tiles
                    // above us and to the right
                if(board[boardIndex - 1][stringIndex] == '@') rollsAroundUs++;
                if(board[boardIndex - 1][stringIndex + 1] == '@') rollsAroundUs++;
                if(board[boardIndex + 1][stringIndex] == '@') rollsAroundUs++;
                if(board[boardIndex + 1][stringIndex + 1] == '@') rollsAroundUs++;
            }
            break;


        case RIGHT:
            // Always check the tile to the left
            if(board[boardIndex][stringIndex - 1] == '@') rollsAroundUs++;
            if(corner){
                if(boardIndex == 0){
                    // We're in the top right corner
                    // Check the one below, and the one to the left of that
                    if(board[boardIndex + 1][stringIndex] == '@') rollsAroundUs++;
                    if(board[boardIndex + 1][stringIndex - 1] == '@') rollsAroundUs++;
                }
                else{
                    // We must be in the bottom right corner
                    // Check the one above, and the one to the right of that
                    if(board[boardIndex - 1][stringIndex] == '@') rollsAroundUs++;
                    if(board[boardIndex - 1][stringIndex - 1] == '@') rollsAroundUs++;
                }
            }
            else{
                // Since we're not in a corner, check the surrounding five tiles
                    // above us and to the left
                if(board[boardIndex - 1][stringIndex] == '@') rollsAroundUs++;
                if(board[boardIndex - 1][stringIndex - 1] == '@') rollsAroundUs++;
                if(board[boardIndex + 1][stringIndex] == '@') rollsAroundUs++;
                if(board[boardIndex + 1][stringIndex - 1] == '@') rollsAroundUs++;
            }
        break;

        case UP:
            // Always check the tile beneath us
            if(board[boardIndex + 1][stringIndex] == '@') rollsAroundUs++;
            // I'm letting left and right handle the corner cases, so just check the
                // five adjacent tiles
            if(board[boardIndex][stringIndex - 1] == '@') rollsAroundUs++;
            if(board[boardIndex][stringIndex + 1] == '@') rollsAroundUs++;
            if(board[boardIndex + 1][stringIndex - 1] == '@') rollsAroundUs++;
            if(board[boardIndex + 1][stringIndex + 1] == '@') rollsAroundUs++;
        break;

        case DOWN:
            // Always check the tile above us
            if(board[boardIndex - 1][stringIndex] == '@') rollsAroundUs++;
            // I'm letting left and right handle the corner cases, so just check the
                // five adjacent tiles
            if(board[boardIndex][stringIndex - 1] == '@') rollsAroundUs++;
            if(board[boardIndex][stringIndex + 1] == '@') rollsAroundUs++;
            if(board[boardIndex - 1][stringIndex - 1] == '@') rollsAroundUs++;
            if(board[boardIndex - 1][stringIndex + 1] == '@') rollsAroundUs++;
        break;

        default: break;
    }

    return rollsAroundUs;
}


int normalChecker(const vector<string> &board, int boardIndex, int stringIndex){
    // Check the surrounding 8 tiles
    // If we're in here, we know that we don't have to deal with any edge cases
    int rollsAroundUs = 0;
    // To the right
    if(board[boardIndex][stringIndex + 1] == '@') rollsAroundUs++;
    // To the right and down
    if(board[boardIndex + 1][stringIndex + 1] == '@') rollsAroundUs++;
    // Directly down
    if(board[boardIndex + 1][stringIndex] == '@') rollsAroundUs++;
    // Directly down and to the left
    if(board[boardIndex + 1][stringIndex - 1] == '@') rollsAroundUs++;
    // To the left
    if(board[boardIndex][stringIndex - 1] == '@') rollsAroundUs++;
    // To the left and up
    if(board[boardIndex - 1][stringIndex - 1] == '@') rollsAroundUs++;
    // Directly up
    if(board[boardIndex - 1][stringIndex] == '@') rollsAroundUs++;
    // Directly up and to the right
    if(board[boardIndex - 1][stringIndex + 1] == '@') rollsAroundUs++;

    return rollsAroundUs;
}


// main
main(){
    char readChar;
    string fileLine;
    vector<string> board;

    std::ifstream boardText("board.txt");
    while(getline(boardText, fileLine)){
        // Pop that into the vector
        board.push_back(fileLine);
    }
    if(boardText.eof()) boardText.close();

    int numberOfMoveableRolls = countMoveableRolls(board);
    cout << "Number of moveable rolls: " << numberOfMoveableRolls << endl;

    return 0;
}
