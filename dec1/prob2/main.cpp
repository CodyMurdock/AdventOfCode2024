#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

int main() {
    std::ifstream inputFile("/home/cody/Git_Repos/FunPrograms/adventofCode2024/dec1/prob2/input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::vector<int> leftColumn;
    std::unordered_map<int, int> rightColumnCount;
    int left, right;

    // Read the input file
    while (inputFile >> left >> right) {
        leftColumn.push_back(left);
        rightColumnCount[right]++;
    }

    inputFile.close();

    int result = 0;

    // Calculate the result
    for (int num : leftColumn) {
        if (rightColumnCount.find(num) != rightColumnCount.end()) {
            result += num * rightColumnCount[num];
        }
    }

    std::cout << "The result is: " << result << std::endl;

    return 0;
}