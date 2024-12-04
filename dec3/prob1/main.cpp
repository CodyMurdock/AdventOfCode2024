#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main() {
    std::ifstream inputFile("/home/cody/Git_Repos/FunPrograms/AdventOfCode2024/dec3/prob1/input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
        return 1;
    }

    std::string line;
    std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::smatch match;
    int sum = 0;

    while (std::getline(inputFile, line)) {
        while (std::regex_search(line, match, pattern)) {
            int num1 = std::stoi(match[1].str());
            int num2 = std::stoi(match[2].str());
            sum += num1 * num2;
            line = match.suffix().str();
        }
    }

    inputFile.close();
    std::cout << "The sum of all products is: " << sum << std::endl;
    return 0;
}