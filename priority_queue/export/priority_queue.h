#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

using std::vector;

namespace queue {

const unsigned int MAX_HEAP_SIZE{50};
typedef int Index;

template <typename T, typename Container = vector<T>,
          typename Compare = std::less<typename Container::value_type>>
class PriorityQueue {
   private:
    Container arr;
    Compare comp;
    unsigned int maxSize;

   public:
    PriorityQueue() : arr(Container()), comp(Compare()), maxSize(MAX_HEAP_SIZE) {}
    explicit PriorityQueue(const Container& arr);
    PriorityQueue(const PriorityQueue&) = default;
    PriorityQueue(PriorityQueue&&) = default;
    PriorityQueue& operator=(const PriorityQueue&) = default;
    PriorityQueue& operator=(PriorityQueue&&) = default;

    ~PriorityQueue();

   private:
    void heapifyUp(Index& index);
    void heapifyDown(const Index& index);

   public:
    void buildHeap(const Container& inputArr);
    void push(const T& item);
    void pop();
    const T& top() const;
    int size() const { return arr.size(); };
    bool empty() const { return arr.empty(); };

    void print() const;
};

template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::PriorityQueue(const Container& inputArr) {
    buildHeap(arr);
}

template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::~PriorityQueue() {}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::heapifyUp(Index& index) {
    Index parentId{(index - 1) / 2};
    int i{index};
    while (index != 0 && comp(arr.at(parentId), arr.at(index))) {
        std::swap(arr.at(parentId), arr.at(index));
        index = parentId;
        parentId = (index - 1) / 2;
    }
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::heapifyDown(const Index& index) {
    Index largest{index};
    const auto left{2 * index + 1};   // left child of the node at given index
    const auto right{2 * index + 2};  // right child of the node at given index

    if (left < arr.size() && comp(arr.at(largest), arr.at(left))) {
        largest = left;
    }

    if (right < arr.size() && comp(arr.at(largest), arr.at(right))) {
        largest = right;
    }

    if (index != largest) {
        std::swap(arr.at(index), arr.at(largest));
        heapifyDown(largest);
    }
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::buildHeap(const Container& inputArr) {
    arr = std::move(inputArr);
    for (Index index{static_cast<Index>(arr.size() / 2 - 1)}; index >= 0; index--) {
        heapifyDown(index);
    }
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::push(const T& item) {
    if (arr.size() < maxSize) {
        arr.push_back(item);
        Index newItemId{static_cast<int>(arr.size() - 1)};
        heapifyUp(newItemId);
    } else {
        std::cout << "There is no left space in the queue" << std::endl;
    }
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::pop() {
    if (!arr.empty()) {
        std::swap(arr.front(), arr.back());
        arr.pop_back();
        heapifyDown(0);
    } else {
        std::cerr << "Queue is empty! cannot pop" << std::endl;
        return;
    }
}

template <typename T, typename Container, typename Compare>
const T& PriorityQueue<T, Container, Compare>::top() const {
    if (!arr.empty()) {
        return arr.front();
    } else {
        throw std::runtime_error("Queue is empty! cannot access top.");
    }
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::print() const {
    std::cout << "Arr:" << std::endl;
    for (auto x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

}  // namespace  queue
