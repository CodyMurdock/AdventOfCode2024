#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream inputFile("/home/cody/Git_Repos/FunPrograms/adventofCode2024/dec1/prob1/input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::vector<int> column1;
    std::vector<int> column2;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int num1, num2;
        if (!(iss >> num1 >> num2)) {
            std::cerr << "Error reading numbers from line: " << line << std::endl;
            continue;
        }
        column1.push_back(num1);
        column2.push_back(num2);
    }

    inputFile.close();

    // Sort both columns
    std::sort(column1.begin(), column1.end());
    std::sort(column2.begin(), column2.end());

    // Calculate the sum of differences
    int totalSum = 0;
    for (size_t i = 0; i < column1.size(); ++i) {
        totalSum += std::abs(column1[i] - column2[i]);
    }

    std::cout << "Total sum of differences: " << totalSum << std::endl;

    return 0;
}