//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day03.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int part_1() {
    std::ifstream infile("input.txt");
    std::string line;
    int sum = 0;
    int sum2 = 0;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        cout << line << endl;
        string comp1, comp2;
        comp1 = line.substr(0, line.length() / 2);
        comp2 = line.substr(line.length() / 2, line.length());

        set<char> seen;
        for (const auto &item: comp1) {
            seen.insert(item);
        }
        char dupe;
        for (const auto &item: comp2) {
            if (seen.find(item) != seen.end()) {
                cout << "dupe: " << item << endl;
                dupe = item;
            }
        }
        int val = 0;
        if (isupper(dupe)) {
            val = dupe - 'A' + 27;
        } else {
            val = dupe - 'a' + 1;
        }
        cout << val << endl;
        sum += val;
        cout << "comp1: " << comp1 << " comp2: " << comp2 << endl;
    }
    cout << "Part 1: " << sum << endl;
    return 0;
}

void to_set(string s, set<char>& set) {
    for (const auto &item: s) {
        set.insert(item);
    }
}

int part_2() {
    std::ifstream infile("input.txt");
    std::string line;
    string elf1, elf2, elf3;
    vector<string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    int sum = 0;
    for (int i = 0; i < lines.size(); i += 3) {
        elf1 = lines[i];
        elf2 = lines[i+1];
        elf3 = lines[i+2];
        set<char> elf1_set, elf2_set, elf3_set;
        to_set(elf1, elf1_set);
        to_set(elf2, elf2_set);
        to_set(elf3, elf3_set);
        char badge = 0;
        for (const auto &item: elf1_set) {
            if (elf2_set.find(item) != elf2_set.end() && elf3_set.find(item) != elf3_set.end()) {
                cout << "badge: " << item << endl;
                badge = item;
                break;
            }
        }
        int val = 0;
        if (isupper(badge)) {
            val = badge - 'A' + 27;
        } else {
            val = badge - 'a' + 1;
        }
        cout << val << endl;
        sum += val;
    }
    cout << "Part 2: " << sum << endl;
    return 0;
}

int main() {
//    part_1();
    part_2();
}