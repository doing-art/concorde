#include "red_black_tree.h"

RedBlackTree::RedBlackTree() {
  nil = new TreeNode(0, black);
  nil->left = nil;
  nil->right = nil;
  root = nil;
}

void RedBlackTree::insert(int key) {
  TreeNode* newNode = new TreeNode(key);
  TreeNode* parent{};
  TreeNode* current{root};
  newNode->left = nil;
  newNode->right = nil;

  size++;

  while (current != nil) {
    parent = current;
    if (current->key > key) {
      current = current->left;
    } else if (current->key < key) {
      current = current->right;
    } else {
      return;
    }
  }

  newNode->parent = parent;
  if (parent == nullptr) {
    root = newNode;
  } else if (parent->key > key) {
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

  while (!stack.empty() || current != nil) {
    if (current != nil) {
      stack.push_back(current);
      current = current->left;
    } else {
      current = stack.back();
      stack.pop_back();
      result[i] = current->key;
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

  if (parent != nullptr) {
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

  if (parent != nullptr) {
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
  while (node != root && node->color == red && node->parent->color == red) {
    if (node->parent->parent->left == node->parent) {
      TreeNode* uncle = node->parent->parent->right;

      if (uncle->color == red) {
        node->parent->parent->color = red;
        uncle->color = black;
        node->parent->color = black;
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
          node = node->parent;
          rotateLeft(node);
        }
        node->parent->color = black;
        node->parent->parent->color = red;
        rotateRight(node->parent->parent);
      }
    } else {
      TreeNode* uncle = node->parent->parent->left;

      if (uncle->color == red) {
        node->parent->parent->color = red;
        uncle->color = black;
        node->parent->color = black;
        node = node->parent->parent;
      } else {
        if (node == node->parent->left) {
          node = node->parent;
          rotateRight(node);
        }
        node->parent->color = black;
        node->parent->parent->color = red;
        rotateLeft(node->parent->parent);
      }
    }
  }

  root->color = black;
};

RedBlackTree::TreeNode* RedBlackTree::find(int key) {
  TreeNode* current = root;

  while (current != nil) {
    if (current->key < key) {
      current = current->right;
    } else if (current->key > key) {
      current = current->left;
    } else {
      return current;
    }
  }

  return current;
}

bool RedBlackTree::contains(int key) { return find(key) != nil; }

void RedBlackTree::transplant(TreeNode* nodeToRemove, TreeNode* node) {
  if (!nodeToRemove->parent) {
    root = node;
  } else if (nodeToRemove->parent->left == nodeToRemove) {
    nodeToRemove->parent->left = node;
  } else {
    nodeToRemove->parent->right = node;
  }

  node->parent = nodeToRemove->parent;
}

RedBlackTree::TreeNode* RedBlackTree::minimum(TreeNode* node) {
  while (node->left != nil) {
    node = node->left;
  }
  return node;
}

void RedBlackTree::remove(int key) {
  TreeNode* nodeToRemove = find(key);
  TreeNode* nodeToFix{};
  Color originalColor = nodeToRemove->color;

  if (nodeToRemove == nil) {
    return;
  }

  if (nodeToRemove->left == nil) {
    nodeToFix = nodeToRemove->right;
    transplant(nodeToRemove, nodeToFix);
  } else if (nodeToRemove->right == nil) {
    nodeToFix = nodeToRemove->left;
    transplant(nodeToRemove, nodeToFix);
  } else {
    TreeNode* min = minimum(nodeToRemove->right);
    nodeToFix = min->right;
    originalColor = min->color;
    if (min->parent != nodeToRemove) {
      transplant(min, nodeToFix);
      min->right = nodeToRemove->right;
      min->right->parent = min;
    } else {
      nodeToFix->parent = min;
    }
    transplant(nodeToRemove, min);
    min->left = nodeToRemove->left;
    min->left->parent = min;
    min->color = nodeToRemove->color;
  }

  delete nodeToRemove;
  size--;

  if (originalColor == black) {
    fixRemoval(nodeToFix);
  }
}

void RedBlackTree::fixRemoval(TreeNode* node) {
  while (node != root && node->color == black) {
    if (node == node->parent->left) {
      TreeNode* sibling = node->parent->right;
      if (sibling->color == red) {
        sibling->color = black;
        node->parent->color = red;
        rotateLeft(node->parent);
        sibling = node->parent->right;
      }
      if (sibling->left->color == black && sibling->right->color == black) {
        sibling->color = red;
        node = node->parent;
      } else {
        if (sibling->right->color == black) {
          sibling->left->color = black;
          sibling->color = red;
          rotateRight(sibling);
          sibling = node->parent->right;
        }
        sibling->color = node->parent->color;
        node->parent->color = black;
        sibling->right->color = black;
        rotateLeft(node->parent);
        node = root;
      }
    } else {
      TreeNode* sibling = node->parent->left;
      if (sibling->color == red) {
        sibling->color = black;
        node->parent->color = red;
        rotateRight(node->parent);
        sibling = node->parent->left;
      }
      if (sibling->right->color == black && sibling->left->color == black) {
        sibling->color = red;
        node = node->parent;
      } else {
        if (sibling->left->color == black) {
          sibling->right->color = black;
          sibling->color = red;
          rotateLeft(sibling);
          sibling = node->parent->left;
        }
        sibling->color = node->parent->color;
        node->parent->color = black;
        sibling->left->color = black;
        rotateRight(node->parent);
        node = root;
      }
    }
  }
  node->color = black;
}
