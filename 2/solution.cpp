#include <vector>
#include <iostream>
#include <fstream>
#include <string>

bool isSafe(std::vector<int> &numbers) {
    bool isIncreasig = numbers[0] < numbers[1];
    int diff = 0;

    for(int i = 1; i < numbers.size(); i++) {
        if(isIncreasig) {
            diff = numbers[i] - numbers[i-1];
            return diff > 0 && diff < 4;
        } else if(!isIncreasig) {
            diff = numbers[i-1] - numbers[i];
            return diff > 0 && diff < 4;
        }
    }

    // sprawdzić wersję z auto wraz ze zmienną pomocniczą na poprzednią wartość (logika od indexu 1)
}

std::vector<std::vector<int>> getDataFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    char currentLine[64];
    char schowek[64];

    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }



    std::vector<bool> data;

    while(file) {
        file.getline(currentLine, 64);
        std::vector<int> numbers;
        std::string currentNumber = "";
        for (int i = 0; i < 64; i++) {
            if (currentLine[i] == ' ') {
                numbers.push_back(std::stoi(currentNumber));
                currentNumber = "";
            } else if (currentLine[i] == '\0') {
                numbers.push_back(std::stoi(currentNumber));
                currentNumber = "";
                break;
            } else {
               currentNumber += currentLine[i];
            }

            
        }
    }
}

int main()
{
    int result = 0;

    return 0;
}