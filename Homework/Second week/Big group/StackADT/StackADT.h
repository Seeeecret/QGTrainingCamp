#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct item {
    double data;
    item(double newData) {
        data = newData;
    }
} Item;

typedef struct Node // ջ���
{
    Item item; // ������
    struct Node* next; // ָ����
} Node;

typedef struct Node* Stack; // ջ����

Stack createStack() {// ����һ����ջ
    Stack s = (Stack)malloc(sizeof(Node)); // �����ڴ�ռ�
    if (s==NULL) // �ڴ����ʧ��
    {
        printf("MemoryAllocationException!Please try again!\n");
        return NULL;
    }
    s->next = NULL; // ջ��ָ��ָ��NULL
    s->item.data = NAN;
    return s;

}

bool isEmpty(Stack* s) {
    return isnan((*s)->item.data);
}// �ж�ջ�Ƿ�Ϊ��

int countStack(Stack* s) {
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

void deleteStack(Stack* s) { // ɾ��һ��ջ
    Node* temp = NULL;
    while ((*s)->next != NULL) // ���������ͷ�ÿ�����Ŀռ�
    {
        temp = (*s)->next;
        (*s)->next = temp->next;
        free(temp);
    }
    free(*s); // �ͷ�ͷ���Ŀռ�
    *s = NULL;
}

void pushStack(Stack* s, Item newItem) { // ��ջ
    if(s==NULL){
        printf("NullPointerException! Please try again!\n");
        return;
    }
    else if (isEmpty(s)) {
        (*s)->item = newItem;
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
    }
}

Item popStack(Stack* s) { // ��ջ
    if ((*s) == NULL) {
        printf("NullPointerException! Please try again!\n");
        return Item(NAN);
    }
    else if (isEmpty(s)) {
        printf("EmptyStackException! Please try again!\n");
        return Item(NAN);
    }
    else if ((*s)->next == NULL) {
        Item popItem1 = (*s)->item;
        (*s)->item.data = NAN;
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
