#include "priority_queue.h"

#include <gtest/gtest.h>

#include <queue>

namespace queue {

class PriorityQueueTest : public ::testing::Test {
   protected:
    PriorityQueue<int, std::vector<int>, std::greater<int>> queue;
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

    bool checkHeapProperty() const {
        auto reference{queue};
        while (!reference.empty()) {
            const auto top{reference.top()};
            reference.pop();

            if (!reference.empty()) {
                const auto leftLeaf{reference.top()};
                reference.pop();

                if (std::greater<int>{}(top, leftLeaf)) return false;
            }

            if (!reference.empty()) {
                const auto rightLeaf{reference.top()};
                reference.pop();

                if (std::greater<int>{}(top, rightLeaf)) return false;
            }
        }

        return true;
    }
};

TEST_F(PriorityQueueTest, buildHeap_ok) {
    queue.buildHeap(arr);
    EXPECT_TRUE(checkHeapProperty());
}

TEST_F(PriorityQueueTest, pop_ok) {
    queue.buildHeap(arr);
    const auto size{queue.size()};
    const int popNum{3};
    for (int i = 0; i < popNum; i++) {
        queue.pop();
    }
    EXPECT_TRUE(checkHeapProperty());
    EXPECT_EQ(size, queue.size() + popNum);
}

TEST_F(PriorityQueueTest, top_and_pop_ok) {
    queue.buildHeap(arr);

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

    for (int i = 0; i < size; i++) {
        const auto queueTop{queue.top()};
        const auto refQueueTop{refQueue.top()};
        EXPECT_EQ(queueTop, refQueueTop);
        queue.pop();
        refQueue.pop();
    }

    EXPECT_EQ(queue.size(), refQueue.size());
}

TEST_F(PriorityQueueTest, eraseWhenGivenIndex_ok) {
    queue.buildHeap(arr);
    const auto& element{arr.front()};
    auto selected{queue.erase(element)};
    EXPECT_TRUE(std::find(arr.begin(), arr.end(), selected) != arr.end());
}

TEST_F(PriorityQueueTest, eraseWhenGivenIndex_Nok) {
    queue.buildHeap(arr);
    const auto& element{*std::max_element(arr.begin(), arr.end()) + 1};
    EXPECT_THROW(queue.erase(element), std::out_of_range);
}

}  // namespace queue