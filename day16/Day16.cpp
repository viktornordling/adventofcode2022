//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day16.h"
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

class Node {
public:
    string name;
    vector<string> edges;
    int flow;
};

int dfs(map<string, Node *> nodes, Node *cur, int minutes, int flow, set<string> &visited) {
    visited.insert(cur->name);

}

int solve() {
    std::ifstream infile("easy.txt");
    string line;
    vector<string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    int sum = 0;
    map<string, Node *> nodes;
    for (int i = 0; i < lines.size(); i++) {
        string line1 = lines[i];

        std::istringstream iss(line1);
        cout << line1 << endl;
        string dummy;
        string valve;
        string flow;
        iss >> dummy >> valve >> dummy >> dummy >> flow;
        cout << "valve: " << valve << " flow: " << flow << endl;
        string valves = line1.substr(line1.find_last_of("valve") + 1);
        if (valves[0] == 's') {
            valves = valves.substr(1);
        }
        cout << "valves: " << valves << endl;

        size_t pos = 0;
        std::string token;
        string delimiter = ", ";
        vector<string> items;
        while ((pos = valves.find(delimiter)) != std::string::npos) {
            token = valves.substr(0, pos);
            std::cout << token << std::endl;
            valves.erase(0, pos + delimiter.length());
            items.push_back(token);
        }
        items.push_back(valves);
        cout << items.size() << endl;
        Node *node = new Node();
        node->name = valve;
        node->flow = stoi(flow.substr(5, flow.size() - 1));
        cout << "flow: " << node->flow << endl;
        node->edges = items;
        nodes[valve] = node;
    }
    Node *start = nodes["AA"];



    return 0;
}

int main() {
    solve();
}