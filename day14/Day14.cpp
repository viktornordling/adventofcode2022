//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day14.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int MAX_Y = 0;

void draw_world(map<pair<int, int>, char> &world) {
    int minX = 480;
    int maxX = 520;
    int minY = 0;
    int maxY = 14;

    for (int y = minY; y < maxY; y++) {
        for (int x = minX; x < maxX; x++) {
            char c = world[make_pair(x, y)];
            if (c == 0) {
                c = '.';
            }
            cout << c;
        }
        cout << endl;
    }
    cout << endl;
}

void parse_line(map<pair<int, int>, char> &world, string &line) {
    std::istringstream iss(line);
    pair<int, int> curPos = make_pair(-1, -1);
    while (iss.peek() != -1) {
        int x;
        int y;
        char d;
        string dummy;
        iss >> x;
        iss >> d;
        iss >> y;
        iss >> dummy;
        cout << "x = " << x << " y = " << y << endl;
        pair<int, int> newPos = make_pair(x, y);
        if (curPos.first != -1) {
            if (curPos.first == newPos.first) {
                int step = 1;
                if (newPos.second < curPos.second) {
                    step = -1;
                }
                int i;
                for (i = curPos.second; i != newPos.second; i += step) {
                    world[make_pair(curPos.first, i)] = '#';
                }
                world[make_pair(curPos.first, i)] = '#';
            } else {
                int step = 1;
                if (newPos.first < curPos.first) {
                    step = -1;
                }
                int i;
                for (i = curPos.first; i != newPos.first; i += step) {
                    world[make_pair(i, curPos.second)] = '#';
                }
                world[make_pair(i, curPos.second)] = '#';
            }
        }
        curPos = newPos;
        if (curPos.second > MAX_Y) {
            MAX_Y = curPos.second;
        }
    }
}

bool drop_sand(map<pair<int, int>, char> &world) {
    pair<int, int> sand_pos = make_pair(500, 0);
    if (world[make_pair(sand_pos.first, sand_pos.second + 1)] != 0 &&
        world[make_pair(sand_pos.first - 1, sand_pos.second + 1)] != 0 &&
        world[make_pair(sand_pos.first + 1, sand_pos.second + 1)] != 0) {
        return false;
    }

    while (sand_pos.second < MAX_Y) {
        if (sand_pos.second + 1 == MAX_Y) {
            world[make_pair(sand_pos.first, sand_pos.second + 1)] = '#';
            world[make_pair(sand_pos.first - 1, sand_pos.second + 1)] = '#';
            world[make_pair(sand_pos.first + 1, sand_pos.second + 1)] = '#';
        }
        if (world[make_pair(sand_pos.first, sand_pos.second + 1)] == 0) {
            world[make_pair(sand_pos.first, sand_pos.second + 1)] = 'o';
            world[make_pair(sand_pos.first, sand_pos.second)] = 0;
            sand_pos = make_pair(sand_pos.first, sand_pos.second + 1);
        } else if (world[make_pair(sand_pos.first, sand_pos.second + 1)] != 0 && world[make_pair(sand_pos.first - 1, sand_pos.second + 1)] == 0) {
            world[make_pair(sand_pos.first - 1, sand_pos.second + 1)] = 'o';
            world[make_pair(sand_pos.first, sand_pos.second)] = 0;
            sand_pos = make_pair(sand_pos.first - 1, sand_pos.second + 1);
        } else if (world[make_pair(sand_pos.first, sand_pos.second + 1)] != 0 && world[make_pair(sand_pos.first + 1, sand_pos.second + 1)] == 0) {
            world[make_pair(sand_pos.first + 1, sand_pos.second + 1)] = 'o';
            world[make_pair(sand_pos.first, sand_pos.second)] = 0;
            sand_pos = make_pair(sand_pos.first + 1, sand_pos.second + 1);
        } else {
            break;
        }
    }
//    if (sand_pos.second == MAX_Y) {
//        world[sand_pos] = 0;
//        return false;
//    }
    return true;
}

int part1() {
    std::ifstream infile("input.txt");
    string line;
    vector<string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    map<pair<int, int>, char> world;
    for (int i = 0; i < lines.size(); i++) {
        string line1 = lines[i];

        cout << "line1: " << line1 << endl;

        std::istringstream iss(line1);
        parse_line(world, line1);
    }
    MAX_Y = MAX_Y + 2;
    cout << "MAXY = " << MAX_Y << endl;
    draw_world(world);
    int result = true;
    int count = 0;
    while (result) {
        result = drop_sand(world);
        count++;
//        if (count == 92) {
//            draw_world(world);
//        }
    }
    draw_world(world);

    cout << "Part 1: " << count << endl;
    return 0;
}

int main() {
    part1();
//    part2();
}