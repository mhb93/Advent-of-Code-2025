// Advent of Code 2025, Day 2, Puzzle 1
// Mary Bolling
// December 3rd, 2025


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
int findInvalidNumbers(vector<RangePair> ranges);
int countDigit(uint64_t n);

// functions
int findInvalidNumbers(vector<RangePair> ranges){
    // For each pair in the vector, figure out the invalid numbers in each range
    int vectorLength = ranges.size();
    int numDigits;

    int64_t rangeS, rangeE, rangeRange;

    for(int index = 0; index < vectorLength; index++){
        // For each entry in the passed vector...
        rangeS = ranges[index].rangeStart;
        rangeE = ranges[index].rangeEnd;
        rangeRange = rangeE - rangeS;
        // cout << index << endl;
        if(index == 18){
            cout << rangeS << endl;
            cout << rangeE << endl;
        }
        for(int currentNum = ranges[index].rangeStart;
                     currentNum <= ranges[index].rangeEnd;
                                                 currentNum++){
            // ...search each number in the range for an invalid input
            numDigits = countDigit(currentNum);
            if(numDigits % 2 == 0){
                // Odd number won't have a twice-repeated sequence, so
                    // don't look at it
                // cout << currentNum << endl;
                std::string numString = std::to_string(currentNum);
                // cout << numString << endl;
            }
        }
        // Search the range of numbers for invalid entries
        // numDigits = countDigits(ranges[1].rangeStart)
    }


    return 0;   // DUMMY, YEAH
}

// Counts the number of digits in a number
// This code was taken from https://www.geeksforgeeks.org/dsa/program-count-digits-integer-3-different-methods/
int countDigit(uint64_t n)
{
    // Use logarithm base 10 to count digits
    // log10(n) gives number of digits minus 1, so add 1
    // cout << n << endl;
    return floor(log10(n) + 1);
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

    int commaCounter = 0;   // DELETE THIS!

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
        else if(readCharacter == ','){
            // If we find a comma, we've found the end of a range
            rangeHolder.rangeEnd = stoull(rangeValue);  // int it
            // cout << "Range end: ";
            // cout << rangeHolder.rangeEnd << "\n" << endl;
            rangeValue.clear();  // clear it
            index = 0;

            // Add the RangePair to your vector
            ranges.push_back(rangeHolder);
            commaCounter++;
        }
    }

    IDs.close();  // Clean up after yourself

    cout << commaCounter << endl;
    cout << ranges.size() << "\n " << endl;
    // Now, for each range, go through and find the numbers
    sumOfInvalidNumbers = findInvalidNumbers(ranges);

    return 0;
}
