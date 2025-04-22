#include "red_black_tree.h"

#include <iostream>
#include <vector>

void RedBlackTree::insert(int value) {
  TreeNode* newNode = new TreeNode(value);

  if (!root) {
    root = newNode;
    return;
  }

  TreeNode* parent{};
  TreeNode* current{root};
  while (current) {
    parent = current;
    if (current->value > value) {
      current = current->left;
    } else if (current->value < value) {
      current = current->right;
    } else {
      return;
    }
  }

  newNode->parent = parent;
  if (parent->value > value) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }

  fixInsertion(newNode);
}

void RedBlackTree::printInorder() {
  TreeNode* current{root};
  std::vector<TreeNode*> stack{};

  while (!stack.empty() || current) {
    if (current) {
      stack.push_back(current);
      current = current->left;
    } else {
      current = stack.back();
      stack.pop_back();
      std::cout << current->value << ' ';
      current = current->right;
    }
  }

  std::cout << '\n';
}

void RedBlackTree::rotateLeft(TreeNode* node) {
  TreeNode* right = node->right;
  TreeNode* parent = node->parent;

  if (!right) return;

  if (parent) {
    if (parent->left == node) parent->left = right;
    if (parent->right == node) parent->right = right;
    right->parent = parent;
  } else {
    root = right;
    right->parent = nullptr;
  }
  node->right = right->left;
  node->right->parent = node;
  right->left = node;
  node->parent = right;
}

void RedBlackTree::rotateRight(TreeNode* node) {
  TreeNode* left = node->left;
  TreeNode* parent = node->parent;

  if (!left) return;

  if (parent) {
    if (parent->left == node) parent->left = left;
    if (parent->right == node) parent->right = left;
    left->parent = parent;
  } else {
    root = left;
    left->parent = nullptr;
  }
  node->left = left->right;
  node->left->parent = node;
  left->right = node;
  node->parent = left;
};

void RedBlackTree::fixInsertion(TreeNode* node) {
  while (node->color == red && node->parent->color == red) {
    TreeNode* parent = node->parent;
    TreeNode* grandParent = parent->parent;

    if (grandParent->left == parent) {
      TreeNode* uncle = grandParent->right;

      if (uncle->color == red) {
        grandParent->color = red;
        uncle->color = black;
        parent->color = black;
      } else {
        if (node == parent->left) {
          parent->color = black;
          grandParent->color = red;
          rotateRight(grandParent);
        } else {
          rotateLeft(parent);
        }
      }
    } else {
      TreeNode* uncle = grandParent->left;

      if (uncle->color == red) {
        grandParent->color = red;
        uncle->color = black;
        parent->color = black;
      } else {
        if (node == parent->right) {
          parent->color = black;
          grandParent->color = red;
          rotateLeft(grandParent);
        } else {
          rotateRight(parent);
        }
      }
    }
  }
};
