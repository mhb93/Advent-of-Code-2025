// Advent of Code 2025, Day 2, Puzzle 2
// Mary Bolling
// December 4th, 2025

// As always, this starts with opening a file
// Something tells me I'm going to be good at opening and parsing files in C++
    // by the end of this

// The file gives me a list of inclusive ranges. I need to identifty all the
    // numbers in the ranges that have repeating sequences, like 11 or 1818
    // or 921921

// includes
#include <fstream>  // For reading from a file
#include <string>   // For string manipulation
#include <vector>   // For vectors
#include <cstdint>  // For big numbers
#include <iostream> // For debugging and printing out the answer
using std::cout;
using std::endl;    // Got annoyed writing std:: before these
using std::vector;

// Man I love using structs
struct RangePair{
    uint64_t rangeStart;
    uint64_t rangeEnd;
};

// function declarations
uint64_t findInvalidNumbers(vector<RangePair> ranges);
uint64_t findRepeatedStrings(uint64_t number, std::string numberString, uint64_t repeaterLength);


// functions
uint64_t findInvalidNumbers(vector<RangePair> ranges){
    // For each pair in the vector, figure out the invalid numbers in each range
    int vectorLength = ranges.size();
    uint64_t invalidSum = 0;

    for(int index = 0; index < vectorLength; index++){
        // For each entry in the passed vector...
        for(uint64_t currentNum = ranges[index].rangeStart;
                         currentNum <= ranges[index].rangeEnd;
                                                   currentNum++){
            // ...search each number in the range for an invalid input
            std::string numString = std::to_string(currentNum);
            
            // Need to find all the repeated patterns within the range.
            // The repeated sequence will be at most n / 2 digits, where n is
                // the number of digits in the number.
            // I wonder if I can do something like, "for each number n is
                // divisible by, look for repeated strings of that length."
                // Yes, that sounds pretty good. I'll try that.

            uint64_t invalidBefore = invalidSum;
            for(uint64_t isDivis = 1; isDivis <= numString.size(); isDivis++){
                // Find out if our current number is divisible by isDivis
                if(numString.size() % isDivis == 0 && numString.size() != isDivis){
                    // Look for repeating strings with a length of isDivis
                    invalidSum += findRepeatedStrings(currentNum, numString, isDivis);
                }
                if(invalidSum > invalidBefore) break;   // Make sure each number is only added ONCE
            }
        }
    }
    return invalidSum;
}
            

// Checks for repeated sequences of numbers within a number.
// Returns the passed number if it finds a repeated sequence and returns 0 otherwise.
uint64_t findRepeatedStrings(uint64_t number, std::string numberString, uint64_t repeaterLength){
    // Create the first string, then compare it to all the others. If we fail, return.
    std::string repeatingSequence, comparingString;
    int numberOfReps = int(numberString.size() / repeaterLength);
    int numIndex;
    for(int numIndex = 0; numIndex < repeaterLength; numIndex++){
        repeatingSequence += numberString[numIndex];
    }

    // Now that we have our repeating string, compare it to the other segments of the number
    for(int repSection = 1; repSection < numberOfReps; repSection++){
        // Check every repeating section
        // If our repeating section is 3 digits long, then check num[0, 1, 2] against num[3, 4, 5]
        // Make num[3, 4, 5]
        for(int looper = 0; looper < repeaterLength; looper++){
            // cout << repSection << endl;
            numIndex = repSection * repeaterLength + looper;
            comparingString += numberString[numIndex];
        }
        if(comparingString != repeatingSequence) return 0;
        comparingString.clear();
    }

    return number;
}
    


int main(){
    RangePair rangeHolder = {};
    std::vector<RangePair> ranges;
    // Open up the file
    std::ifstream IDs("IDs.txt");
    std::string rangeValue;

    // The numbers are split up via commas and dashes
    const char COMMA = ',';
    const char DASH  = '-';
    char readCharacter;

    // Obligatory index variable
    int index = 0;
    uint64_t sumOfInvalidNumbers;

    // Let's read our data, shall we?
    while(!(IDs.eof())){
        readCharacter = IDs.get();
        if(isdigit(readCharacter)){
            // Add this digit to the number we're currently on
            rangeValue += readCharacter;
            index++;
        }
        else if(readCharacter == '-'){
            // If we find a dash, we've found the end of a number
            rangeHolder.rangeStart = stoull(rangeValue);  // int it and save it
            rangeValue.clear();  // clear it
            index = 0;
        }
        else if(readCharacter == ',' || readCharacter == EOF){
            // If we find a comma (or the end of our file), we've found the end of a range
            rangeHolder.rangeEnd = stoull(rangeValue);  // int it
            rangeValue.clear();  // clear it
            index = 0;

            // Add the RangePair to your vector
            ranges.push_back(rangeHolder);
        }
    }

    IDs.close();  // Clean up after yourself

    // Now, for each range, go through and find the numbers
    sumOfInvalidNumbers = findInvalidNumbers(ranges);

    cout << "Sum: " << sumOfInvalidNumbers << endl;
    return 0;
}
