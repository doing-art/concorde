#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <vector>

class RedBlackTreeTest;

class RedBlackTree {
 public:
  RedBlackTree();
  void insert(int value);
  bool contains(int value);
  void remove(int value);
  std::vector<int> inorder();

  friend class RedBlackTreeTest;

 private:
  enum Color { red, black };

  struct TreeNode {
    int value{};
    Color color{};
    TreeNode* parent{};
    TreeNode* left{};
    TreeNode* right{};

    TreeNode(int newValue, Color newColor = red)
        : value{newValue}, color{newColor} {}
  };

  TreeNode* nil{};
  TreeNode* root{};
  int size{};

  void rotateLeft(TreeNode* node);
  void rotateRight(TreeNode* node);
  void fixInsertion(TreeNode* node);
  void fixRemoval(TreeNode* node);
  void transplant(TreeNode* nodeToRemove, TreeNode* node);
  TreeNode* minimum(TreeNode* node);
  TreeNode* find(int value);
};

#endif
