//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day07.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

class File {
    public:
        string name;
        int size = 0;
};

class Dir {
    public:
        Dir *parent;
        string dirname;
        map<string, Dir*> dirs;
        vector<File> files;
};

long calcSizes(const Dir* dir, vector<long>& sizes) {
    long fileSizes = 0;
    for (const auto &item: dir->files) {
        fileSizes += item.size;
    }
    for (const auto &item: dir->dirs) {
        fileSizes += calcSizes(item.second, sizes);
    }
//    if (fileSizes <= 100000) {
        sizes.push_back(fileSizes);
//    }
    return fileSizes;
}

int part1() {
    std::ifstream infile("input.txt");
    std::string line;
    Dir *curDir = nullptr;
    map<string, Dir *> dirs;
    vector<string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    int lineNumber = 0;
    while (lineNumber < lines.size()) {
        line = lines[lineNumber++];
        istringstream iss(line);
        cout << line << endl;
        if (line[0] == '$') {
            string dummy;
            string command;
            iss >> dummy >> command;
            if (command == "cd") {
                string dirname;
                iss >> dirname;
                if (dirname == "/") {
                    Dir *newDir = new Dir;
                    newDir->dirname = dirname;
                    curDir = newDir;
                }
                if (dirname == "..") {
                    curDir = curDir->parent;
                } else {
                    for (const auto &item: curDir->dirs) {
                        if (item.second->dirname == dirname) {
                            curDir = item.second;
                            break;
                        }
                    }
                }
                dirs[dirname] = curDir;
            } else {
                while (lineNumber < lines.size() && lines[lineNumber][0] != '$') {
                    cout << "gg " << lines[lineNumber] << endl;
                    istringstream iss2(lines[lineNumber]);
                    string first;
                    string fileName;
                    iss2 >> first;
                    iss2 >> fileName;
                    if (first == "dir") {
                        Dir *dir = new Dir;
                        dir->parent = curDir;
                        dir->dirname = fileName;
                        curDir->dirs[fileName] = dir;
                    } else {
                        File file;
                        file.size = stoi(first);
                        file.name = fileName;
                        curDir->files.push_back(file);
                    }
                    lineNumber++;
                }
            }
        }
    }
    vector<long> sizes;
    long slash = calcSizes(dirs["/"], sizes);
    long sum = 0;
    for (const auto &item: sizes) {
        sum += item;
    }
    long unused = 70000000 - slash;
    long needed = 30000000 - unused;
    cout << "needed: " << needed << endl;
    sort(sizes.begin(), sizes.end());
    cout << "Part 1: " << sum << endl;
    for (const auto &item: sizes) {
        if (item >= needed) {
            cout << "Part 2: " << item << endl;
            return 0;
        }
    }
    return 0;
}

int part2() {
    std::ifstream infile("input.txt");
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        cout << line << endl;
    }
    return 0;
}

int main() {
    part1();
//    part2();
}