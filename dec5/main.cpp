#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

bool followsRules(const std::vector<int>& list, const std::unordered_map<int, std::unordered_set<int>>& rules) {
    std::unordered_map<int, int> positions;
    for (int i = 0; i < list.size(); ++i) {
        positions[list[i]] = i;
    }

    for (const auto& rule : rules) {
        int XX = rule.first;
        for (int YY : rule.second) {
            if (positions.find(XX) == positions.end() || positions.find(YY) == positions.end()) {
                continue; // If either number doesn't exist in the list, skip this rule
            }
            if (positions[XX] >= positions[YY]) {
                //std::cout << "Rule violated: " << XX << " | " << YY << std::endl;
                return false;
            }
        }
    }

    return true;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::unordered_map<int, std::unordered_set<int>> rules;
    std::string line;
    bool readingRules = true;

    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            readingRules = false;
            continue;
        }

        if (readingRules) {
            std::istringstream ruleStream(line);
            std::string rule;
            while (std::getline(ruleStream, rule)) {
                int XX = std::stoi(rule.substr(0, rule.find('|')));
                int YY = std::stoi(rule.substr(rule.find('|') + 1));
                rules[XX].insert(YY);
                //std::cout << "Rule added: " << XX << " | " << YY << std::endl;
                
            }
        } else {
            std::istringstream listStream(line);
            std::vector<int> list;
            std::string numberStr;
            while (std::getline(listStream, numberStr, ',')) {
                int number = std::stoi(numberStr);
                list.push_back(number);
            }

            if (followsRules(list, rules)) {
                std::cout << "List follows rules: ";
                for (int num : list) {
                    std::cout << num << " ";
                }
                std::cout << std::endl;

                static std::vector<int> middleNumbers;
                if (list.size() > 2) {
                    middleNumbers.push_back(list[list.size() / 2]);
                }

                // Sum all middle numbers
                int sum = 0;
                for (int num : middleNumbers) {
                    sum += num;
                }
                std::cout << "Already Correct Sum: " << sum << std::endl;
            } else {
                //std::cout << "List does not follow rules: ";
                for (int num : list) {
                    std::cout << num << " ";
                }
                std::cout << std::endl;
            // Attempt to reorder the list to follow the rules
            bool reordered = false;
            do {
                reordered = false;
                for (const auto& rule : rules) {
                    int XX = rule.first;
                    for (int YY : rule.second) {
                        auto posXX = std::find(list.begin(), list.end(), XX);
                        auto posYY = std::find(list.begin(), list.end(), YY);
                        if (posXX != list.end() && posYY != list.end() && posXX >= posYY) {
                            std::iter_swap(posXX, posYY);
                            reordered = true;
                        }
                    }
                }
            } while (reordered && !followsRules(list, rules));

            if (followsRules(list, rules)) {
                std::cout << "Reordered list follows rules: ";
                for (int num : list) {
                    std::cout << num << " ";
                }
                std::cout << std::endl;

                static std::vector<int> middleNumbers;
                if (list.size() > 2) {
                    middleNumbers.push_back(list[list.size() / 2]);
                }

                // Sum all middle numbers
                int sum = 0;
                for (int num : middleNumbers) {
                    sum += num;
                }
                std::cout << "Corrected Sum: " << sum << std::endl;
            } else {
                std::cout << "Unable to reorder list to follow rules: ";
                for (int num : list) {
                    std::cout << num << " ";
                }
                std::cout << std::endl;
            }
            }
        }
    }

    inputFile.close();
    return 0;
}