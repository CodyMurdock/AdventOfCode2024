#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//924 too low

bool isXShape(const std::vector<std::string>& grid, int row, int col) {
    int n = grid.size();
    int m = grid[0].size();
    //
    //     | M . S | | S . M | | M . M | | S . S |
    //     | . A . | | . A . | | . A . | | . A . |
    //     | M . S | | S . M | | s . S | | M . M |
    // Check for "MAS" in X shape
    if (row - 1 >= 0 && row + 1 < n && col - 1 >= 0 && col + 1 < m) {
        if(((grid[row - 1][col - 1] == 'M' && grid[row + 1][col + 1] == 'S') ||
            (grid[row - 1][col - 1] == 'S' && grid[row + 1][col + 1] == 'M')) &&
           ((grid[row + 1][col - 1] == 'S' && grid[row - 1][col + 1] == 'M') ||
            (grid[row + 1][col - 1] == 'M' && grid[row - 1][col + 1] == 'S'))) {
            return true;
        }
    }
    return false;
}

int countXShapes(const std::vector<std::string>& grid) {
    int count = 0;
    int pseudoCount = 0;
    for (int i = 1; i < grid.size()-1; ++i) {
        for (int j = 1; j < grid[0].size()-1; ++j) {
            if (grid[i][j] == 'A') {
                ++pseudoCount;
                if (isXShape(grid, i, j))
                    ++count;
            }
        }
    }
    std::cout << "Pseudo count: " << pseudoCount << std::endl;
    return count;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::vector<std::string> grid;
    std::string line;
    while (std::getline(inputFile, line)) {
        grid.push_back(line);
    }

    int result = countXShapes(grid);
    std::cout << "Number of X-shaped 'MAS': " << result << std::endl;

    return 0;
}