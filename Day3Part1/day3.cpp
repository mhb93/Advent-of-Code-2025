// Advent of Code 2025, Day 3, Puzzle 1
// Mary Bolling
// December 4th, 2025
// Last updated December 5th, 2025


// Part 1 of today's challenge involves comparing numbers in sequences
// Seems easy enough   <--- famous last words

// I used to have a bunch of #includes here, but I'm getting tired of
    // adding them every time so I think I'm just gonna create a .h file to make my life easier

#include "QOL.hpp"

main(){
    char readCharacter;
    string batteryString;
    vector<string> batteryLines;

    int totalJolts = 0;  // Our running total of jolts

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

    // Go through your battery rows and activate the right batteries
    for(int index = 0; index < batteryLines.size(); index++){
        int firstBigNumber = batteryLines[index][0] - '0';
        int secondBigNumber = 0;
        bool changeFirst = 0;  // Flag to indicate whether we changed the first number
        for(int character /* Yeah that'll be confusing */ = 1;
                            character < batteryLines[index].size();
                                                         character++){
            // Simple comparison
            if((batteryLines[index][character]) - '0' > firstBigNumber){
                // Only make the swap if we're not at the end
                if(character < batteryLines[index].size() - 1){
                    // Go ahead, swap 'em
                    firstBigNumber = batteryLines[index][character] - '0';
                    secondBigNumber = 0;
                    changeFirst = 1;
                }
            }
            // If we weren't cool enough to become the tens place, maybe we
                // could still be the ones place
            if((batteryLines[index][character]) - '0' > secondBigNumber){
                if(!changeFirst){
                    // Make the swaparooni
                    secondBigNumber = batteryLines[index][character] - '0';
                }
            }
            changeFirst = 0;
        }
        string firstNumString = std::to_string(firstBigNumber);
        string secondNumString = std::to_string(secondBigNumber);
        string joltString = firstNumString + secondNumString;
        totalJolts += stoi(joltString);
    }

    cout << "Total jolts: " << totalJolts << endl;
    return 0;
}
