#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

#define DEFAULT_INPUT_NAME  "1/input.txt"

void readTwoColumns(const std::string& filename, std::vector<int>& array1, std::vector<int>& array2) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    int num1, num2;
    // Reading numbers from file - assuming we have correctly formated file with integers in two columns
    // Passing those numbers to two different arrays
    while (file >> num1 >> num2) {
        array1.push_back(num1);
        array2.push_back(num2);
    }

    file.close();
}

int countOcurrences(int searchingNumber, std::vector<int>& arr, std::unordered_map<int, int> &cache) {
    if(cache[searchingNumber]) {
        return cache[searchingNumber];
    }
    int result = count(arr.begin(), arr.end(), searchingNumber);
    cache[searchingNumber] = result;
    return result;
}

int main(int argc, char *argv[]) {
    std::vector<int> testL;
    std::vector<int> testR;
    std::string inputName = DEFAULT_INPUT_NAME;
    std::unordered_map<int, int> cache;
    int result = 0;
    int result2 = 0;
    int counter = 0;    

    if(argc > 1) {
        inputName = argv[1];
    }
    
    // Filling arrays from file with data
    readTwoColumns(inputName,testL, testR);

    // Sorting both arrays, to ensure pairing lowest possible pairs
    std::sort(testL.begin(), testL.end());
    std::sort(testR.begin(), testR.end());

    // Counting distance for each pair of sorted columns
    for (int n: testL) {
        result+= abs(n - testR[counter]);
        counter++;
    }

    // Display result for the first puzzle
    std::cout << "Result for puzzle one: " << result << std::endl;

    // Reset counter
    counter = 0;

    // Count data for the second puzzle
    for(int n: testL) {
        result2 += n * countOcurrences(n, testR, cache);
    }

    // Display result for the second puzzle
    std::cout << "Result for puzzle two: " << result2 << std::endl;

    return 0;
}