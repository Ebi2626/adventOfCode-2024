#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>

#define DEFAULT_INPUT_NAME "4/input.txt"

void readFile(const std::string &filename, std::vector<std::vector<char>> &chars)
{

    std::ifstream file(filename);
    std::string lineBuffer;

    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    int lineNumber = 0;
    while (std::getline(file, lineBuffer))
    {
        chars.push_back(std::vector<char>());
        for (auto c : lineBuffer)
        {
            chars[lineNumber].push_back(c);
        }

        lineNumber++;
    }

    file.close();
}

bool verifyRight(std::vector<std::vector<char>> &chars, int row, int column, const int size) {
    if (chars[row][column + 1] == 'M' && chars[row][column + 2] == 'A' && chars[row][column + 3] == 'S') {
        return true;
    }
    return false;
}

bool verifyLeft(std::vector<std::vector<char>> &chars, int row, int column, const int size) {
    if (chars[row][column - 1] == 'M' && chars[row][column - 2] == 'A' && chars[row][column - 3] == 'S') {
        return true;
    }
    return false;
}

bool verifyUp(std::vector<std::vector<char>> &chars, int row, int column, const int size) {
    if (chars[row - 1][column] == 'M' && chars[row - 2][column] == 'A' && chars[row - 3][column] == 'S') {
        return true;
    }
    return false;
}

bool verifyDown(std::vector<std::vector<char>> &chars, int row, int column, const int size) {
    if (chars[row + 1][column] == 'M' && chars[row + 2][column] == 'A' && chars[row + 3][column] == 'S') {
        return true;
    }
    return false;
}

bool verifyUpRight(std::vector<std::vector<char>> &chars, int row, int column, const int size) {
    if (chars[row - 1][column + 1] == 'M' && chars[row - 2][column + 2] == 'A' && chars[row - 3][column + 3] == 'S') {
        return true;
    }
    return false;
}

bool verifyUpLeft(std::vector<std::vector<char>> &chars, int row, int column, const int size) {
    if (chars[row - 1][column - 1] == 'M' && chars[row - 2][column - 2] == 'A' && chars[row - 3][column - 3] == 'S') {
        return true;
    }
    return false;
}

bool verifyDownRight(std::vector<std::vector<char>> &chars, int row, int column, const int size) {
    if (chars[row + 1][column + 1] == 'M' && chars[row + 2][column + 2] == 'A' && chars[row + 3][column + 3] == 'S') {
        return true;
    }
    return false;
}

bool verifyDownLeft(std::vector<std::vector<char>> &chars, int row, int column, const int size) {
    if (chars[row + 1][column - 1] == 'M' && chars[row + 2][column - 2] == 'A' && chars[row + 3][column - 3] == 'S') {
        return true;
    }
    return false;
}


void verifySorrunding(std::vector<std::vector<char>> &chars, int row, int column, const int size, int &result) {
    if(row >= 3) { // Check up
        if(verifyUp(chars, row, column, size)) {
            result++;
        }
    }

    if(row < size - 3) { // Check down
        if(verifyDown(chars, row, column, size)) {
            result++;
        }
    }

    if(column >= 3) { // Check left
        if(verifyLeft(chars, row, column, size)) {
            result++;
        }
    }
    if(column < size - 3) { // Check right
        if(verifyRight(chars, row, column, size)) {
            result++;
        }
    }

    if(row >= 3 && column >= 3) { // Check up left
        if(verifyUpLeft(chars, row, column, size)) {
            result++;
        }
    }

    if(row >= 3 && column < size - 3) { // Check up right
        if(verifyUpRight(chars, row, column, size)) {
            result++;
        }
    }

    if(row < size - 3 && column >= 3) { // Check down left
        if(verifyDownLeft(chars, row, column, size)) {
            result++;
        }
    }

    if(row < size - 3 && column < size - 3) { // Check down right
        if(verifyDownRight(chars, row, column, size)) {
            result++;
        }
    }
}

std::string coordsToString(int row, int column) {
    return std::to_string(row) + std::to_string(column);
}

void saveMToCache(std::vector<std::string> &countedMCache, int row, int column) {
    countedMCache.push_back(coordsToString(row, column));
}

bool isMCached(std::vector<std::string> &countedMCache, int row, int column) {
    auto it = std::find(countedMCache.begin(), countedMCache.end(), coordsToString(row, column));
    if(it != countedMCache.end()) {
        return true;
    }
    return false;
}

bool verifyMasUpRight(std::vector<std::vector<char>> &chars, int row, int column, const int size, std::vector<std::string> &countedMCache) {
    if (
        (
            (chars[row - 2][column] == 'M' && chars[row - 1][column + 1] == 'A' && chars[row - 2][column + 2] == 'S' && chars[row][column + 2] == 'S') &&
            !isMCached(countedMCache, row - 2, column)
        ) || 
        ((chars[row - 2][column] == 'S' && chars[row - 1][column + 1] == 'A' && chars[row - 2][column + 2] == 'S' && chars[row][column + 2] == 'M') &&
            !isMCached(countedMCache, row , column + 2)
        )
    ) {
        std::cout << "verifyMasUpRight Detected: [" << row << ", " << column << "]" << std::endl; 
        return true;
    }
    return false;
}

