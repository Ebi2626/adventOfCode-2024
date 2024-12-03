#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_set>
#include <vector>

#define DEFAULT_INPUT_NAME "3/input.txt"
#define LINE_BUFFER_SIZE 4192 // B

enum ReadingMode { Active, Inactive };

void readRealMulString(const std::string &filename,
                       std::vector<std::string> &validExpressions,
                       std::regex &regex_pattern) {

  // Open file to read data
  std::ifstream file(filename);
  char lineBuffer[LINE_BUFFER_SIZE];

  // Ensure we have access to file with data
  if (!file.is_open()) {
    throw std::runtime_error("Error: Unable to open file " + filename);
  }

  // Reading data line by line
  while (file.getline(lineBuffer, LINE_BUFFER_SIZE)) {
    std::string line(lineBuffer);
    auto matches_begin =
        std::sregex_iterator(line.begin(), line.end(), regex_pattern);
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

/*
   Function to calculate sum of multipling both numbers from each vector
   position. Each vector position should be string with followin pattern
   mul(n,m) - where n and m are int
*/
int calculateVauleFromValidStrings(std::vector<std::string> &validExpressions) {
  std::regex first_number_pattern(R"(\bmul\((\d+),\d+\))");
  std::regex second_number_pattern(R"(\bmul\(\d+,(\d+)\))");
  std::smatch match1;
  std::smatch match2;

  int result = 0;

  for (auto text : validExpressions) {
    // Extracting two numbers from string with following pattern "mul(123,123)"
    std::regex_search(text, match1, first_number_pattern);
    std::regex_search(text, match2, second_number_pattern);

    // adding result of multiplication those numbers
    result += (std::stoi(match1[1]) * std::stoi(match2[1]));
  }

  return result;
}

/*
    Function to verify current mode or push new valid mule to the vector if current mode is Active
*/
void validateStringBuffer(std::string &stringBuffer,
                          std::vector<std::string> &validExpressions,
                          ReadingMode &currentMode) {
  std::regex does(R"(do\(\))");
  std::regex dont(R"(don't\(\))");
  std::regex mulRegexPattern(R"(mul\(\d+,\d+\))");
  std::smatch match;

  int size = stringBuffer.size();

  // Only for bigger buffers than 3 elements
  if (size> 3) {
    // We are starting from big buffers assuming it should be "mul(n,m)" pattern
    if (size > 7 &&
        std::regex_search(stringBuffer, match, mulRegexPattern)) {
      // We count value only if currentMode is Active
      if (currentMode == Active) {
        validExpressions.push_back(stringBuffer);
      }
      stringBuffer.clear();
      // Here we are testing against "don't()"
    } else if (std::regex_search(stringBuffer, match, dont)) {
      currentMode = Inactive;
      stringBuffer.clear();
      // Hera we are testing against "do()"
    } else if (std::regex_search(stringBuffer, match, does)) {
      currentMode = Active;
      stringBuffer.clear();
    }
  }
}

/*
    Function to push only those mule's which don't appear after "don't()" function 
*/
void countConditionallyCorrectMules(
  const std::string &filename, std::vector<std::string> &validExpressions) {
  // Open file to read data
  std::ifstream file(filename);

  // List of avialable characters
  std::unordered_set<char> letterSet {'d', 'o', 'n', '\'', 't', '(', ')',
                               ',', 'm', 'u', 'l',  '1', '2', '3',
                               '4', '5', '6', '7',  '8', '9', '0'};
  // Mode Active allowing for adding new mules, inactive not
  ReadingMode currentMode = Active;

  char c = '\0';
  std::string stringBuffer;

  // Ensure we have access to file with data
  if (!file.is_open()) {
    throw std::runtime_error("Error: Unable to open file " + filename);
  }

  // Read file char by char
  while (file.get(c)) {

    // Validate if we have buffer big enough to have correct value
    if(stringBuffer.size() > 3) {
        validateStringBuffer(stringBuffer, validExpressions, currentMode);
    }

    // Verify if next char is correct or clear buffer
    if (letterSet.find(c) != letterSet.end()) {

      // Add valid char to the buffer      
      stringBuffer.push_back(c);
    } else {
      // Clear buffer if invalid char occurs  
      stringBuffer.clear();
    }
  }

  file.close();
}

int main(int argc, char *argv[]) {
  std::vector<std::string> validExpressions;
  std::vector<std::string> validExpressions2;
  std::regex mulRegexPattern(R"(mul\(\d+,\d+\))");
  std::string inputName = DEFAULT_INPUT_NAME;

  // Read filename from CLI argument if any passed
  if (argc > 1) {
    inputName = argv[1];
  }

  // Parsing text to valid mules expressions
  readRealMulString(inputName, validExpressions, mulRegexPattern);

  // Parsing text char-by-char to detect do() and don't() mode and add only those mules read in active mode (after do())
  countConditionallyCorrectMules(inputName, validExpressions2);

  // Calculate sum from multiplying both numbers for each valid mule expression
  int result = calculateVauleFromValidStrings(validExpressions);
  int result2 = calculateVauleFromValidStrings(validExpressions2);

  // Displaying result to the console
  std::cout << "Result is: " << result << std::endl;
  std::cout << "Result for second puzzle is: " << result2 << std::endl;

  return 0;
}