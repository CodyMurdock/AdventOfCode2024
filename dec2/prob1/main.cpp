#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

bool isSafeReport(const std::vector<int>& row) {
    bool increasing = row[1] > row[0];
    for (size_t i = 1; i < row.size(); ++i) {
        int diff = row[i] - row[i - 1];
        if ((increasing && (diff < 1 || diff > 3)) || (!increasing && (diff > -1 || diff < -3))) {
            return false;
        }
    }
    return true;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    int safeReportCount = 0;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::vector<int> report;
        int number;
        while (iss >> number) {
            report.push_back(number);
        }

        if (isSafeReport(report)) {
            ++safeReportCount;
        }
    }

    inputFile.close();

    std::cout << "Total number of safe reports: " << safeReportCount << std::endl;

    return 0;
}