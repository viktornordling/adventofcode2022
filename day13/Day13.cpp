//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day13.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Expr {
public:
    vector<Expr *> exprs;
    bool isList = true;
    int val = -1;
};

//class ScalarExpr: public Expr {
//public:
//    int val{};
//};

Expr parse(string line) {
    stack<Expr *> exprStack;
    Expr *curExp = nullptr;

    istringstream iss(line);
    while (iss.peek() != -1) {
        int next = iss.peek();
//        cout << "next " << char(next) << endl;
        if (next == '[') {
            if (curExp != nullptr) {
                exprStack.push(curExp);
            }
            curExp = new Expr();
            iss.get();
        } else if (next == ']') {
            Expr *tmp = curExp;
            if (!exprStack.empty()) {
                curExp = exprStack.top();
                exprStack.pop();
                curExp->exprs.push_back(tmp);
            }
            iss.get();
        } else if (next == ',') {
            iss.get();
        } else {
            int num;
            iss >> num;
            auto *scalarExpr = new Expr();
            scalarExpr->val = num;
            scalarExpr->isList = false;
            curExp->exprs.push_back(scalarExpr);
        }
    }
    return std::move(*curExp);
}

int valid(Expr left, Expr right) {
    if (left.isList && right.isList) {
        for (int i = 0; i < left.exprs.size(); i++) {
            if (i >= right.exprs.size()) {
                return -1;
            }
            int result = valid(*left.exprs[i], *right.exprs[i]);
            if (result != 0) {
                return result;
            }
        }
        if (left.exprs.size() < right.exprs.size()) {
            return 1;
        } else {
            return 0;
        }
    } else if (left.isList && right.val > -1) {
        Expr newRight = Expr();
        newRight.exprs.push_back(&right);
        return valid(left, newRight);
    } else if (left.val > -1 && right.isList) {
        Expr newLeft = Expr();
        newLeft.exprs.push_back(&left);
        return valid(newLeft, right);
    } else {
        if (left.val < right.val) {
            return 1;
        } else if (left.val > right.val) {
            return -1;
        } else {
            return 0;
        }
    }
}

struct less_than_key
{
    inline bool operator() (const Expr& struct1, const Expr& struct2)
    {
        int result = valid(struct1, struct2);
        return (result == 1);
    }
};

int part1() {
    std::ifstream infile("input.txt");
    string line;
    vector<string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    int pair = 1;
    int sum = 0;
    vector<Expr> exprs;
    for (int i = 0; i < lines.size(); i++) {
        string line1 = lines[i++];
        string line2 = lines[i++];

        cout << "line1: " << line1 << endl;
        cout << "line2: " << line2 << endl;

        Expr expr1 = parse(line1);
        Expr expr2 = parse(line2);
        exprs.push_back(expr1);
        exprs.push_back(expr2);

        int check = valid(expr1, expr2);
        if (check == 1) {
            sum += pair;
        } else if (check == 0) {
            cout << "BAAAAD" << endl;
        }
        cout << "pair " << pair << " " << check << endl;
        pair++;
    }

    cout << "Part 1: " << sum << endl;
    sort(exprs.begin(), exprs.end(), less_than_key());
    int twoMark = 0;
    int sixMark = 0;
    for (int i = 0; i < exprs.size(); i++) {
        if (exprs[i].exprs.size() == 1 && exprs[i].exprs[0]->exprs.size() == 1 && exprs[i].exprs[0]->exprs[0]->val == 2) {
            cout << "TWO MARK!" << endl;
            twoMark = i + 1;
        }
        if (exprs[i].exprs.size() == 1 && exprs[i].exprs[0]->exprs.size() == 1 && exprs[i].exprs[0]->exprs[0]->val == 6) {
            cout << "SIX MARK!" << endl;
            sixMark = i + 1;
        }
    }
    cout << "Part 2: " << twoMark * sixMark << endl;
    return 0;
}

int main() {
    part1();
//    part2();
}