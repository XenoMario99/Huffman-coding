#pragma once

#include <iostream>
#include <unordered_map>

namespace huffman {

typedef char Symbol;
typedef int Frequency;

struct Node {
    Symbol symbol;
    Frequency frequency;
    Node* left;
    Node* right;

    Node() : symbol(' '), frequency(0), left(nullptr), right(nullptr) {}
    Node(const Symbol& sym, const Frequency& freq) : symbol(sym), frequency(freq), left(nullptr), right(nullptr) {}
    ~Node() {}

    friend bool operator<(const Node& lhs, const Node& rhs) {
        return lhs.frequency > rhs.frequency;
    }
    friend bool operator>(const Node& lhs, const Node& rhs) {
        return lhs.frequency < rhs.frequency;
    }

    friend std::ostream& operator<<(std::ostream& os, const Node& node) {
        os << node.symbol << "|" << node.frequency << std::endl;
        return os;
    }
};

Node* encode(const std::unordered_map<Symbol, Frequency>& symbols);

}  // namespace huffman
