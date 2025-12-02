// Advent of Code 2025, Day 1, Puzzle 1
// Mary Bolling
// December 1st, 2025





// We've got a dial. There are numbers on the dial, and the direction we need to turn
    // the dial in.
// Example: The dial is pointing to 11. The rotation R8 would result in the dial being
    // on 19.
    // I can only assume from this that if I then used L9, the dial would be on 10.
    // 99 -> 0
    // 99 <- 0

// Here's the kicker:
/*
    THE ACTUAL PASSWORD IS THE NUMBER OF TIMES THE DIAL IS LEFT POINTING AT 0
    AFTER ANY ROTATION IN THE SEQUENCE
    Also, the dial starts pointing at 50.
*/

// Game plan:
    // Make some sort of circular counting construct/algorithm, work from there.


// includes
#include <string>    // For strings
#include <iostream>  // For printing


// function declarations
void twist(char direction, int distance, int &currentDialValue);


// functions
void twist(char direction, int distance, int &currentDialValue){
    // Counting here is a little funky
    // 10 - 20 would be 90
    // 94 + 18 would be 12
    int rightOrLeft = (direction == 'R') ? 1 : -1;  // If the direction is right,
                                                       // we will add the number.
                                                       // If it's left, we subtract it
    currentDialValue = (currentDialValue + (rightOrLeft * distance));

    // No negative numbers on the dial, so we need to fix that if it occurs
    if(currentDialValue < 0){
        currentDialValue = 100 + currentDialValue;
    }
    // Likewise, can't be higher than 99
    else if(currentDialValue > 99){
        currentDialValue -= 100;
    }
}


// main
int main(){
    // Gotta get the list of numbers in here somehow. I could hardcode them, but it
        // would be better practice to be able to take an extrernal list.
        // Will hardcode for now, polish up later

    int password = 0;

    // Oh baby it's struct time
    struct TurnData{
        char direction;
        int distance;
    };

    TurnData allMoves[10] = {{'L', 68}, {'L', 30}, {'R', 48}, {'L', 5},
                             {'R', 60}, {'L', 55}, {'L', 1}, {'L', 99},
                             {'R', 14}, {'L', 82}};  
    // The setup of this will probably
                                                    // change drastically if I have to
                                                    // read from a list. Oh well!
                                                    // This is the Santa Experience.
    
    int listLength = sizeof(allMoves) / sizeof(allMoves[0]);
    int currentDialValue = 50;  // Given from the instructions


    // For each item in the list, perform the move
    for(int index = 0; index < listLength; index++){
        // Twist, but don't shout because this is a secret entrance to the North Pole
        twist(allMoves[index].direction, allMoves[index].distance, currentDialValue);
        std::cout << currentDialValue << std::endl;
        // If it's a 0, make a note of that by updating the password
        if(currentDialValue == 0) password++;
    }

    std::cout << "The password is: " << password << std::endl;

    
    return 0;
}


