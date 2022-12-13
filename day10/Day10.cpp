//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day10.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

void draw(map<pair<int, int>, char> &screen, int cycle, int x) {
    pair<int, int> pos = make_pair((cycle - 1) % 40, (cycle - 1) / 40);
    pair<int, int> sprite_pos = make_pair(x % 40, x / 40);
//    cout << "x == " << x << " cycle = " << cycle << endl;
//    cout << "row = " << pos.second << " col: " << pos.first << endl;
    if (pos.first >= sprite_pos.first - 1 && pos.first <= sprite_pos.first + 1) {
        cout << "draw #" << endl;
        screen[pos] = '#';
    } else {
        cout << "draw ." << endl;
        screen[pos] = '.';
    }
}

int part1() {
    std::ifstream infile("input.txt");
    std::string line;
    vector<string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    int lineNumber = 0;
    int cycle = 1;
    int x = 1;
    map<int, int> xvals;
    map<pair<int, int>, char> screen;
    while (lineNumber < lines.size()) {
        line = lines[lineNumber];
//        cout << line << endl;
        lineNumber++;
        std::istringstream iss(line);
        string instr;
        int num;
        iss >> instr;
        if (instr == "addx") {
            iss >> num;
            draw(screen, cycle, x);
            xvals[++cycle] = x;
//            cout << "cycle: " << cycle << ", x: " << x << endl;
            draw(screen, cycle, x);
            x += num;
            xvals[++cycle] = x;
        } else {
            draw(screen, cycle, x);
            xvals[++cycle] = x;
        }
//        cout << "cycle: " << cycle << ", x: " << x << endl;
    }

    int sum = xvals[20] * 20 + xvals[60]*60 + xvals[100]*100 + xvals[140]*140 + xvals[180]*180 + xvals[220]*220;
    cout << "Part 1: " << sum << endl;
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 40; col++) {
            cout << screen[make_pair(col, row)];
        }
        cout << endl;
    }
    return 0;
}

int main() {
    part1();
//    part2();
}