#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <vector>

class RedBlackTreeTest;

class RedBlackTree {
 public:
  RedBlackTree();
  void insert(int key);
  bool contains(int key);
  void remove(int key);
  std::vector<int> inorder();

  friend class RedBlackTreeTest;

 private:
  enum Color { red, black };

  struct TreeNode {
    int key{};
    Color color{};
    TreeNode* parent{};
    TreeNode* left{};
    TreeNode* right{};

    TreeNode(int newkey, Color newColor = red)
        : key{newkey}, color{newColor} {}
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
  TreeNode* find(int key);
};

#endif
