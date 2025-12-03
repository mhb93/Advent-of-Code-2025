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
#include <string>   // For strings
#include <iostream> // For printing
#include <fstream>  // For reading from a file
#include <vector>   // For creating a vector

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
        while(currentDialValue < 0) currentDialValue += 100;
    }
    // Likewise, can't be higher than 99
    else if(currentDialValue > 99){
        while(currentDialValue > 99) currentDialValue -= 100;
    }
}


// main
int main(){
    int password = 0;

    // Oh baby it's struct time
    struct TurnData{
        char direction;
        int distance;
    };

    TurnData move = {};  // This will be the struct we store each move in before
                               // pushing it onto a vector
    std::vector<TurnData> steps;  // This is that vector of moves (or "steps")

    int vectorLength;
    int currentDialValue = 50;  // Given from the instructions
    std::string distanceString;
    std::string tempString;

    // Open the file, read the directions from it
    std::ifstream file("password.txt");
    std::string line;


    while(getline(file, line)){
        move.direction = line[0];  // Save the direction we want to move in

        distanceString = line[1];  // Record our distance
        if(isdigit(line[2])){ // If the distance is 2 character long...
            tempString = line[1];
            distanceString = tempString + line[2];
            // But what about 3 digits?
            if(isdigit(line[3])){
                tempString = distanceString;
                distanceString = tempString + line[3];
            }
        }

        // Throw the distance into our temporary struct
        move.distance = std::stoi(distanceString);

        // Put this temporary struct into our vector
        steps.push_back(move);
    }
    if(file.eof()) file.close();  // Clean up after yourself

    // For each item in the list, perform the move
    vectorLength = steps.size();
    for(int index = 0; index < vectorLength; index++){
        // Twist, but don't shout because this is a secret entrance to the North Pole
        twist(steps[index].direction, steps[index].distance, currentDialValue);
        // If it's a 0, make a note of that by updating the password
        if(currentDialValue == 0) password++;
    }

    std::cout << "The password is: " << password << std::endl;
    
    return 0;
}


