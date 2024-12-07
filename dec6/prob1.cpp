#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void turnRight(char &direction) {
    switch (direction) {
        case '>': direction = 'v'; break;
        case 'v': direction = '<'; break;
        case '<': direction = '^'; break;
        case '^': direction = '>'; break;
    }
}

void move(int &x, int &y, char direction) {
    switch (direction) {
        case '>': y++; break;
        case 'v': x++; break;
        case '<': y--; break;
        case '^': x--; break;
    }
}

bool isValidMove(int newX, int newY, const vector<string> &map) {
    return newX >= 0 && newX < map.size() && newY >= 0 && newY < map[0].size() && map[newX][newY] != '#';
}

bool isWithinBounds(int x, int y, const vector<string> &map) {
    return x >= 0 && x < map.size() && y >= 0 && y < map[0].size();
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    vector<string> map;
    string line;
    while (getline(inputFile, line)) {
        map.push_back(line);
    }
    inputFile.close();

    int rows = map.size();
    int cols = map[0].size();
    int x, y;
    char direction;
    bool found = false;

    for (int i = 0; i < rows && !found; ++i) {
        for (int j = 0; j < cols && !found; ++j) {
            if (map[i][j] == '>' || map[i][j] == 'v' || map[i][j] == '<' || map[i][j] == '^') {
                x = i;
                y = j;
                direction = map[i][j];
                if (isValidMove(i, j, map)) {
                    map[i][j] = 'X';
                    found = true;
                }
            }
        }
    }

    while (true) {
        int newX = x, newY = y;
        move(newX, newY, direction);

        if (!isWithinBounds(newX, newY, map) || !isValidMove(newX, newY, map)) {
            turnRight(direction);
            while (!isWithinBounds(newX, newY, map) || !isValidMove(newX, newY, map)) {
                turnRight(direction);
                move(newX, newY, direction);
            }
        } else {
            x = newX;
            y = newY;
            map[x][y] = 'X';
        }
    }

    ofstream outputFile("output.txt");
    if (!outputFile) {
        cerr << "Error opening output file" << endl;
        return 1;
    }

    for (const auto &row : map) {
        outputFile << row << endl;
    }
    outputFile.close();

    int countX = 0;
    for (const auto &row : map) {
        for (const auto &ch : row) {
            if (ch == 'X') {
                countX++;
            }
        }
    }

    cout << "Number of spaces containing 'X': " << countX << endl;

    return 0;
}
