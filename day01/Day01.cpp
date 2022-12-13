//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day01.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    std::ifstream infile("input.txt");
    std::string line;
    int sum = 0;
    int maxSum = 0;
    vector<int> sums;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        if (line.empty()) {
            if (sum > maxSum) {
                maxSum = sum;
            }
            sums.push_back(sum);
            sum = 0;
        } else {
            int a;
            iss >> a;
            sum += a;
        }
    }
    sums.push_back(sum);
    int sum2 = 0;
    make_heap(sums.begin(), sums.end());
    for (int i = 0; i < 3; i++) {
        sum2 += sums.front();
        pop_heap (sums.begin(), sums.end());
        sums.pop_back();
    }
    cout << "Part 1:" << maxSum << endl;
    cout << "Part 2:" << sum2 << endl;
    return 0;
}