#include "red_black_tree.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <set>
#include <vector>

class RedBlackTreeTest : public testing::Test {
 private:
  bool validateNode(RedBlackTree::TreeNode* node, int curBlackHeight) {
    if (node == tree.nil) {
      if (blackHeight < 0) {
        blackHeight = curBlackHeight;
      }
      return blackHeight == curBlackHeight;
    }

    if (node->color == RedBlackTree::red &&
        node->parent->color == RedBlackTree::red) {
      return false;
    }

    if (node->color == RedBlackTree::black) {
      curBlackHeight++;
    }

    return validateNode(node->left, curBlackHeight) &&
           validateNode(node->right, curBlackHeight);
  }

 public:
  RedBlackTree tree{};
  int blackHeight{-1};

  bool validate() {
    if (tree.root && tree.root->color == RedBlackTree::red) {
      return false;
    }

    return validateNode(tree.root, 0);
  }
};

TEST_F(RedBlackTreeTest, CheckInsertion) {
  std::vector<int> input{50, 30, 70, 60, 80, 90, 100, 75, 95,
                        98, 97, 10, 20, 5,  3,  25,  24};
  std::vector<int> expected{3,  5,  10, 20, 24, 25, 30, 50, 60,
                            70, 75, 80, 90, 95, 97, 98, 100};
  for (auto val : input) {
    tree.insert(val);
  }
  EXPECT_TRUE(validate());
  EXPECT_THAT(tree.inorder(), testing::ContainerEq(expected));
}

TEST_F(RedBlackTreeTest, CheckMassiveInsertion) {
  std::vector<int> expected(1001);
  for (int i = -500; i <= 500; i++) {
    tree.insert(i);
    expected[i + 500] = i;
  }
  EXPECT_TRUE(validate());
  EXPECT_THAT(tree.inorder(), testing::ContainerEq(expected));
}

TEST_F(RedBlackTreeTest, CheckContains) {
  std::vector<int> input{50, 30, 70, 60, 80, 90, 100, 75, 95,
                        98, 97, 10, 20, 5,  3,  25,  24};
  for (auto val : input) {
    tree.insert(val);
  }
  EXPECT_TRUE(tree.contains(97));
  EXPECT_TRUE(tree.contains(5));
  EXPECT_TRUE(tree.contains(24));
  EXPECT_FALSE(tree.contains(101));
  EXPECT_FALSE(tree.contains(92));
}

TEST_F(RedBlackTreeTest, CheckRemoval) {
  std::set<int> nodesToRemove{90, 50, 30, 80};
  std::vector<int> input{50, 30, 70, 60, 80, 90, 100, 75, 95,
                         98, 97, 10, 20, 5,  3,  25,  24};
  std::vector<int> expected{};

  for (auto item : input) {
    tree.insert(item);
    if (!nodesToRemove.contains(item)) {
      expected.push_back(item);
    }
  }

  std::ranges::sort(expected);

  for (auto item : nodesToRemove) {
    tree.remove(item);
  }

  EXPECT_TRUE(validate());
  EXPECT_THAT(tree.inorder(), testing::ContainerEq(expected));

  for (auto item : nodesToRemove) {
    EXPECT_FALSE(tree.contains(item));
  }
}

TEST_F(RedBlackTreeTest, CheckMassiveRemoval) {
  std::set<int> nodesToRemove{500, 200, 0, 1, 3, -5};
  std::vector<int> expected{};
  for (int i = -500; i <= 500; i++) {
    tree.insert(i);
    if (!nodesToRemove.contains(i)) {
      expected.push_back(i);
    }
  }
  for (auto item : nodesToRemove) {
    tree.remove(item);
  }
  EXPECT_TRUE(validate());
  EXPECT_THAT(tree.inorder(), testing::ContainerEq(expected));
}
