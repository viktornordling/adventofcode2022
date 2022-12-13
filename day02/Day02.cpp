//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day02.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int win(string me, string you) {
    if (me == "A") {
        if (you == "X") {
            return 3;
        }
        if (you == "Y") {
            return 6;
        }
        if (you == "Z") {
            return 0;
        }
    }
    if (me == "B") {
        if (you == "X") {
            return 0;
        }
        if (you == "Y") {
            return 3;
        }
        if (you == "Z") {
            return 6;
        }
    }
    if (me == "C") {
        if (you == "X") {
            return 6;
        }
        if (you == "Y") {
            return 0;
        }
        if (you == "Z") {
            return 3;
        }
    }
}

char get_shape(string me, string result) {
    if (me == "A") {
        if (result == "X") {
            return 'Z';
        }
        if (result == "Y") {
            return 'X';
        }
        if (result == "Z") {
            return 'Y';
        }
    }
    if (me == "B") {
        if (result == "X") {
            return 'X';
        }
        if (result == "Y") {
            return 'Y';
        }
        if (result == "Z") {
            return 'Z';
        }
    }
    if (me == "C") {
        if (result == "X") {
            return 'Y';
        }
        if (result == "Y") {
            return 'Z';
        }
        if (result == "Z") {
            return 'X';
        }
    }
}


int point(string me) {
    return me[0] - 'W';
}

int main() {
    std::ifstream infile("input.txt");
    std::string line;
    int sum = 0;
    int sum2 = 0;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        cout << line << endl;
        string you, me;
        istringstream ss(line);
        ss >> you >> me;
//        cout << "me: " << me << " you: " << you << endl;
        cout << win(you, me) << " " << point(me) << endl;
        sum += win(you, me) + point(me);
        char shape = get_shape(you, me);
        sum2 += win(you, string(1, shape));
        sum2 += point(string(1, shape));
    }
    cout << "Part 1: " << sum << endl;
    cout << "Part 2: " << sum2 << endl;
    return 0;
}