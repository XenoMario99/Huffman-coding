#include "huffman.h"

#include "priority_queue.h"

namespace huffman {

Node* encode(const std::unordered_map<Symbol, Frequency>& symbols) {
    Node* node{nullptr};

    queue::PriorityQueue<Node> queue;

    for (auto ptr{symbols.begin()}; ptr != symbols.end(); ptr++) {
        queue.push(Node(ptr->first, ptr->second));
    }

    queue.print();

    return node;
}

}  // namespace huffman