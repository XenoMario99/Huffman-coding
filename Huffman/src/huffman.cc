#include "huffman.h"

#include "priority_queue.h"

namespace huffman {

struct {
    bool operator()(Node* lhs, Node* rhs) { return lhs->frequency > rhs->frequency; }
} cmp;

Node* encode(const std::unordered_map<Symbol, Frequency>& symbols) {
    queue::PriorityQueue<Node*, std::vector<Node*>, decltype(cmp)> queue;

    for (auto ptr{symbols.begin()}; ptr != symbols.end(); ptr++) {
        Node* node = new Node(ptr->first, ptr->second);
        queue.push(node);
    }

    int32_t size{queue.size()};
    int32_t i{0};
    Node* result{nullptr};
    while (i < size - 1) {  // Solution is obtained when i = size - 1
        Node* p{queue.top()};
        queue.pop();
        Node* q{queue.top()};
        queue.pop();

        result = new Node(' ', p->frequency + q->frequency);
        result->left = p;
        result->right = q;
        queue.push(result);
        i++;
    }

    return queue.erase(result);
}

}  // namespace huffman