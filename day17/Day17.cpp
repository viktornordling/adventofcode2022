//
// Created by Viktor Nordling on 12/1/22.
//

#include "Day17.h"
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

class Piece {
public:
    set<pair<int, int>> blocks;
    void move_down() {
//        cout << "moving down" << endl;
        set<pair<int, int>> new_blocks;
        for (const auto &block : blocks) {
            new_blocks.insert(make_pair(block.first, block.second - 1));
        }
        blocks = new_blocks;
    }

    void move_left() {
        set<pair<int, int>> new_blocks;
        for (const auto &block : blocks) {
            new_blocks.insert(make_pair(block.first - 1, block.second ));
        }
        blocks = new_blocks;
    }

    void move_right() {
        set<pair<int, int>> new_blocks;
        for (const auto &block : blocks) {
            new_blocks.insert(make_pair(block.first + 1, block.second ));
        }
        blocks = new_blocks;
    }

};

Piece add_piece(int piece_id, map<pair<int, int>, char> &world, int maxY) {
    piece_id = piece_id % 5;
    set<pair<int, int>> new_piece;
    int bottomEdge = 0;
    if (maxY == -1) {
        bottomEdge = 3;
    } else {
        bottomEdge = maxY + 4;
    }
    if (piece_id == 0) {
        // - piece
        new_piece.insert(make_pair(2, bottomEdge));
        new_piece.insert(make_pair(3, bottomEdge));
        new_piece.insert(make_pair(4, bottomEdge));
        new_piece.insert(make_pair(5, bottomEdge));
    } else if (piece_id == 1) {
        // plus piece
        new_piece.insert(make_pair(3, bottomEdge));
        new_piece.insert(make_pair(2, bottomEdge + 1));
        new_piece.insert(make_pair(3, bottomEdge + 1));
        new_piece.insert(make_pair(4, bottomEdge + 1));
        new_piece.insert(make_pair(3, bottomEdge + 2));
    } else if (piece_id == 2) {
        // ⅃ piece
        new_piece.insert(make_pair(2, bottomEdge));
        new_piece.insert(make_pair(3, bottomEdge));
        new_piece.insert(make_pair(4, bottomEdge));
        new_piece.insert(make_pair(4, bottomEdge + 1));
        new_piece.insert(make_pair(4, bottomEdge + 2));
    } else if (piece_id == 3) {
        // | piece
        new_piece.insert(make_pair(2, bottomEdge));
        new_piece.insert(make_pair(2, bottomEdge + 1));
        new_piece.insert(make_pair(2, bottomEdge + 2));
        new_piece.insert(make_pair(2, bottomEdge + 3));
    } else if (piece_id == 4) {
        // o piece
        new_piece.insert(make_pair(2, bottomEdge));
        new_piece.insert(make_pair(3, bottomEdge));
        new_piece.insert(make_pair(2, bottomEdge + 1));
        new_piece.insert(make_pair(3, bottomEdge + 1));
    }
    Piece piece;
    piece.blocks = new_piece;
    return piece;
}

bool can_drop(map<pair<int, int>, char> world, Piece &piece) {
    for (const auto& p : piece.blocks) {
        if ((world.find(make_pair(p.first, p.second - 1)) != world.end() && world[make_pair(p.first, p.second - 1)] != 0) || p.second == 0) {
//            cout << "Stuff: " << world[make_pair(p.first, p.second - 1)] << endl;
//            cout << "cannot drop" << endl;
            return false;
        }
    }
//    cout << "can drop" << endl;
    return true;
}

bool can_move_right(map<pair<int, int>, char> world, Piece &piece) {
    for (const auto& p : piece.blocks) {
        if ((world.find(make_pair(p.first + 1, p.second)) != world.end() && world[make_pair(p.first + 1, p.second)] != 0) || p.first == 6) {
//            cout << "cannot move right" << endl;
            return false;
        }
    }
//    cout << "can move right" << endl;
    return true;
}

bool can_move_left(map<pair<int, int>, char> world, Piece &piece) {
    for (const auto& p : piece.blocks) {
        if ((world.find(make_pair(p.first - 1, p.second)) != world.end() && world[make_pair(p.first - 1, p.second)] != 0) || p.first == 0) {
            return false;
        }
    }
    return true;
}

void print_world(map<pair<int, int>, char> &world, int maxY, Piece &piece) {
    for (int y = maxY; y >= 0; y--) {
        cout << '|';
        for (int x = 0; x < 7; x++) {
            char c = world[make_pair(x, y)];
            if (c == 0) {
                c = '.';
            }
            if (piece.blocks.find(make_pair(x, y)) != piece.blocks.end()) {
                c = '@';
            }
            cout << c;
        }
        cout << '|';
        cout << endl;
    }
}

void drop_piece(map<pair<int, int>, char> &world, Piece &piece, int &flowId, string &flows) {
    cout << "dropping piece" << endl;
    bool keep_falling = true;
    while (keep_falling) {
//        print_world(world, 27, piece);
        char flow = flows[flowId % flows.size()];
//        cout << "flowId = " << flowId << " flow = " << flows[flowId % flows.size()] << endl;
        flowId++;
//        cout << "flowId: " << flowId << endl;
        if (flow == '>' && can_move_right(world, piece)) {
//            cout << "moving right" << endl;
            piece.move_right();
        } else if (flow == '<' && can_move_left(world, piece)) {
//            cout << "moving left" << endl;
            piece.move_left();
        }
        if (can_drop(world, piece)) {
            piece.move_down();
        } else {
            keep_falling = false;
        }
    }
//    char flow = flows[flowId % flows.size()];
//    flowId++;
//    if (flow == '>' && can_move_right(world, piece)) {
//        cout << "moving right" << endl;
//        piece.move_right();
//    } else if (can_move_left(world, piece)) {
//        cout << "moving left" << endl;
//        piece.move_left();
//    }
}


int solve() {
    std::ifstream infile("input.txt");
    string flows;
    infile >> flows;
    cout << "line: " << flows << endl;

    map<pair<int, int>, char> world;
    int piece_id = 0;
    int maxY = -1;
    int flowId = 0;
    for (int i = 0; i < 2022; i++) {
        cout << "i = " << i << endl;
        Piece new_piece = add_piece(piece_id++, world, maxY);
        drop_piece(world, new_piece, flowId, flows);
        Piece piece;
        for (const auto &block : new_piece.blocks) {
            int pid = (piece_id - 1) % 5;
            world[block] = '0' + pid;
            maxY = max(maxY, block.second);
        }
//        print_world(world, maxY + 3, piece);
//        cout << "maxY: " << maxY << endl;
    }
    cout << "Part 1: " << maxY + 1 << endl;

    return 0;
}

int main() {
    solve();
}