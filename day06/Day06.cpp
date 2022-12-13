//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day06.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;


int find_packet(int offset) {
    std::ifstream infile("input.txt");
    map<int, stack<int>> stacks;
    std::string line;
    std::getline(infile, line);
    for (int i = 0; i < line.size(); i++) {
        if (i >= offset - 1) {
            set<char> seen;
            bool unique = true;
            for (int j = i - (offset - 1); j <= i; j++) {
                if (seen.find(line[j]) != seen.end()) {
                    unique = false;
                    break;
                }
                seen.insert(line[j]);
            }
            if (unique) {
                return i + 1;
            }
        }
    }
    return 0;
}

int main() {
    cout << "Part 1: " << find_packet(4) << endl;
    cout << "Part 2: " << find_packet(14) << endl;
}