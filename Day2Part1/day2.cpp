// Advent of Code 2025, Day 2, Puzzle 1
// Mary Bolling
// December 3rd, 2025
// Last edited December 4th, 2025


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
#include <math.h>   // For floor()
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
int countDigit(uint64_t n);

// functions
uint64_t findInvalidNumbers(vector<RangePair> ranges){
    // For each pair in the vector, figure out the invalid numbers in each range
    int vectorLength = ranges.size();
    uint64_t invalidSum = 0;

    for(int index = 0; index < vectorLength; index++){
        cout << ranges[index].rangeStart << "\n" << endl;
        // For each entry in the passed vector...
        for(uint64_t currentNum = ranges[index].rangeStart;
                         currentNum <= ranges[index].rangeEnd;
                                                   currentNum++){
            // ...search each number in the range for an invalid input
            std::string numString = std::to_string(currentNum);
            // Odd number won't have a twice-repeated sequence, so
                // don't look at it
            if(numString.size() % 2 == 0){
                // Chop the number in half, compare the two strings
                std::string firstHalf, secondHalf;
                for(int numStrIndex = 0; numStrIndex < numString.size(); numStrIndex++){
                    // Grab the first half of the number string
                    if((numStrIndex < numString.size()/2)) firstHalf += numString[numStrIndex];
                    // Grab the second half of the number string
                    else secondHalf += numString[numStrIndex];
                }
                // Compare them
                if(firstHalf == secondHalf && !(firstHalf.empty())){
                    // Criteria met! Add the number to the running total
                    invalidSum += currentNum;
                }
                firstHalf.clear();
                secondHalf.clear();
            }
        }
    }

    // Got our answer
    return invalidSum;
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
            // cout << "Range start: " << rangeValue << endl;
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
