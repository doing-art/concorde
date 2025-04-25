#include "red_black_tree.h"

void RedBlackTree::insert(int value) {
  TreeNode* newNode = new TreeNode(value);

  size++;

  if (!root) {
    root = newNode;
    fixInsertion(newNode);
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

std::vector<int> RedBlackTree::inorder() {
  TreeNode* current{root};
  std::vector<TreeNode*> stack{};
  std::vector<int> result(size);
  int i = 0;

  while (!stack.empty() || current) {
    if (current) {
      stack.push_back(current);
      current = current->left;
    } else {
      current = stack.back();
      stack.pop_back();
      result[i] = current->value;
      current = current->right;
      i++;
    }
  }

  return result;
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
  if (node->right) {
    node->right->parent = node;
  }
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
  if (node->left) {
    node->left->parent = node;
  }
  left->right = node;
  node->parent = left;
};

void RedBlackTree::fixInsertion(TreeNode* node) {
  while (node != root && node->color == red && node->parent->color == red) {
    TreeNode* parent = node->parent;
    TreeNode* grandParent = parent->parent;

    if (grandParent->left == parent) {
      TreeNode* uncle = grandParent->right;

      if (uncle && uncle->color == red) {
        grandParent->color = red;
        uncle->color = black;
        parent->color = black;
        node = grandParent;
      } else {
        if (node == parent->left) {
          parent->color = black;
          grandParent->color = red;
          rotateRight(grandParent);
        } else {
          rotateLeft(parent);
          node = parent;
        }
      }
    } else {
      TreeNode* uncle = grandParent->left;

      if (uncle && uncle->color == red) {
        grandParent->color = red;
        uncle->color = black;
        parent->color = black;
        node = grandParent;
      } else {
        if (node == parent->right) {
          parent->color = black;
          grandParent->color = red;
          rotateLeft(grandParent);
        } else {
          rotateRight(parent);
          node = parent;
        }
      }
    }
  }

  root->color = black;
};
