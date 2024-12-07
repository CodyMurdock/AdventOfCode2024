#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
//P1
//412888233236
//5030892084481--------------------------------

//P2
//91377501990670
//
using namespace std;

long testEquation(const string& equation)
{
    string result;
    vector<long> operands;
    stringstream ss(equation);
    getline(ss, result, ':');
    long operand;
    while (ss >> operand) {
        operands.push_back(operand);
    }

    long resultValue = stol(result);
    
    // Check all possible combinations of +, *, and ||
    size_t n = operands.size();
    for (size_t i = 0; i < (1 << (2 * (n - 1))); ++i) {
        long currentResult = operands[0];
        for (size_t j = 0; j < n - 1; ++j) {
            int op = (i >> (2 * j)) & 3;
            if (op == 0) {
                currentResult += operands[j + 1];
            } else if (op == 1) {
                currentResult *= operands[j + 1];
            } else if (op == 2) {
                currentResult = stol(to_string(currentResult) + to_string(operands[j + 1]));
            }
        }
        if (currentResult == resultValue) {
            cout << "Combination sequence found: ";
            currentResult = operands[0];
            cout << operands[0];
            for (size_t j = 0; j < n - 1; ++j) {
                int op = (i >> (2 * j)) & 3;
                if (op == 0) {
                    cout << " + " << operands[j + 1];
                    currentResult += operands[j + 1];
                } else if (op == 1) {
                    cout << " * " << operands[j + 1];
                    currentResult *= operands[j + 1];
                } else if (op == 2) {
                    cout << " || " << operands[j + 1];
                    currentResult = stol(to_string(currentResult) + to_string(operands[j + 1]));
                }
            }
            cout << " = " << result << endl;
            return currentResult;
        }
    }

    // Placeholder return value
    return 0;
}
int main()
{
    fstream f = fstream("input.txt");
    string ln;
    
    vector<string> equations;
    while (getline(f, ln))
    {
        equations.push_back(ln);
    }
    long sum = 0;
    // Print the equations to verify
    for (const auto& equation : equations)
    {
        sum += testEquation(equation);
    }
    cout << "results: " << sum << endl;
    
    return 0;
}