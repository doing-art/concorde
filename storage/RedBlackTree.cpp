#include <iostream>
#include <vector>
#include "RedBlackTree.h"

void RedBlackTree::insert(int value) {
	TreeNode* newNode = new TreeNode(value);

	if (!root) {
		root = newNode;
		return;
	}

	TreeNode* parent{};
	TreeNode* current{ root };
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
}

void RedBlackTree::printInorder() {
	TreeNode* current{ root };
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
