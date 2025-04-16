#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

class RedBlackTree {
public:
	struct TreeNode {
		int value{};
		bool color{};
		TreeNode* parent{};
		TreeNode* left{};
		TreeNode* right{};

		TreeNode(int newValue, bool newColor = false) :value{ newValue }, color{ newColor } { }
	};

	void insert(int value);
	void printInorder();

private:
	TreeNode* root{};
	void rotateLeft(TreeNode* node);
};

#endif
