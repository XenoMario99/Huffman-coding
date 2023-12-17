#include "huffman.h"

#include <gtest/gtest.h>

namespace huffman {

TEST(HuffmanCodingTest, coding_ok) {
    std::unordered_map<Symbol, Frequency> map;

    map.emplace('a', 16);
    map.emplace('b', 5);
    map.emplace('c', 12);
    map.emplace('d', 17);
    map.emplace('e', 10);
    map.emplace('f', 25);

    Node* node{encode(map)};

    EXPECT_EQ(node->frequency, 85);
    EXPECT_EQ(node->left->frequency, 33);
    EXPECT_EQ(node->left->left->symbol, 'a');
    EXPECT_EQ(node->left->right->symbol, 'd');
    EXPECT_EQ(node->right->frequency, 52);
    EXPECT_EQ(node->right->left->symbol, 'f');
    EXPECT_EQ(node->right->right->frequency, 27);
    EXPECT_EQ(node->right->right->left->symbol, 'c');
    EXPECT_EQ(node->right->right->right->left->symbol, 'b');
    EXPECT_EQ(node->right->right->right->right->symbol, 'e');
}

}  // namespace huffman