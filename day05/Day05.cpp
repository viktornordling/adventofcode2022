//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day05.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

void insert_at_bottom(stack<int> &s, int x)
{
    if (s.empty())
    {
        s.push(x);
        return;
    }

    int y = s.top();
    s.pop();
    insert_at_bottom(s, x);
    s.push(y);
}

void reverse_stack(stack<int> &s)
{
    if (s.empty())
        return;

    int x = s.top();
    s.pop();
    reverse_stack(s);
    insert_at_bottom(s, x);
}

void print_stack(stack<int> s)
{
    reverse_stack(s);
    stack<int> temp;

    // Reverse the stack using a temporary stack
    while (!s.empty())
    {
        temp.push(s.top());
        s.pop();
    }

    // Print the reversed stack
    while (!temp.empty())
    {
        cout << char(temp.top()) << " ";
        temp.pop();
    }
    cout << endl;
    reverse_stack(s);
}

int part_1() {
    std::ifstream infile("input.txt");
    map<int, stack<int>> stacks;
    std::string line;
    int num_stacks = 0;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        if (line.empty()) {
            break;
        }
        for (int i = 0; i < line.length(); i++) {
            if (isupper(line[i])) {
                int index = (i - 1) / 4 + 1;
                if (stacks.find(index) == stacks.end()) {
                    stacks[index] = stack<int>();
                }
                stacks[index].push(line[i]);
                if (index > num_stacks) {
                    num_stacks = index;
                }
            }
        }
    }
    for (int i = 1; i <= num_stacks; ++i) {
        reverse_stack(stacks[i]);
    }

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        string dummy;
        int num;
        int from;
        int to;
        iss >> dummy >> num >> dummy >> from >> dummy >> to;
        stack<int>& from_stack = stacks[from];
        stack<int>& to_stack = stacks[to];
        for (int i = 0; i < num; ++i) {
            int top = from_stack.top();
            to_stack.push(top);
            from_stack.pop();
        }
    }

    cout << "Part 1: ";
    for (int i = 1; i <= num_stacks; ++i) {
        cout << char(stacks[i].top()) << "";
    }
    cout << endl;
    return 0;
}

int part_2() {
    std::ifstream infile("input.txt");
    map<int, stack<int>> stacks;
    std::string line;
    int num_stacks = 0;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        if (line.empty()) {
            break;
        }
        for (int i = 0; i < line.length(); i++) {
            if (isupper(line[i])) {
                int index = (i - 1) / 4 + 1;
                if (stacks.find(index) == stacks.end()) {
                    stacks[index] = stack<int>();
                }
                stacks[index].push(line[i]);
                if (index > num_stacks) {
                    num_stacks = index;
                }
            }
        }
    }
    for (int i = 1; i <= num_stacks; ++i) {
        reverse_stack(stacks[i]);
    }

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        string dummy;
        int num;
        int from;
        int to;
        iss >> dummy >> num >> dummy >> from >> dummy >> to;
        stack<int>& from_stack = stacks[from];
        stack<int>& to_stack = stacks[to];
        stack<int> temp;
        for (int i = 0; i < num; ++i) {
            int top = from_stack.top();
            temp.push(top);
            from_stack.pop();
        }
        for (int i = 0; i < num; ++i) {
            int top = temp.top();
            temp.pop();
            to_stack.push(top);
        }
    }

    cout << "Part 2: ";
    for (int i = 1; i <= num_stacks; ++i) {
        cout << char(stacks[i].top()) << "";
    }
    cout << endl;
    return 0;
}

int main() {
    part_1();
    part_2();
}