bool verifyMasUpLeft(std::vector<std::vector<char>> &chars, int row, int column, const int size, std::vector<std::string> &countedMCache) {
    if (
        (
            (chars[row - 2][column] == 'S' && chars[row - 1][column - 1] == 'A' && chars[row - 2][column - 2] == 'S' && chars[row][column - 2] == 'M') &&
            !isMCached(countedMCache, row, column - 2)
         ) ||
        ((chars[row - 2][column] == 'M' && chars[row - 1][column - 1] == 'A' && chars[row - 2][column - 2] == 'S' && chars[row][column - 2] == 'S')
            && !isMCached(countedMCache, row - 2, column)
        )
    ) {
        std::cout << "verifyMasUpLeft Detected: [" << row << ", " << column << "]" << std::endl; 
        return true;
    }
    return false;
}

bool verifyMasDownLeft(std::vector<std::vector<char>> &chars, int row, int column, const int size, std::vector<std::string> &countedMCache) {
    if (
        (
            (chars[row + 2][column] == 'M' && chars[row + 1][column - 1] == 'A' && chars[row + 2][column - 2] == 'S' && chars[row][column - 2] == 'S') &&
            !isMCached(countedMCache, row + 2, column)
        ) ||
        ((chars[row + 2][column] == 'S' && chars[row + 1][column - 1] == 'A' && chars[row + 2][column - 2] == 'M' && chars[row][column - 2] == 'S') &&
            !isMCached(countedMCache, row + 2, column - 2)
        )
    ){
        std::cout << "verifyMasDownLeft Detected: [" << row << ", " << column << "]" << std::endl; 
        return true;
    }
    return false;
}

bool verifyMasDownRight(std::vector<std::vector<char>> &chars, int row, int column, const int size, std::vector<std::string> &countedMCache) {
    if (
        (
            (chars[row + 2][column] == 'M' && chars[row + 1][column + 1] == 'A' && chars[row + 2][column + 2] == 'S' && chars[row][column + 2] == 'S') &&
            !isMCached(countedMCache, row + 2, column)
        ) || 
        ((chars[row + 2][column] == 'S' && chars[row + 1][column + 1] == 'A' && chars[row + 2][column + 2] == 'S' && chars[row][column + 2] == 'M')
            && !isMCached(countedMCache, row, column + 2)
        )
    ) {
        std::cout << "verifyMasDownRight Detected: [" << row << ", " << column << "]" << std::endl; 
        return true;
    }
    return false;
}



void verifySorrundingCrossMas(std::vector<std::vector<char>> &chars, int row, int column, const int size, int &result,  std::vector<std::string> & countedMCache) {
    if(row >= 2 && column >= 2) { // Check up left
        if(verifyMasUpLeft(chars, row, column, size, countedMCache) && !isMCached(countedMCache, row, column)) {
            saveMToCache(countedMCache, row, column);
            result++;
        }
    }

    if(row >= 2 && column < size - 2) { // Check up right
        if(verifyMasUpRight(chars, row, column, size, countedMCache) && !isMCached(countedMCache, row, column)) {
            saveMToCache(countedMCache, row, column);
            result++;
        }
    }

    if(row < size - 2 && column >= 2) { // Check down left
        if(verifyMasDownLeft(chars, row, column, size, countedMCache) && !isMCached(countedMCache, row, column)) {
            saveMToCache(countedMCache, row, column);
            result++;
        }
    }

    if(row < size - 2 && column < size - 2) { // Check down right
        if(verifyMasDownRight(chars, row, column, size, countedMCache) && !isMCached(countedMCache, row, column)) {
            saveMToCache(countedMCache, row, column);
            result++;
        }
    }
}

void countCrossMas(int &result, std::vector<std::vector<char>> &chars) {
    int size = chars.size();

    std::vector<std::string> countedMCache;

    for(int line = 0; line < size; line++) {
        for(int i = 0; i < size; i++) {
            if(chars[line][i] == 'M') {
                verifySorrundingCrossMas(chars, line, i, size, result, countedMCache);
            }
        }
    }
}

/* Function to find each X and check it's sorrounding for pattern */
void countXmasStrings(int &result, std::vector<std::vector<char>> &chars) {
    int size = chars.size();

    for(int line = 0; line < size; line++) {
        for(int i = 0; i < size; i++) {
            if(chars[line][i] == 'X') {
                verifySorrunding(chars, line, i, size, result);
            }
        }
    }
}



int main(int argc, char *argv[])
{
    std::string inputName = DEFAULT_INPUT_NAME;
    std::vector<std::vector<char>> chars;
    int xMasCount = 0;
    int crossMassCount = 0;

    // Read filename from CLI argument if any passed
    if (argc > 1)
    {
        inputName = argv[1];
    }

    // Load text into vector of vectors
    readFile(inputName, chars);

    // Count XMAS
    countXmasStrings(xMasCount, chars);

    // Count CrossMAS
    countCrossMas(crossMassCount, chars);

    // Display result to the console
    std::cout << "Xmas nuber is: " << xMasCount << std::endl;

    // Display result to the console
    std::cout << "CrossMas nuber is: " << crossMassCount << std::endl;

    return 0;
}