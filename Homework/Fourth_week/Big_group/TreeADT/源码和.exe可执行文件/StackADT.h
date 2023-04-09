
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <time.h>
// ���ڵ�
typedef struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
}TreeNode;
// ��
typedef struct Tree {
    TreeNode* root;
}Tree;

struct item {
    TreeNode* data;
    item(TreeNode* newData) {
        data = newData;
    }
};


typedef struct item Item;


struct node // ջ���
{
    Item item; // ������
    struct node* next; // ָ����
};

typedef struct node Node;

typedef struct node* Stack; // ջ����






Stack createStack() {// ����һ����ջ
    Stack s = (Stack)malloc(sizeof(Node)); // �����ڴ�ռ�
    if (s==NULL) // �ڴ����ʧ��
    {
        printf("MemoryAllocationException!Please try again!\n");
        free(s);
        return NULL;
    }
    s->next = NULL; // ջ��ָ��ָ��NULL
    s->item.data = NULL;
    return s;

}
bool isNULLL(TreeNode* tree) {
    if (tree != NULL)return false;
    else return true;
}
bool isEmpty(Stack* s) { // �ж�ջ�Ƿ�Ϊ��
    if ((*s) == NULL) {
        return 1;
    }
    return isNULLL((*s)->item.data);
}// �ж�ջ�Ƿ�Ϊ��

int countStack(Stack* s) { // ����ջ��Ԫ�ظ���
    if ((*s) == NULL) {
        printf("NullPointerException! Please try again!\n");
        return -1;
    }
    else if (isEmpty(s)) {
        printf("EmptyStackException! Please try again!\n");
        return -1;
    }
    else {
        int cnt = 1;
        Node* temp = (*s);
        while (temp->next != NULL) {
            cnt++;
            temp = temp->next;
        }
        return cnt;
    }
}

void deleteStack(Stack* s) { // ɾ��ջ
    if ((*s) == NULL) {
        printf("NullPointerException! Please try again!\n");
        return;
    }
    Node* temp = NULL;
    while ((*s)->next != NULL) // ���������ͷ�ÿ�����Ŀռ�
    {
        temp = (*s)->next;
        (*s)->next = temp->next;
        free(temp);
    }
    free(*s); // �ͷ�ͷ���Ŀռ�
    *s = NULL;
    //printf("Done!\n");
}

void pushStack(Stack* s, Item newItem) { // ��ջ
    if((*s)==NULL){
        printf("NullPointerException! Please enter Q to quit and create a stack!\n");
        return;
    }
    else if (isEmpty(s)) {
        (*s)->item = newItem;
        //puts("New data pushed in!");
        return;
    }
    else {
        Node* p = (Node*)malloc(sizeof(Node)); // �����ڴ�ռ�
        if (!p) // �ڴ����ʧ��
        {
            printf("MemoryAllocationException! Please try again!\n");
            return;
        }
        p->item = newItem; // ָ����������ֵ
        p->next = (*s); // ���½����뵽ͷ�������
        (*s) = p; // ����ͷ�ڵ�
        //puts("New data pushed in!");
    }
}

Item popStack(Stack* s) { // ��ջ
    if ((*s) == NULL) {
        printf("NullPointerException! Please try again!\n");
        return Item(NULL);
    }
    else if (isEmpty(s)) {
        //printf("EmptyStackException! Please try again!\n");
        return Item(NULL);
    }
    else if ((*s)->next == NULL) {
        Item popItem1 = (*s)->item;
        (*s)->item.data = NULL;
        return popItem1;
    }
    else {
        Node* temp = (*s);
        Item popItem2 = (*s)->item;
        (*s) = (*s)->next;
        (*s)->next = temp->next->next;
        free(temp);
        return popItem2;
    }
}

