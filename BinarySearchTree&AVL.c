#include <stdio.h>
#include<stdlib.h>

typedef struct BinarySearchTreeNode {
	int data;
	struct BinarySearchTreeNode* left;
	struct BinarySearchTreeNode* right;
} BinarySearchTreeNode;

struct BinarySearchTreeNode* Find(struct BinarySearchTreeNode* root, int data) {
	if (root == NULL)
		return NULL;
	
	if (data < root->data)
		return Find(root->left, data);
	else if (data > root->data)
		return Find(root->right, data);
	else
		return root;
}

struct BinarySearchTreeNode* BST_Insert(struct BinarySearchTreeNode* root, int data) {
	if (root == NULL) { // 빈 Tree
		root = (struct BinarySearchTreeNode*)malloc(sizeof(struct BinarySearchTreeNode));
		if (root == NULL) { // 에러 처리
			printf("Memory Error");
			return NULL;
		}
		else {
			root->data = data;
			root->left = root->right = NULL;
		}
	}
	else {
		if (data < root->data) root->left = BST_Insert(root->left, data);
		if (data > root->data) root->right = BST_Insert(root->right, data);
	}
	return root;
}

typedef struct AVLTreeNode {
	int data;
	struct AVLTreeNode* left;
	struct AVLTreeNode* right;
	int height;
} AVLTreeNode;

int Height(struct AVLTreeNode* root) {
	if (!root) return -1;
	else return root->height;
}

struct AVLTreeNode* Rotate_Right(struct AVLTreeNode* X) {
	struct AVLTreeNode* W = X->left;
	X->left = W->right;
	W->right = X;
	X->height = max(Height(X->left), Height(X->right)) + 1; // 높이 값 밸런싱
	W->height = max(Height(W->left), X->height) + 1;
	return W; // 새 루트 노드
}

struct AVLTreeNode* Rotate_Left(struct AVLTreeNode* W) {
	struct AVLTreeNode* X = W->right;
	W->right = X->left;
	X->left = X;
	W->height = max(Height(W->left), Height(W->right)) + 1; // 높이 값 밸런싱
	X->height = max(W->height, Height(X->right)) + 1;
	return X; // 새 루트 노드
}

struct AVLTreeNode* Rotate_LeftRight(struct AVLTreeNode* Z) {
	Z->left = Rotate_Left(Z->left);
	return Rotate_Right(Z);
}

struct AVLTreeNode* Rotate_RightLeft(struct AVLTreeNode* Z) {
	Z->right = Rotate_Right(Z->right);
	return Rotate_Left(Z);
}

struct AVLTreeNode* AVL_Insert(struct AVLTreeNode* root, int data) {
	if (root == NULL) { // 빈 Tree
		root = (struct AVLTreeNode*)malloc(sizeof(struct AVLTreeNode));
		if (root == NULL) { // 에러 처리
			printf("Memory Error");
			return NULL;
		}
		else {
			root->data = data;
			root->height = 0;
			root->left = root->right = NULL;
		}
	}
	else if (data < root->data) { // 왼쪽으로
		root->left = AVL_Insert(root->left, data);
		if ((Height(root->left) - Height(root->right)) == 2) {
			if (data < root->left->data) // LeftLeft Case
				root = Rotate_Right(root);
			else
				root = Rotate_LeftRight(root); // LeftRight Case
		}
	}
	else if (data > root->data) { // 오른쪽으로
		root->right = AVL_Insert(root->right, data);
		if ((Height(root->right) - Height(root->left)) == 2) {
			if (data > root->right->data) // RightRight Case
				root = Rotate_Left(root);
			else
				root = Rotate_RightLeft(root); // RightLeft Case
		}
	}
	root->height = max(Height(root->left), Height(root->right)) + 1;
	return root;
}

int main()
{
	struct BinarySearchTreeNode* mytree = NULL;	
	mytree = BST_Insert(mytree, 1);

	struct AVLTreeNode* mytree2 = NULL;
	mytree2 = AVL_Insert(mytree2, 2);

	return 0;
}