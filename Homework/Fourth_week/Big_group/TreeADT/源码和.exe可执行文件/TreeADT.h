// ����������ADT
/*
* ����������ķ�ʽʵ�֣�ÿ���ڵ�洢����ָ��:���ӡ����ӡ����ڵ�
* ��Ҫ�ֱ���ɲ��ҡ����롢ɾ���������������������ĵݹ�ͷǵݹ�汾
* �ѿ��Գ����˽Ⲣʵ�֣�AVL��Ҫ��ת�ѶȽϸߣ���������ڸ��ӡ�
*/
//#ifndef _TREEADT_H_
//#define _TREEADT_H_
#include <iostream>
#include <queue>
#include "StackADT.h"
#include <windows.h>
#define MAXSIZE 100
using namespace std;

// ��ʼ��
void initTree(Tree **tree);
// ����
TreeNode *searchNode(Tree *tree, int value);
// ����
bool insertNode(Tree *tree, int value);
// ɾ��
bool deleteNode(Tree *tree, int value);
// �������
void preOrderRecursive(TreeNode *root);
void inOrderRecursive(TreeNode *root);
void postOrderRecursive(TreeNode *root);
// �������
void levelOrder(TreeNode *root);
// �ǵݹ��������
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
// ����
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
// ����
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

// ɾ��
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
	// ֻ��һ���ڵ�,�Ҹýڵ�λ���ڵ�
	if (tree->root->value == node->value && isNULL(tree->root->right)&& isNULL(tree->root->left)) {
		free(node);
		tree->root = NULL;
		return true;
	}
	// ����������
	else if (node->left == NULL && node->right == NULL) {
		if (isLeftChild(node)) {
		parent->left = NULL;	
		}
		else {			
		parent->right = NULL;
		}
		free(node);
	}
	// ��������
	else if (node->left == NULL) {
		if (isNULL(parent)) {// ������ڵ㲻����,���ҵ��Ľڵ��Ǹ��ڵ�
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
	// ��������
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
	// ����������
	else {
		TreeNode *temp = node->right;// �ҵ�����������С�Ľڵ�
		while (temp->left != NULL) {
			temp = temp->left;
		}
		if (temp->value == tree->root->right->value){ // �Ǹ��ڵ���ҽڵ�
			temp->parent->right = temp->right;
		}
		else if (isLeftChild(temp) && !isNULL(temp->right)) {// Ŀ���滻�ڵ������ӽڵ��������ӽڵ�
			temp->parent->left = temp->right;
		}
		else if (!isLeftChild(temp) && !isNULL(temp->right)) {// Ŀ���滻�ڵ������ӽڵ��������ӽڵ�
			temp->parent->right = temp->right;
		}
		else {// Ŀ��ڵ����ӽڵ�
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
// ɾ��������
void deleteAll(TreeNode* root) {
	if (!isNULL(root)) {
		deleteAll(root->left);
		deleteAll(root->right);
		free(root);
	}
}
// ɾ�����������ⲿ��װ
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

// �ж��Ƿ�ΪNULL
bool isNULL(Tree* tree) {
	if (tree != NULL)return false;
	else return true;
}
bool isNULL(TreeNode* tree) {
	if (tree != NULL)return false;
	else return true;
}

// �ж���Ϊ��	
bool isEmpty(Tree* tree) {
	if (tree->root != NULL)return false;
	else return true;
}

// �жϴ���ڵ��ǲ��Ǹ��ڵ����ڵ㣬�Ƿ���true,���Ƿ���false
bool isLeftChild(TreeNode *treeNode) {
	if (isNULL(treeNode->parent->left)) return false;
	if (treeNode->parent->left->value == treeNode->value) return true;
	else return false;
}

// ��������ݹ�:
// ǰ�����
void preOrderRecursive(TreeNode* root) {
	if (!isNULL(root)) {
		printf("%d  ", root->value);
		preOrderRecursive(root->left);
		preOrderRecursive(root->right);
	}
}
// �������
void inOrderRecursive(TreeNode* root) {
	if (!isNULL(root)) {
		inOrderRecursive(root->left);
		printf("%d  ", root->value);
		inOrderRecursive(root->right);
	}
}
// �������
void postOrderRecursive(TreeNode* root) {
	if (!isNULL(root)) {
		postOrderRecursive(root->left);
		postOrderRecursive(root->right);
		printf("%d  ", root->value);
	}
}

// ��������ǵݹ�:
// �ǵݹ�ǰ�����
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
// �ǵݹ��������
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
// �ǵݹ�������
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

// �������
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
// ������Ԫ���ⲿ��װ
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