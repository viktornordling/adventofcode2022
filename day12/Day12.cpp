//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day12.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <queue>

using namespace std;

set<pair<int, int>> visited;
map<pair<int, int>, char> elevationMap;
map<pair<int, int>, pair<int, int>> predMap;

int bfs(map<pair<int, int>, vector<pair<int, int>>> &nMap, const pair<int, int> &curPos, pair<int, int> &endPos) {
    cout << "visiting: " << curPos.first << ", " << curPos.second << " " << elevationMap[curPos] << endl;
    queue<pair<int, int>> theq;
    theq.push(curPos);
    visited.insert(curPos);
    int steps = 0;
    while (!theq.empty()) {
        pair<int, int> popped = theq.front();
        theq.pop();
        if (popped == endPos) {
            return steps;
        }
        steps++;
        vector<pair<int, int>> neighbors = nMap[popped];
        for (const auto &item: neighbors) {
            if (visited.find(item) == visited.end()) {
                visited.insert(item);
                if (item == popped) {
                    cout << "This is not right" << endl;
                }
                predMap[item] = popped;
                theq.push(item);
            }
        }
    }
    return -1;
}

int part1() {
    std::ifstream infile("input.txt");
    std::string line;
    vector<string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    int lineNumber = 0;

    int y = 0;
    int maxX = 0;
    int maxY = 0;
    pair<int, int> startPos;
    pair<int, int> endPos;
    set<pair<int, int>> startPositions;
    while (lineNumber < lines.size()) {
        maxY = max(maxY, y);
        line = lines[lineNumber];
        for (int x = 0; x < line.size(); x++) {
            char cur = line[x];
            if (cur == 'S') {
                cur = 'a';
                startPos = make_pair(x, y);
            } else if (cur == 'E') {
                cur = 'z' + 1;
                endPos = make_pair(x, y);
            }
            if (cur == 'a') {
                startPositions.insert(make_pair(x, y));
            }
            elevationMap[make_pair(x, y)] = cur;
            maxX = max(maxX, x);
        }
        lineNumber++;
        y++;
    }
    vector<pair<int, int>> dirs;
    dirs.emplace_back(make_pair(1, 0));
    dirs.emplace_back(make_pair(-1, 0));
    dirs.emplace_back(make_pair(0, 1));
    dirs.emplace_back(make_pair(0, -1));
    map<pair<int, int>, vector<pair<int, int>>> nMap;
    for (y = 0; y <= maxY; y++) {
        for (int x = 0; x <= maxX; x++) {
            vector<pair<int, int>> neighbors;
            pair<int, int> curPos = make_pair(x, y);
            char curHeight = elevationMap[curPos];
            for (const auto &item: dirs) {
                pair<int, int> nPos = make_pair(x + item.first, y + item.second);
                if (nPos.first < 0 || nPos.first > maxX || nPos.second < 0 || nPos.second > maxY) {
                    continue;
                }
                char nHeight = elevationMap[nPos];
                if (nHeight <= curHeight || nHeight - curHeight == 1) {
                    neighbors.emplace_back(nPos);
                }
            }
            nMap[curPos] = neighbors;
        }
    }
    unsigned int minP = 100000;
    for (const auto &item: startPositions) {
        predMap.clear();
        if (item.first == 5) {
            cout << "item: " << item.first << ", " << item.second << endl;
        }
        int result = bfs(nMap, item, endPos);
        if (result == -1) {
            continue;
        }
        visited.clear();
        vector<pair<int, int>> path;
        pair<int, int> crawl = endPos;
        while (predMap[crawl] != item) {
            cout << "item: " << item.first << ", " << item.second << " pred: " << predMap[crawl].first << ", " << predMap[crawl].second << " ";
            path.push_back(predMap[crawl]);
            crawl = predMap[crawl];
        }
        cout << endl;
        if (path.size() < minP) {
            minP = path.size();
        }
        cout << path.size() << endl;
    }
    cout << "min = " << minP + 1 << endl;
    return 0;
}

int main() {
    part1();
//    part2();
}