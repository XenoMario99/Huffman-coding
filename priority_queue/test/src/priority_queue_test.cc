#include "priority_queue.h"

#include <gtest/gtest.h>

namespace queue {

class PriorityQueueTest : public ::testing::Test {
   protected:
    PriorityQueue<int> queue;

    void SetUp() override{};
    void TearDown() override{};

    bool checkMaxHeapProperty() const {
        auto refQueue{queue};
        while (!refQueue.empty()) {
            const auto& top{refQueue.top()};
            refQueue.pop();

            if (!refQueue.empty()) {
                const auto& leftLeaf{refQueue.top()};
                refQueue.pop();

                if (top < leftLeaf) return false;
            }

            if (!refQueue.empty()) {
                const auto& rightLeaf{refQueue.top()};
                refQueue.pop();

                if (top < rightLeaf) return false;
            }
        }

        return true;
    }
};

TEST_F(PriorityQueueTest, test1) {
    std::vector<int> arr{12, 11, 13, 5, 6, 7, 19, 1, 41, 3, 8, 7};
    queue.buildHeap(arr);
    EXPECT_TRUE(checkMaxHeapProperty());
}

}  // namespace queue