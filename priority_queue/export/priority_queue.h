#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

using std::vector;

namespace queue {

const unsigned int MAX_HEAP_SIZE{50};
typedef int Index;

template <typename T>
class PriorityQueue {
   private:
    std::vector<T> arr;
    unsigned int maxSize;

   public:
    PriorityQueue() : maxSize(MAX_HEAP_SIZE) {}
    explicit PriorityQueue(const std::vector<T>& arr);
    PriorityQueue(const PriorityQueue&) = default;
    PriorityQueue(PriorityQueue&&) = default;
    PriorityQueue& operator=(const PriorityQueue&) = default;
    PriorityQueue& operator=(PriorityQueue&&) = default;

    ~PriorityQueue();

   private:
    void heapifyUp(Index& index);
    void heapifyDown(const Index& index);

   public:
    void buildHeap(const std::vector<T>& inputArr);
    void push(const T& item);
    void pop();
    const T& top() const;
    int size() const { return arr.size(); };
    bool empty() const { return arr.empty(); };
};

template <typename T>
PriorityQueue<T>::PriorityQueue(const std::vector<T>& arr) {
    buildHeap(arr);
}

template <typename T>
PriorityQueue<T>::~PriorityQueue() {}

template <typename T>
void PriorityQueue<T>::heapifyUp(Index& index) {
    Index parentId{arr.size() % 2 == 0 ? (index - 2) / 2 : (index - 1) / 2};  // Finding parent node id depending on whether new leaf is left or right
    int i{index};
    while (index != 0 || arr.at(parentId) < arr.at(index)) {
        std::swap(arr.at(parentId), arr.at(index));
        index = parentId;
        parentId = arr.size() % 2 == 0 ? (index - 2) / 2 : (index - 1) / 2;
    }
}

template <typename T>
void PriorityQueue<T>::heapifyDown(const Index& index) {
    Index largest{index};
    const auto left{2 * index + 1};   // left child of the node at given index
    const auto right{2 * index + 2};  // right child of the node at given index

    if (left < arr.size() && arr.at(left) > arr.at(largest)) {
        largest = left;
    }

    if (right < arr.size() && arr.at(right) > arr.at(largest)) {
        largest = right;
    }

    if (index != largest) {
        std::swap(arr.at(index), arr.at(largest));
        heapifyDown(largest);
    }
}

template <typename T>
void PriorityQueue<T>::buildHeap(const std::vector<T>& inputArr) {
    arr = std::move(inputArr);

    for (Index index{static_cast<Index>(arr.size() / 2 - 1)}; index >= 0; index--) {
        heapifyDown(index);
    }
}

template <typename T>
void PriorityQueue<T>::push(const T& item) {
    if (arr.size() < maxSize) {
        arr.push_back(item);
        Index newItemId{arr.size() - 1};
        heapifyUp(newItemId);
    } else {
        std::cout << "There is no left space in the queue" << std::endl;
    }
}

template <typename T>
void PriorityQueue<T>::pop() {
    if (!arr.empty()) {
        std::swap(arr.front(), arr.back());
        arr.pop_back();
        heapifyDown(0);
    } else {
        std::cerr << "Queue is empty! cannot pop" << std::endl;
        return;
    }
}

template <typename T>
const T& PriorityQueue<T>::top() const {
    if (!arr.empty()) {
        return arr.front();
    } else {
        throw std::runtime_error("Queue is empty! cannot access top.");
    }
}

}  // namespace  queue
