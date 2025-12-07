// Advent of Code 2025, Day 3, Puzzle 2
// Mary Bolling
// December 5th, 2025
// Last updated December 6th, 2025


// Part 1 of today's challenge involves comparing numbers in sequences
// Seems easy enough   <--- famous last words

// I used to have a bunch of #includes here, but I'm getting tired of
    // adding them every time so I think I'm just gonna create a .h file to make my life easier

// The new thing to do is to use the 12 numbers in each string that will produce me the biggest number
// How to do this...?
// I know that the highest digit will be in the first n - 11 digits, where n is the number of all
    // digits in the battery string, so I should search the first n - 11 digits for the largest
    // one and select that one to be the highest digit.
    // Then I should search the next n - 11 - k digits, where k is the index of the highest digit,
    // rinse and repeat.

#include "QOL.hpp"

// #defines
#define TOTAL_DIGITS 12

// function declarations
string assembleNumString(string batteryString);
int findBiggestDigit(int startIndex, int endIndex, string batteryString);

// functions
string assembleNumString(string batteryString){
    int startingIndex = 0;
    int newDigitIndex;
    string finalBatteryString;
    for(int digitRange = batteryString.size() - TOTAL_DIGITS; digitRange < batteryString.size(); digitRange++){
        // For the first digitRange number of digits, find the largest digit in the range
        newDigitIndex = findBiggestDigit(startingIndex, (digitRange + 1), batteryString);
        finalBatteryString += batteryString[newDigitIndex];
        startingIndex = newDigitIndex + 1;  // Without this +1, we don't reach the last digit
    }

    return finalBatteryString;
}

// Alright I'm making separate functions for this one. Everything in main() in part 1 gave me the ick a little bit.
// Recursive function alert?
int findBiggestDigit(int startIndex, int endIndex, string batteryString){
    // Go through the given indices of the string and choose the largest number from among them

    int bigDigit = 0;
    int indexOfDigit = 0;
    for(int index = startIndex; index < endIndex; index++){
        // Check for a digit with a value larger than the one we already have
        if(batteryString[index] - '0' > bigDigit){
            bigDigit = batteryString[index] - '0';
            indexOfDigit = index;
        }
    }
    // We've found our biggest digit in the given range. Now the range needs to be expanded to
        // include the index after our largest number up to our end index + 1
    // I realize now. I have written a helper function. This is fine.
    return indexOfDigit;
}

main(){
    char readCharacter;
    string batteryString;
    vector<string> batteryLines;
    string joltString;
    
    uint64_t totalJolts = 0;  // Our running total of jolts

    // You know the drill. Let's open our file.
    std::ifstream batteries("batteries.txt");

    // Split up the file by line
    while(!(batteries.eof())){
        readCharacter = batteries.get();
        if(isdigit(readCharacter)) batteryString += readCharacter;
        else{
            batteryLines.push_back(batteryString);
            batteryString.clear();
        }
    }

    // Clean up after yourself
    batteries.close();
    
    // Add each joltage
    for(int batteryIndex = 0; batteryIndex < batteryLines.size(); batteryIndex++){
        // Clear our string
        joltString.clear();
        // Assemble the string of batteries
        joltString = assembleNumString(batteryLines[batteryIndex]);
        // Cast it to a uint64 and add it to the running total
        totalJolts += stoull(joltString);
    }

    cout << "Total jolts: " << totalJolts << endl;
    return 0;
}
