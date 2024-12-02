#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

bool isSafeReport(const std::vector<int>& row, bool tolerance) {
    bool increasing = row[1] > row[0];
    for (size_t i = 1; i < row.size(); i++) {
        int diff = row[i] - row[i - 1];
        if ((increasing && (diff < 1 || diff > 3)) || (!increasing && (diff > -1 || diff < -3))) {
            if(tolerance == true) {
                std::vector<int> copy = row;
                std::vector<int> copy2 = row;
                std::vector<int> copy3 = row;
                std::vector<int> copy4 = row;
                copy.erase(copy.begin() + i);
                copy2.erase(copy2.begin() + (i - 1));
                copy3.erase(copy3.begin());
                copy4.erase(copy4.begin() + 1);
                
                if(isSafeReport(copy, false)){
                    // std::cout <<"Safe report found after tolerance\n";
                    // std::cout << "Original vector: ";
                    // for (int num : row) {
                    //     std::cout << num << " ";
                    // }
                    // std::cout << "\nVector with element " << row[i] << " removed: ";
                    // for (int num : copy) {
                    //     std::cout << num << " ";
                    // }
                    // std::cout << std::endl;
                    return true;
                } else if(isSafeReport(copy2, false)){
                    // std::cout <<"Safe report found after tolerance\n";
                    // std::cout << "Original vector: ";
                    // for (int num : row) {
                    //     std::cout << num << " ";
                    // }
                    // std::cout << "\nVector with element " << row[i - 1] << " removed: ";
                    // for (int num : copy2) {
                    //     std::cout << num << " ";
                    // }
                    // std::cout << std::endl;
                    return true;
                } else if(isSafeReport(copy3, false)){
                    // std::cout <<"Safe report found after tolerance\n";
                    // std::cout << "Original vector: ";
                    // for (int num : row) {
                    //     std::cout << num << " ";
                    // }
                    // std::cout << "\nVector with element " << row[0] << " removed: ";
                    // for (int num : copy3) {
                    //     std::cout << num << " ";
                    // }
                    // std::cout << std::endl;
                    return true;
                } else{
                    return false;
                }
            }else {
                if(tolerance == false){
                    //std::cout << "Unsafe report found\n";
                    std::cout << "Original vector: ";
                    for (int num : row) {
                        std::cout << num << " ";
                    }
                    std::cout << std::endl;
                }
                return false;
            }
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

        if (isSafeReport(report, true)) {
            ++safeReportCount;
        }
    }

    inputFile.close();

    std::cout << "Total number of safe reports: " << safeReportCount << std::endl;

    return 0;
}