#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

#define DEFAULT_INPUT_NAME  "3/input.txt"
#define LINE_BUFFER_SIZE 4192 //B

void readRealMulString(const std::string &filename, std::vector<std::string> & validExpressions, std::regex regex_pattern) {

    // Open file to read data
    std::ifstream file(filename);
    char lineBuffer[LINE_BUFFER_SIZE];

    // Ensure we have access to file with data
    if (!file.is_open())
    {
        throw std::runtime_error("Error: Unable to open file " + filename);
    }

    // Reading data line by line
    while(file.getline(lineBuffer, LINE_BUFFER_SIZE)) {
        std::string line (lineBuffer);
        auto matches_begin = std::sregex_iterator(line.begin(), line.end(), regex_pattern);
        auto matches_end = std::sregex_iterator();

        // Adding matching results to the vector with valid mules
        for (std::sregex_iterator i = matches_begin; i != matches_end; ++i) {
            std::smatch match = *i;
            validExpressions.push_back(match.str());
        }
    }

    file.close();
    return;
}

int calculateVauleFromValidStrings(std::vector<std::string> & validExpressions) {
    std::regex first_number_pattern(R"(\bmul\((\d+),\d+\))");
    std::regex second_number_pattern(R"(\bmul\(\d+,(\d+)\))");
    std::smatch match1;
    std::smatch match2;

    int result = 0;

    for(auto text: validExpressions) {
        // Extracting two numbers from string with following pattern "mul(123,123)"
        std::regex_search(text, match1, first_number_pattern);
        std::regex_search(text, match2, second_number_pattern);

        // adding result of multiplication those numbers
        result += (std::stoi(match1[1]) * std::stoi(match2[1])); 
    }

    return result;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> validExpressions;
    std::regex mulRegexPattern(R"(mul\(\d+,\d+\))");
    std::string inputName = DEFAULT_INPUT_NAME;

    // Read filename from CLI argument if any passed
    if(argc > 1) {
        inputName = argv[1];
    }

    // Parsing text to valid mules expressions
    readRealMulString(inputName, validExpressions, mulRegexPattern);

    // Calculate sum from multiplying both numbers for each valid mule expression
    int result = calculateVauleFromValidStrings(validExpressions);

    // Displaying result to the console
    std::cout << "Result is: " << result << std::endl;

    return 0;
}