//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day18.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;


int solve(const string& fileName) {
    std::ifstream infile(fileName);
    string line;
    vector<string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    int sum = 0;
    set<tuple<int, int, int>> world;
    int minX = 100;
    int maxX = -100;
    int minY = 100;
    int maxY = -100;
    int minZ = 100;
    int maxZ = -100;
    for (int i = 0; i < lines.size(); i++) {
        string line1 = lines[i];

        std::istringstream iss(line1);
        int x, y, z;
        char dummy;
        iss >> x >> dummy >> y >> dummy >> z;
        cout << "x " << x << " y " << y << " z " << endl;
        world.insert(make_tuple(x, y, z));
        minX = std::min(minX, x);
        maxX = std::max(maxX, x);
        minY = std::min(minY, y);
        maxY = std::max(maxY, y);
        minZ = std::min(minZ, z);
        maxZ = std::max(maxZ, z);
    }
    vector<tuple<int, int, int>> dirs;
    dirs.push_back(make_tuple(0, 0, 1));
    dirs.push_back(make_tuple(0, 0, -1));
    dirs.push_back(make_tuple(0, 1, 0));
    dirs.push_back(make_tuple(0, -1, 0));
    dirs.push_back(make_tuple(1, 0, 0));
    dirs.push_back(make_tuple(-1, 0, 0));
    for (const auto &item : world) {
        int free = 0;
        for (const auto &dir: dirs) {
            tuple<int, int, int> n = make_tuple(std::get<0>(item) + std::get<0>(dir), std::get<1>(item) + std::get<1>(dir), std::get<2>(item) + std::get<2>(dir));
            if (world.find(n) == world.end()) {
                free++;
            }
        }
        sum += free;
    }

    cout << "Part 1: " << sum << endl;

    minX -= 3;
    minY -= 3;
    minZ -= 3;

    maxX += 3;
    maxY += 3;
    maxZ += 3;

    set<tuple<int, int, int>> inside;
    set<tuple<int, int, int>> outside;
    for (int x = minX; x < maxX; x++) {
        for (int y = minY; y < maxY; y++) {
            for (int z = minZ; z < maxZ; z++) {
                cout << "x = " << x << " y = " << y << " z = " << z << endl;
                tuple<int, int, int> cur = make_tuple(x, y, z);
                if (inside.find(cur) != inside.end() || outside.find(cur) != outside.end() || world.find(cur) != world.end()) {
                    continue;
                }
                set<tuple<int, int, int>> flood;
                queue<tuple<int, int, int>> ns;
                ns.push(cur);
                bool is_outside = false;
                while (!ns.empty()) {
                    const auto& item = ns.front();
                    ns.pop();
                    flood.insert(item);
                    cout << "pop" << "x = " << std::get<0>(item) << " y = " << std::get<1>(item) << " z = " << std::get<2>(item) << endl;
                    for (const auto &dir: dirs) {
                        tuple<int, int, int> n = make_tuple(std::get<0>(item) + std::get<0>(dir), std::get<1>(item) + std::get<1>(dir), std::get<2>(item) + std::get<2>(dir));
                        if (inside.find(n) != inside.end() || outside.find(n) != outside.end() || flood.find(n) != flood.end()) {
                            // continue
                        } else if (std::get<0>(n) <= minX || std::get<0>(n) >= maxX || std::get<1>(n) <= minY || std::get<1>(n) >= maxY || std::get<2>(n) <= minZ || std::get<2>(n) >= maxZ) {
                            is_outside = true;
                        } else if (world.find(n) == world.end() && outside.find(n) == outside.end() && inside.find(n) == inside.end()) {
                            cout << "inserting. maxY = " << maxY << " y = " << std::get<1>(n) << endl;
                            flood.insert(n);
                            ns.push(n);
                        }
                    }
                }
                if (is_outside) {
                    for (const auto& item : flood) {
                        outside.insert(item);
                    }
                } else {
                    for (const auto& item : flood) {
                        inside.insert(item);
                    }
                }
            }
        }
    }

    sum = 0;
    for (const auto &item : world) {
        int free = 0;
        for (const auto &dir: dirs) {
            tuple<int, int, int> n = make_tuple(std::get<0>(item) + std::get<0>(dir), std::get<1>(item) + std::get<1>(dir), std::get<2>(item) + std::get<2>(dir));
            if (world.find(n) == world.end() && outside.find(n) == outside.end()) {
                cout << "not adding " << "x = " << std::get<0>(n) << " y = " << std::get<1>(n) << " z = " << std::get<2>(n) << " because it's not outside " << endl;
            }
//            if (world.find(n) == world.end() && inside.find(n) != inside.end()) {
//                cout << "not adding " << "x = " << std::get<0>(n) << " y = " << std::get<1>(n) << " z = " << std::get<2>(n) << " because it's inside " << endl;
//            }
            if (world.find(n) == world.end() && outside.find(n) != outside.end()) {
                free++;
            }
        }
        sum += free;
    }

    cout << "Part 2: " << sum << endl;

    return 0;
}

int main() {
    solve("input.txt");
}