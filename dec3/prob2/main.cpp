#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
//original 191183308
//19632049 incorrect
//6705633 too low
int main() {
    std::ifstream inputFile("/home/cody/Git_Repos/FunPrograms/AdventOfCode2024/dec3/prob1/input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
        return 1;
    }

    std::string line;
    std::regex mulPattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::regex doPattern(R"(do\(\))");
    std::regex dontPattern(R"(don't\(\))");
    std::smatch match;
    int sum = 0;
    bool enableMul = true;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string token;
        while (iss >> token) {
            if (std::regex_search(token, match, doPattern)) {
                enableMul = true;
                std::cout << "Enabled mul" << std::endl;
            } else if (std::regex_search(token, match, dontPattern)) {
                enableMul = false;
                std::cout << "Disabled mul" << std::endl;
            } else if (enableMul) {
                auto words_begin = std::sregex_iterator(token.begin(), token.end(), mulPattern);
                auto words_end = std::sregex_iterator();
                for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
                    std::smatch match = *i;
                    int num1 = std::stoi(match[1].str());
                    int num2 = std::stoi(match[2].str());
                    sum += num1 * num2;
                    std::cout << "Adding " << num1 << " * " << num2 << " to the sum." << std::endl;
                }
            } else if (!enableMul) {
                auto words_begin = std::sregex_iterator(token.begin(), token.end(), mulPattern);
                auto words_end = std::sregex_iterator();
                for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
                    std::smatch match = *i;
                    int num1 = std::stoi(match[1].str());
                    int num2 = std::stoi(match[2].str());
                    std::cout << "Skipping mul " << num1 << " * " << num2 << std::endl;
                }
            }
        }
    }

    inputFile.close();
    std::cout << "The sum of all products is: " << sum << std::endl;
    return 0;
}