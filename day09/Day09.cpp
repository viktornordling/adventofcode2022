//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day09.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

pair<int, int> add_pos(pair<int, int> pair1, pair<int, int> pair2) {
    return make_pair(pair1.first + pair2.first, pair1.second + pair2.second);
}

void print_map(pair<int, int> head, pair<int, int> tails[]) {
    int minx = -10;
    int maxx = 10;
    int miny = -10;
    int maxy = 5;
    for (int y = miny; y < maxy; y++) {
        for (int x = minx; x < maxx; x++) {
            bool printed = false;
            if (x == head.first && y == head.second) {
                printed = true;
                cout << 'H';
            } else {
                for (int i = 0; i < 10; i++) {
                    if (x == tails[i].first && y == tails[i].second && !printed) {
                        printed = true;
                        cout << i + 1;
                    }
                }
            }
            if (!printed) {
                cout << '.';
            }
        }
        cout << endl;
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
    set<pair<int, int>> visited;
    pair<int, int> hpos = make_pair(0, 0);
    pair<int, int> tpos = make_pair(0, 0);
    visited.insert(tpos);
    while (lineNumber < lines.size()) {
        line = lines[lineNumber];
        cout << line << endl;
        istringstream iss(line);
        char dir;
        int steps;
        iss >> dir >> steps;
        pair<int, int> dirv;
        if (dir == 'R') {
            dirv = make_pair(1, 0);
        } else if (dir == 'L') {
            dirv = make_pair(-1, 0);
        } else if (dir == 'U') {
            dirv = make_pair(0, -1);
        } else if (dir == 'D') {
            dirv = make_pair(0, 1);
        }
        for (int i = 0; i < steps; i++) {
            hpos = add_pos(hpos, dirv);
            if (hpos.second - tpos.second > 1 && hpos.first != tpos.first) {
                // diagnoal 1, up right
                // diagnoal 2, up left
                tpos.second = hpos.second - 1;
                tpos.first = hpos.first;
            } else if (hpos.second - tpos.second < -1 && hpos.first != tpos.first) {
                // diagnoal 3, down right
                // diagnoal 4, down left
                tpos.second = hpos.second + 1;
                tpos.first = hpos.first;
            } else if (hpos.first - tpos.first > 1 && hpos.second != tpos.second) {
                // diagnoal 5, right up
                // diagnoal 6, right down
                tpos.first = hpos.first - 1;
                tpos.second = hpos.second;
            } else if (hpos.first - tpos.first < -1 && hpos.second != tpos.second) {
                // diagnoal 5, right up
                // diagnoal 6, right down
                tpos.first = hpos.first + 1;
                tpos.second = hpos.second;
            } else if (hpos.first - tpos.first > 1) {
                tpos.first = hpos.first - 1;
            } else if (hpos.first - tpos.first < -1) {
                tpos.first = hpos.first + 1;
            } else if (hpos.second - tpos.second > 1) {
                tpos.second = hpos.second - 1;
            } else if (hpos.second - tpos.second < -1) {
                tpos.second = hpos.second + 1;
            }
            cout << "tpos: " << tpos.first << "," << tpos.second << endl;
            visited.insert(tpos);
        }
        lineNumber++;
    }

    int sum = 0;
    int sum2 = 0;
    cout << "Part 1: " << visited.size() << endl;
    cout << "Part 2: " << sum2 << endl;
    return 0;
}

int part2() {
    std::ifstream infile("input.txt");
    std::string line;
    vector<string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    int lineNumber = 0;
    set<pair<int, int>> visited;
    pair<int, int> hpos = make_pair(0, 0);
    pair<int, int> tails[9];
    visited.insert(tails[8]);
    while (lineNumber < lines.size()) {
        line = lines[lineNumber];
        cout << line << endl;
        istringstream iss(line);
        char dir;
        int steps;
        iss >> dir >> steps;
        pair<int, int> dirv;
        if (dir == 'R') {
            dirv = make_pair(1, 0);
        } else if (dir == 'L') {
            dirv = make_pair(-1, 0);
        } else if (dir == 'U') {
            dirv = make_pair(0, -1);
        } else if (dir == 'D') {
            dirv = make_pair(0, 1);
        }
        for (int i = 0; i < steps; i++) {
            hpos = add_pos(hpos, dirv);
            for (int a = 0; a < 9; a++) {
                pair<int, int> head;
                if (a == 0) {
                    head = hpos;
                } else {
                    head = tails[a - 1];
                }
                pair<int, int> tail = tails[a];
                if (head.second - tail.second > 1 && head.first != tail.first) {
                    // diagnoal 1, up right
                    // diagnoal 2, up left
                    tail.second = head.second - 1;
                    if (tail.first < head.first) {
                        tail.first++;
                    } else {
                        tail.first--;
                    }
                } else if (head.second - tail.second < -1 && head.first != tail.first) {
                    // diagnoal 3, down right
                    // diagnoal 4, down left
                    tail.second = head.second + 1;
                    if (tail.first < head.first) {
                        tail.first++;
                    } else {
                        tail.first--;
                    }
                } else if (head.first - tail.first > 1 && head.second != tail.second) {
                    // diagnoal 5, right up
                    // diagnoal 6, right down
                    tail.first = head.first - 1;
                    if (tail.second < head.second) {
                        tail.second++;
                    } else {
                        tail.second--;
                    }
                } else if (head.first - tail.first < -1 && head.second != tail.second) {
                    // diagnoal 5, right up
                    // diagnoal 6, right down
                    tail.first = head.first + 1;
                    if (tail.second < head.second) {
                        tail.second++;
                    } else {
                        tail.second--;
                    }
                } else if (head.first - tail.first > 1) {
                    tail.first = head.first - 1;
                } else if (head.first - tail.first < -1) {
                    tail.first = head.first + 1;
                } else if (head.second - tail.second > 1) {
                    tail.second = head.second - 1;
                } else if (head.second - tail.second < -1) {
                    tail.second = head.second + 1;
                }
                tails[a] = tail;
            }
            cout << "tpos: " << tails[8].first << "," << tails[8].second << endl;
            visited.insert(tails[8]);
//            print_map(hpos, tails);
        }
        lineNumber++;
    }

    cout << "Part 2: " << visited.size() << endl;
    return 0;
}


int main() {
//    part1();
    part2();
}