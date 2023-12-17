#pragma once

#include <iostream>
#include <unordered_map>

namespace huffman {

typedef char Symbol;
typedef int32_t Frequency;

struct Node {
    Symbol symbol;
    Frequency frequency;
    Node* left;
    Node* right;

    Node() : symbol(' '), frequency(0), left(nullptr), right(nullptr) {}
    Node(const Symbol& sym, const Frequency& freq) : symbol(sym), frequency(freq), left(nullptr), right(nullptr) {}
    ~Node() {}
};

Node* encode(const std::unordered_map<Symbol, Frequency>& symbols);

}  // namespace huffman
