//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day04.h"
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
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int a1, a2, b1, b2;
        char dummy;
        iss >> a1 >> dummy >> a2 >> dummy >> b1 >> dummy >> b2;
        if ((a1 >= b1 && a2 <= b2) || (b1 >= a1 && b2 <= a2)) {
            sum++;
        }
    }
    cout << "Part 1: " << sum << endl;
    return 0;
}

int part_2() {
    std::ifstream infile("input.txt");
    std::string line;
    int sum = 0;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int a1, a2, b1, b2;
        char dummy;
        iss >> a1 >> dummy >> a2 >> dummy >> b1 >> dummy >> b2;
        if ((a1 >= b1 && a1 <= b2) || (a2 <= b2 && a2 >= b1) || (b2 >= a1 && b1 <= a2) || (b2 <= a2 && b2 >= a1)) {
            sum++;
        }
    }
    cout << "Part 1: " << sum << endl;
    return 0;
}

int main() {
    part_1();
    part_2();
}