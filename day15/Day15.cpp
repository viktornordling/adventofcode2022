//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day15.h"
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

class Sensor {
public:
    pair<int, int> pos;
    pair<int, int> beacon;
};

class Rect {
public:
    int minX;
    int maxX;
    int minY;
    int maxY;
};

int manhattan_dist(const pair<int, int> &p1, const pair<int, int> &p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

bool rect_is_small_enough(Rect &rect) {
    return (abs(rect.maxX - rect.minX) < 2 && abs(rect.maxY - rect.minY) < 2);
}

bool area_covered_completely_by_some_sensor(Rect &rect, vector<Sensor> &sensors) {
    for (const auto &sensor: sensors) {
        int dist = manhattan_dist(sensor.pos, sensor.beacon);
        int d1 = manhattan_dist(sensor.pos, make_pair(rect.minX, rect.minY));
        int d2 = manhattan_dist(sensor.pos, make_pair(rect.maxX, rect.minY));
        int d3 = manhattan_dist(sensor.pos, make_pair(rect.minX, rect.maxY));
        int d4 = manhattan_dist(sensor.pos, make_pair(rect.maxX, rect.maxY));
        if (dist >= d1 && dist >= d2 && dist >= d3 && dist >= d4) {
            return true;
        }
    }
    return false;
}

cpp_int quadTree(queue<Rect> &rectQueue, vector<Sensor> &sensors) {
    if (rectQueue.empty()) {
        cout << "empty!" << endl;
        return -1;
    }
    while (!rectQueue.empty()) {
        Rect &rect = rectQueue.front();
        rectQueue.pop();

        if (area_covered_completely_by_some_sensor(rect, sensors)) {
            // Skip
        } else if (rect_is_small_enough(rect)) {
            for (int y = rect.minY; y <= rect.maxY; y++) {
                for (int x = rect.minX; x <= rect.maxX; x++) {
                    pair<int, int> point = make_pair(x, y);
                    bool covered = false;
                    for (const auto &sensor: sensors) {
                        int dist = manhattan_dist(sensor.pos, sensor.beacon);
                        int dist2 = manhattan_dist(sensor.pos, point);
                        if (point == sensor.pos) {
                            covered = true;
                            break;
                        } else if (point == sensor.beacon) {
                            covered = true;
                            break;
                        } else if (dist2 <= dist) {
                            covered = true;
                            break;
                        }
                    }
                    if (!covered) {
                        return cpp_int(point.first) * cpp_int(4000000) + cpp_int(point.second);
                    }
                }
            }
        } else {
            int midX = (rect.minX + rect.maxX) / 2;
            int midY = (rect.minY + rect.maxY) / 2;

            Rect rect1 = Rect();
            Rect rect2 = Rect();
            Rect rect3 = Rect();
            Rect rect4 = Rect();

            rect1.minX = rect.minX;
            rect1.maxX = midX;
            rect1.minY = rect.minY;
            rect1.maxY = midY;

            rect2.minX = midX;
            rect2.maxX = rect.maxX;
            rect2.minY = rect.minY;
            rect2.maxY = midY;

            rect3.minX = rect.minX;
            rect3.maxX = midX;
            rect3.minY = midY;
            rect3.maxY = rect.maxY;

            rect4.minX = midX;
            rect4.maxX = rect.maxX;
            rect4.minY = midY;
            rect4.maxY = rect.maxY;

            rectQueue.push(rect1);
            rectQueue.push(rect2);
            rectQueue.push(rect3);
            rectQueue.push(rect4);
        }
    }
    return -1;
}

int solve(const string& fileName, int yline, int maxSearch) {
    std::ifstream infile(fileName);
    string line;
    vector<string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    int sum = 0;
    vector<Sensor> sensors;
    for (int i = 0; i < lines.size(); i++) {
        string line1 = lines[i];

        std::istringstream iss(line1);
        string dummy;
        string xstr;
        string ystr;
        string xstrb;
        string ystrb;
        iss >> dummy >> dummy;
        iss >> xstr;
        iss >> ystr;
        iss >> dummy >> dummy >> dummy >> dummy;
        iss >> xstrb;
        iss >> ystrb;
        int x = stoi(xstr.substr(2, xstr.size() - 1));
        int y = stoi(ystr.substr(2, xstr.size()));
        int xb = stoi(xstrb.substr(2, xstr.size() - 1));
        int yb = stoi(ystrb.substr(2, xstr.size()));
        Sensor sensor;
        sensor.pos = make_pair(x, y);
        sensor.beacon = make_pair(xb, yb);
        sensors.push_back(sensor);
    }
    map<pair<int, int>, char> world;
    for (const auto &sensor: sensors) {
        int diff = manhattan_dist(sensor.pos, sensor.beacon);
        int distToLine = abs(sensor.pos.second - yline);
        if (distToLine <= diff) {
            int steps = abs(distToLine - diff) + 1;
            world[make_pair(sensor.pos.first, yline)] = '#';
            for (int i = 0; i < steps; i++) {
                world[make_pair(sensor.pos.first - i, yline)] = '#';
                world[make_pair(sensor.pos.first + i, yline)] = '#';
            }
        }
    }
    for (const auto &item: sensors) {
        if (item.beacon.second == yline) {
            world[item.beacon] = 'B';
        }
        if (item.pos.second == yline) {
            world[item.beacon] = 'S';
        }
    }
    int minX = 100000000;
    int maxX = -100000000;
    for (const auto &item: world) {
        minX = min(minX, item.first.first);
        maxX = max(maxX, item.first.first);
    }
    for (int x = minX - 2; x < maxX + 3; x++) {
        char c = world[make_pair(x, yline)];
        if (c == '#') {
            sum++;
        }
    }
    cout << endl;

    cout << "Part 1: " << sum << endl;

    Rect rect;
    rect.minX = 0;
    rect.maxX = maxSearch;
    rect.minY = 0;
    rect.maxY = maxSearch;
    queue<Rect> rectQueue;
    rectQueue.push(rect);
    cout << "Part 2: " << quadTree(rectQueue, sensors);
    return 0;
}

int main() {
    solve("input.txt", 2000000, 4000000);
}