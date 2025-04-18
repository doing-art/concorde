#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

class RedBlackTree {
public:
	enum Color {
		red,
		black
	};

	struct TreeNode {
		int value{};
		Color color{};
		TreeNode* parent{};
		TreeNode* left{};
		TreeNode* right{};

		TreeNode(int newValue, Color newColor = red) :value{ newValue }, color{ newColor } { }
	};

	void insert(int value);
	void printInorder();

private:
	TreeNode* root{};
	void rotateLeft(TreeNode* node);
	void rotateRight(TreeNode* node);
	void fixInsertion(TreeNode* node);
};

#endif
