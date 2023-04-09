// 二叉排序树ADT
/*
* 用类似链表的方式实现，每个节点存储三个指针:左子、右子、父节点
* 需要分别完成查找、插入、删除、层序遍历、三序遍历的递归和非递归版本
* 堆可以尝试了解并实现，AVL需要旋转难度较高，红黑树过于复杂。
*/
//#ifndef _TREEADT_H_
//#define _TREEADT_H_
#include <iostream>
#include <queue>
#include "StackADT.h"
#include <windows.h>
#define MAXSIZE 100
using namespace std;

// 初始化
void initTree(Tree **tree);
// 查找
TreeNode *searchNode(Tree *tree, int value);
// 插入
bool insertNode(Tree *tree, int value);
// 删除
bool deleteNode(Tree *tree, int value);
// 三序遍历
void preOrderRecursive(TreeNode *root);
void inOrderRecursive(TreeNode *root);
void postOrderRecursive(TreeNode *root);
// 层序遍历
void levelOrder(TreeNode *root);
// 非递归三序遍历
void preOrderIterative(TreeNode *root);
void inOrderIterative(TreeNode *root);
void postOrderIterative(TreeNode *root);

//#endif
bool isNULL(Tree* tree);
bool isEmpty(Tree* tree);
bool isLeftChild(TreeNode* treeNode);
bool isNULL(TreeNode* tree);
void deleteAll(TreeNode* root);
void deleteTree(Tree* tree);
void traverseCell(Tree* tree, void(*pfunc)(TreeNode* root));
void initTree(Tree **tree) {
	if (isNULL(*tree)) {
		*tree = (Tree*)malloc(sizeof(Tree));
		if (*tree == NULL) {
			fprintf(stderr, "MemoryAllocationException! Please try again.\n");
			free(tree);
			return;
		}
		(*tree)->root = NULL;
		puts("A new tree has been initialized.");
	}
	else {
		fprintf(stderr, "ExisitingTreeException! You have already create a tree.\n");
		return;
	}
}
// 查找
TreeNode *searchNode(Tree *tree, int value) {
	if (isNULL(tree)) {
		fprintf(stderr, "NullPointerException! Please try again.\n");
		return NULL;
	}
	TreeNode *node = tree->root;
	while (node != NULL) {
		if (node->value == value) {
			break;
		}
		else if (node->value > value) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	return node;
}
// 插入
bool insertNode(Tree* tree, int value) {
	if (isNULL(tree)) {
		fprintf(stderr, "NullPointerException! Please try again.\n");
		return false;
	}
	TreeNode* node = tree->root;
	TreeNode* parent = NULL;
	if (!isNULL(searchNode(tree, value))) {
		fprintf(stderr, "ExsistingNodeException! You have already insert the same node into the tree!.\n");
		return false;
	}
	while (node != NULL) {
		parent = node;
		if (node->value == value)	return false;
		else if (node->value > value) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	memset(newNode, 0, sizeof(TreeNode));
	newNode->value = value;
	newNode->left = newNode->right = NULL;
	newNode->parent = parent;
	if (parent == NULL) {
		tree->root = newNode;
	}
	else if (parent->value > value) {
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}
	return true;
}

// 删除
bool deleteNode(Tree* tree, int value) {
	if (isNULL(tree)) {
		fprintf(stderr, "NullPointerException! Please try again.\n");
		return false;
	}
	if (isEmpty(tree)) {
		fprintf(stderr, "EmptyTreeException! Please try again.\n");
		return false;
	}
	TreeNode *node = searchNode(tree, value);
	if (isNULL(node))	return false;
	TreeNode *parent = node->parent;
	// 只有一个节点,且该节点位根节点
	if (tree->root->value == node->value && isNULL(tree->root->right)&& isNULL(tree->root->left)) {
		free(node);
		tree->root = NULL;
		return true;
	}
	// 无左右子树
	else if (node->left == NULL && node->right == NULL) {
		if (isLeftChild(node)) {
		parent->left = NULL;	
		}
		else {			
		parent->right = NULL;
		}
		free(node);
	}
	// 无左子树
	else if (node->left == NULL) {
		if (isNULL(parent)) {// 如果父节点不存在,即找到的节点是根节点
			tree->root = node->right;
		}
		else if (isLeftChild(node)) {
			parent->left = node->right;
		}
		else {
			parent->right = node->right;
		}
		free(node);
	}
	// 无右子树
	else if (node->right == NULL) {
		if (isNULL(parent)) {
			tree->root = node->left;
		}
		else if (isLeftChild(node)) {
			parent->left = node->left;
		}
		else {
			parent->right = node->left;
		}
		free(node);
	}
	// 有左右子树
	else {
		TreeNode *temp = node->right;// 找到右子树中最小的节点
		while (temp->left != NULL) {
			temp = temp->left;
		}
		if (temp->value == tree->root->right->value){ // 是根节点的右节点
			temp->parent->right = temp->right;
		}
		else if (isLeftChild(temp) && !isNULL(temp->right)) {// 目标替换节点是左子节点且有右子节点
			temp->parent->left = temp->right;
		}
		else if (!isLeftChild(temp) && !isNULL(temp->right)) {// 目标替换节点是右子节点且有右子节点
			temp->parent->right = temp->right;
		}
		else {// 目标节点无子节点
			if (isLeftChild(temp)) {
				temp->parent->left = NULL;
			}
			else {
				temp->parent -> right = NULL;
			}
		}
		node->value = temp->value;
		free(temp);
	}
	return true;
}
// 删除整棵树
void deleteAll(TreeNode* root) {
	if (!isNULL(root)) {
		deleteAll(root->left);
		deleteAll(root->right);
		free(root);
	}
}
// 删除整棵树的外部封装
void deleteTree(Tree* tree) {
	if (isNULL(tree)) {
		fprintf(stderr, "NullPointerException! Please try again.\n");
		return;
	}
	if (isEmpty(tree)) {
		puts("Successfully delete the tree!");
		return;
	}
	deleteAll(tree->root);
	tree->root = NULL;
	puts("Successfully delete the tree!");
}

// 判断是否为NULL
bool isNULL(Tree* tree) {
	if (tree != NULL)return false;
	else return true;
}
bool isNULL(TreeNode* tree) {
	if (tree != NULL)return false;
	else return true;
}

// 判断树为空	
bool isEmpty(Tree* tree) {
	if (tree->root != NULL)return false;
	else return true;
}

// 判断传入节点是不是父节点的左节点，是返回true,不是返回false
bool isLeftChild(TreeNode *treeNode) {
	if (isNULL(treeNode->parent->left)) return false;
	if (treeNode->parent->left->value == treeNode->value) return true;
	else return false;
}

// 三序遍历递归:
// 前序遍历
void preOrderRecursive(TreeNode* root) {
	if (!isNULL(root)) {
		printf("%d  ", root->value);
		preOrderRecursive(root->left);
		preOrderRecursive(root->right);
	}
}
// 中序遍历
void inOrderRecursive(TreeNode* root) {
	if (!isNULL(root)) {
		inOrderRecursive(root->left);
		printf("%d  ", root->value);
		inOrderRecursive(root->right);
	}
}
// 后序遍历
void postOrderRecursive(TreeNode* root) {
	if (!isNULL(root)) {
		postOrderRecursive(root->left);
		postOrderRecursive(root->right);
		printf("%d  ", root->value);
	}
}

// 三序遍历非递归:
// 非递归前序遍历
void preOrderIterative(TreeNode* root) {
	Stack stackItem = createStack();
	Stack *stack = &stackItem;
	TreeNode *node = root;
	pushStack(stack, node);
	
	while (!isNULL(node) || !isEmpty(stack)) {
		node = popStack(stack).data;
		if (isNULL(node))break;
		printf("%d  ", node->value);
		
		if (!isNULL(node->right)) {
			pushStack(stack, node->right);
		}
		if (!isNULL(node->left)) {
			pushStack(stack, node->left);
		}
	}
	deleteStack(stack);
}
// 非递归中序遍历
void inOrderIterative(TreeNode* root) {
	Stack stackItem = createStack();
	Stack *stack = &stackItem;
	TreeNode *node = root;
	while (!isNULL(node) || !isEmpty(stack)) {
		while (node != NULL) {
			pushStack(stack, node);
			node = node->left;
		}
		if (!isEmpty(stack)) {
			node = popStack(stack).data;
			printf("%d  ", node->value);
			node = node->right;
		}
	}
	deleteStack(stack);

}
// 非递归后序遍历
void postOrderIterative(TreeNode* root) {
	Stack stackItem1 = createStack();
	Stack stackItem2 = createStack();
	Stack *stack1 = &stackItem1;
	Stack *stack2 = &stackItem2;
	TreeNode *node = root;
	TreeNode *last = NULL;
	pushStack(stack1, node);
	while (!isEmpty(stack1))
	{
		node = popStack(stack1).data;
		pushStack(stack2, node);

		if (!isNULL(node->left))
			pushStack(stack1, node->left);
		if (!isNULL(node->right))
			pushStack(stack1, node->right);
	}

	while (!isEmpty(stack2))
	{
		node = popStack(stack2).data;
		printf("%d  ", node->value);
	}
	deleteStack(stack1);
	deleteStack(stack2);
	puts("");
}

// 层序遍历
void levelOrder(TreeNode* tree) {
	queue<TreeNode*> q;
	q.push(tree);
	while (!q.empty()) {
		TreeNode *node = q.front();
		q.pop();
		printf("%d  ", node->value);
		if (node->left != NULL) {
			q.push(node->left);
		}
		if (node->right != NULL) {
			q.push(node->right);
		}
	}
}
// 遍历单元的外部封装
void traverseCell(Tree* tree, void(*pfunc)(TreeNode* root)) {
	if (isNULL(tree)) {
		fprintf(stderr, "NullPointerException! Please try again.\n");
		return ;
	}
	if (isEmpty(tree)) {
		fprintf(stderr, "EmptyTreeException! Please try again.\n");
		return ;
	}
	pfunc(tree->root);
	puts("");
	return;
}