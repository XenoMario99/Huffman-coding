#include "priority_queue.h"

#include <gtest/gtest.h>

#include <queue>

namespace queue {

class PriorityQueueTest : public ::testing::Test {
   protected:
    PriorityQueue<int> queue;
    std::priority_queue<int, std::vector<int>, std::greater<int>> refQueue;
    std::vector<int> arr{12, 11, 13, 5, 6, 7, 19, 1, 41, 3, 8, 7};
    int size;

    void SetUp() override {
        for (const auto& elem : arr) {
            refQueue.push(elem);
        }
        size = arr.size();
    };
    void TearDown() override{};

    bool checkMinHeapProperty() const {
        auto refQueue{queue};
        while (!refQueue.empty()) {
            const auto top{refQueue.top()};
            refQueue.pop();

            if (!refQueue.empty()) {
                const auto leftLeaf{refQueue.top()};
                refQueue.pop();

                if (top > leftLeaf) return false;
            }

            if (!refQueue.empty()) {
                const auto rightLeaf{refQueue.top()};
                refQueue.pop();

                if (top > rightLeaf) return false;
            }
        }

        return true;
    }
};

TEST_F(PriorityQueueTest, buildHeap_ok) {
    queue.buildHeap(arr);
    EXPECT_TRUE(checkMinHeapProperty());
}

TEST_F(PriorityQueueTest, pop_ok) {
    queue.buildHeap(arr);
    const auto size{queue.size()};
    const int popNum{3};
    for (int i = 0; i < popNum; i++) {
        queue.pop();
    }
    EXPECT_TRUE(checkMinHeapProperty());
    EXPECT_EQ(size, queue.size() + popNum);
}

TEST_F(PriorityQueueTest, top_and_pop_ok) {
    queue.buildHeap(arr);

    queue.print();

    for (int i = 0; i < size; i++) {
        const auto queueTop{queue.top()};
        const auto refQueueTop{refQueue.top()};
        EXPECT_EQ(queueTop, refQueueTop);
        queue.pop();
        refQueue.pop();
    }

    EXPECT_EQ(queue.size(), refQueue.size());
}

TEST_F(PriorityQueueTest, push_ok) {
    for (const auto& elem : arr) {
        queue.push(elem);
    }

    queue.print();

    for (int i = 0; i < size; i++) {
        const auto queueTop{queue.top()};
        const auto refQueueTop{refQueue.top()};
        EXPECT_EQ(queueTop, refQueueTop);
        queue.pop();
        refQueue.pop();
    }

    EXPECT_EQ(queue.size(), refQueue.size());
}

}  // namespace queue