//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day08.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

bool is_visible_left(int **map, int row, int col, int cols, int rows) {
    int height = map[row][col];
    for (int i = 0; i < col; i++) {
        if (map[row][i] >= height) {
            return false;
        }
    }
    return true;
}

bool is_visible_right(int **map, int row, int col, int cols, int rows) {
    int height = map[row][col];
    for (int i = col + 1; i < cols; i++) {
        if (map[row][i] >= height) {
            return false;
        }
    }
    return true;
}

bool is_visible_up(int **map, int row, int col, int cols, int rows) {
    int height = map[row][col];
    for (int i = 0; i < row; i++) {
        if (map[i][col] >= height) {
            return false;
        }
    }
    return true;
}

bool is_visible_down(int **map, int row, int col, int cols, int rows) {
    int height = map[row][col];
    for (int i = row + 1; i < rows; i++) {
        if (map[i][col] >= height) {
            return false;
        }
    }
    return true;
}

int scenic_left(int **map, int row, int col, int cols, int rows) {
    int height = map[row][col];
    int score = 0;
    for (int i = col - 1; i >= 0; i--) {
        score++;
        if (map[row][i] >= height) {
            return score;
        }
    }
    return score;
}

int scenic_right(int **map, int row, int col, int cols, int rows) {
    int height = map[row][col];
    int score = 0;
    for (int i = col + 1; i < cols; i++) {
        score++;
        if (map[row][i] >= height) {
            return score;
        }
    }
    return score;
}

int scenic_up(int **map, int row, int col, int cols, int rows) {
    int height = map[row][col];
    int score = 0;
    for (int i = row - 1; i >= 0; i--) {
        score++;
        if (map[i][col] >= height) {
            return score;
        }
    }
    return score;
}

int scenic_down(int **map, int row, int col, int cols, int rows) {
    int height = map[row][col];
    int score = 0;
    for (int i = row + 1; i < rows; i++) {
        score++;
        if (map[i][col] >= height) {
            return score;
        }
    }
    return score;
}


bool is_visible(int **map, int row, int col, int cols, int rows) {
    if (row == 0 || row == rows - 1 || col == 0 || col == cols - 1) {
        return true;
    }
    return is_visible_left(map, row, col, cols, rows) || is_visible_right(map, row, col, cols, rows) || is_visible_down(map, row, col, cols, rows) || is_visible_up(map, row, col, cols, rows);
}

long scenic_score(int **map, int row, int col, int cols, int rows) {
    int left = scenic_left(map, row, col, cols, rows);
    int right = scenic_right(map, row, col, cols, rows);
    int down = scenic_down(map, row, col, cols, rows);
    int up = scenic_up(map, row, col, cols, rows);
    return left * right * up * down;
}


int part1() {
    std::ifstream infile("input.txt");
    std::string line;
    vector<string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    int lineNumber = 0;
    int rows = lines.size();
    int cols = lines[0].size();
    int **map;
    map = new int *[rows];
    for (int i = 0; i < rows; ++i) {
        map[i] = new int[cols];
    }
    while (lineNumber < lines.size()) {
        line = lines[lineNumber];
        for (int i = 0; i < line.size(); i++) {
            cout << line[i] - '0';
            map[lineNumber][i] = line[i] - '0';
        }
        lineNumber++;
        cout << endl;
    }
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            if (is_visible(map, i, j, cols, rows)) {
                sum++;
            }
        }
    }

    long max_score = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            long score = scenic_score(map, i, j, cols, rows);
            if (score > max_score) {
                max_score = score;
            }
        }
    }

    cout << "Part 1: " << sum << endl;
    cout << "Part 2: " << max_score << endl;
    return 0;
}

int part2() {
    std::ifstream infile("input.txt");
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        cout << line << endl;
    }
    return 0;
}

int main() {
    part1();
//    part2();
}