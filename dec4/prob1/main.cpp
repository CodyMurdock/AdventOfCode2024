#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool searchWord(const vector<string>& grid, int row, int col, const string& word, int rowDir, int colDir) {
    int n = grid.size();
    int m = grid[0].size();
    int len = word.length();

    for (int i = 0; i < len; ++i) {
        int newRow = row + i * rowDir;
        int newCol = col + i * colDir;

        if (newRow < 0 || newRow >= n || newCol < 0 || newCol >= m || grid[newRow][newCol] != word[i]) {
            return false;
        }
    }
    return true;
}

int countWordInstances(const vector<string>& grid, const string& word) {
    int n = grid.size();
    int m = grid[0].size();
    int count = 0;
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {1, 1}, {1, -1}, {0, -1}, {-1, 0}, {-1, -1}, {-1, 1}};

    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < m; ++col) {
            for (const auto& dir : directions) {
                if (searchWord(grid, row, col, word, dir.first, dir.second)) {
                    ++count;
                }
            }
        }
    }
    return count;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error opening input file" << endl;
        return 1;
    }

    vector<string> grid;
    string line;
    while (getline(inputFile, line)) {
        grid.push_back(line);
    }

    inputFile.close();

    string word = "XMAS";
    int totalInstances = countWordInstances(grid, word);

    cout << "Total instances of \"" << word << "\": " << totalInstances << endl;

    return 0;
}