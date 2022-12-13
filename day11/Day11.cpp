//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day11.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>


using namespace std;
using namespace boost::multiprecision;

int MAX_DIVISIBLE = 1;

class Operator {
public:
    virtual long apply(const long& item) = 0;
};

class PlusOperator: public Operator {
public:
    explicit PlusOperator(int operand) : operand(operand) {}

private:
    const long operand;

    long apply(const long &item) {
//        return (item + operand);
        return (item + operand) % MAX_DIVISIBLE;
    }
};

class MulOperator: public Operator {
public:
    explicit MulOperator(int operand) : operand(operand) {}

private:
    int operand;
    long apply(const long &item) {
//        return (item * operand);
        return (item * operand) % MAX_DIVISIBLE;
    }
};

class SelfOperator: public Operator {
    long apply(const long &item) {
//        return (item * item);
        return (item * item) % MAX_DIVISIBLE;
    }
};


class Monkey {
public:
     vector<long> items;
     Operator *monkeyOperator;
     int test;
     int trueM;
     int falseM;
};

int part1() {
    std::ifstream infile("input.txt");
    std::string line;
    vector<string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    int lineNumber = 0;
    int monkeyNo = 0;
    vector<Monkey*> monkeys;
    while (lineNumber < lines.size()) {
        lineNumber++; // skip
        line = lines[lineNumber];
        line = line.substr(18, line.size());
        size_t pos = 0;
        std::string token;
        string delimiter = ", ";
        vector<long> items;
        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            std::cout << token << std::endl;
            line.erase(0, pos + delimiter.length());
            items.push_back(stoi(token));
        }
        items.push_back(stoi(line));
        // Operation: new = old * 19
        lineNumber++;
        line = lines[lineNumber];
        Operator *monkOp = nullptr;
        if (line.find('*') != string::npos) {
            if (line.substr(line.length() - 3) == "old") {
                monkOp = new SelfOperator();
            } else {
                string operand = line.substr(line.find_last_of(' '));
                monkOp = new MulOperator(stoi(operand));
            }
        } else {
            string operand = line.substr(line.find_last_of(' '));
            monkOp = new PlusOperator(stoi(operand));
        }
        lineNumber++;
        line = lines[lineNumber];
        int divM = stoi(line.substr(line.find_last_of(' ')));
        MAX_DIVISIBLE *= divM;
        lineNumber++;
        line = lines[lineNumber];
        int trueM = stoi(line.substr(line.find_last_of(' ')));
        lineNumber++;
        line = lines[lineNumber];
        int falseM = stoi(line.substr(line.find_last_of(' ')));
        lineNumber += 2;
        auto *monkey = new Monkey();
        monkey->falseM = falseM;
        monkey->trueM = trueM;
        monkey->items = items;
        monkey->monkeyOperator = monkOp;
        monkey->test = divM;
        monkeys.push_back(monkey);
        monkeyNo++;
    }
    cout << "bla" << endl;
    long monkeyInspections[6];
    for (int i = 0; i < 6; i++) {
        monkeyInspections[i] = 0;
    }
    for (int round = 0; round < 10000; round++) {
        int monkeyIndex = 0;
        for (const auto &monkey: monkeys) {
            for (const auto &item: monkey->items) {
                monkeyInspections[monkeyIndex]++;
                long newWorry = monkey->monkeyOperator->apply(item);
//                cout << "new worry: " << newWorry << endl;
//                newWorry /= 3;
                if (newWorry % monkey->test == 0) {
                    monkeys[monkey->trueM]->items.push_back(newWorry);
                } else {
                    monkeys[monkey->falseM]->items.push_back(newWorry);
                }
            }
            monkeyIndex++;
            monkey->items.clear();
        }
        if (round == 999) {
            cout << "bbbbb" << endl;
        }
        cout << "Round: " << round << endl;
    }
    int n = sizeof(monkeyInspections) / sizeof(monkeyInspections[0]);
    sort(monkeyInspections, monkeyInspections + n);
    cout << monkeyInspections[4] * monkeyInspections[5];

    cpp_int a = 1;
    cpp_int b = 2;
    cpp_int c = a + b;

    return 0;
}

int main() {
    part1();
//    part2();
}