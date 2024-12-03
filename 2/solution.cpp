#include <stdexcept>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#define DEFAULT_INPUT_NAME  "2/input.txt"

bool isSafe(std::vector<int> &numbers) {
    int diff = 0;

    // determine if numbers are increasing or decreasing based on two first positions in our vector
    bool isIncreasig = numbers[0] < numbers[1];

    // we loop over all given numbers
    for(int i = 1; i < numbers.size(); i++) {
        // verify if any pair of following numbers broke business rules
        if(isIncreasig) {
            diff = numbers[i] - numbers[i-1];
            if(diff <= 0 || diff > 3) {
                return false;
            }
        } else {
            diff = numbers[i-1] - numbers[i];
            if(diff <= 0 || diff > 3) {
                return false;
            }
        }
    }

    // if all given numbers meets business criteria we are returning information that all row is safe
    return true;

    // TODO: verify version with "auto" and helper variable for previous value (logic from index 1)
}

// Function veryfying if there is any permutation of numbers without one of them which will meet requirments
bool isSafeWithSingleToleranceLevel(std::vector<int> &numbers) {
    // Iterate over each number from vector to verify permutation without that number
    for(int i = 0; i < numbers.size(); i++) {
        // copying vector to create permutation without current number 
        std::vector<int> numbersCopy = numbers;

        // removing current number from vector
        numbersCopy.erase( numbersCopy.begin() + i);
        
        // veryfing if new vector satisfy requirments
        if(isSafe(numbersCopy)){
            return true;
        }
    }
    return false;
}

void countSafeRowsInFile(const std::string &filename, int & safeRowsCount, int & safeRowsWithSingleLevelToleration) {
    
    // Open file to read data
    std::ifstream file(filename);

    // Prepare buffer for each line
    char currentLine[64];

    // Ensure we have access to file with data
    if (!file.is_open())
    {
        throw std::runtime_error("Error: Unable to open file " + filename);
    }

    // Read file line by line
    while(file.getline(currentLine, 64)) {

        std::vector<int> numbers;
        std::string currentNumber = "";

        // Read each character
        for (int i = 0; i < 64; i++) {
            // If character is space, trasnform buffered string into number
            if (currentLine[i] == ' ') {
                numbers.push_back(std::stoi(currentNumber));
                currentNumber = "";
            // If character is end of line transform buffered string into number and break loop for this line
            } else if (currentLine[i] == '\0') {
                numbers.push_back(std::stoi(currentNumber));
                currentNumber = "";
                break;
            // If character is any other char (assuming it's a number) concatenate it with previous ones
            } else {
               currentNumber += currentLine[i];
            }
        }

        // verify if those numbers meets our business requirments
        if(isSafe(numbers)) {
            // if so, increase counter
            safeRowsCount++;
        } else {
            if(isSafeWithSingleToleranceLevel(numbers)) {
                safeRowsWithSingleLevelToleration++;
            }
        }
    }

    file.close();
}

int main(int argc, char *argv[]) {
    
    // Set default text input file name
    std::string inputName = DEFAULT_INPUT_NAME;

    // Result for puzzle one: completly safe results
    int safeRowsCount = 0;

    // Result to puzzle two: unsafe results which could be safe if one element would be removed
    int safeRowsWithSingleLevelToleration = 0;

    // Read filename from CLI argument if any passed
    if(argc > 1) {
        inputName = argv[1];
    }

    // Read data from file and immediately count safe rows
    countSafeRowsInFile(inputName, safeRowsCount, safeRowsWithSingleLevelToleration);

    // Display results to the terminal
    std::cout << "Safe items count: " << safeRowsCount << std::endl;
    std::cout << "Safe items with single level tolerance: " << safeRowsCount + safeRowsWithSingleLevelToleration << std::endl;

    return 0;
}