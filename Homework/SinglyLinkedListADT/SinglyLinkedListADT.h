#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
struct Item
{
    int data;
};
struct Node {
    Item item;
    struct Node* next;//ָ����һ�ڵ��ָ��
};
typedef Node* List;//��������,�������������ָ������ͷ�ڵ��ָ��

List createEmptyList() {
    Node* head = (Node*)malloc(sizeof(Node)); // ����ͷ�ڵ�ռ�
    head->next = NULL; // ͷ�ڵ��ָ����Ϊ��
    return head; // ����ͷ�ڵ�ָ��
}

bool isFull() {//�ж������Ƿ�����(���ڴ�ʣ��)
    Node* tempNode = (Node*)malloc(sizeof(Node));
    if (tempNode == NULL) {
        free(tempNode);
        return true;
    }
    else {
        free(tempNode);
        return false;
    }
}

bool isNULL(List head) {
    return head == NULL;
}

unsigned int getListLength(const List head) {//�������ļ�������
    unsigned int cnt = 0;
    Node* tempNode = head;
    while (tempNode != NULL) {
        cnt++;
        tempNode = tempNode->next;
    }
    return cnt;
}

bool addNewNode(const List head, Item newItem) {
    if(isNULL(head)) fprintf(stderr, "NullPointerException! Try again!\n");
    else if (isFull()) {
        fprintf(stderr, "MemoryAllocationException! Try again!\n");
        return false;
    }
    else {
        puts("New node added!");
    }
    Node* p = head; // ��p��������
    while (p->next != NULL) { // �ҵ����һ���ڵ�
        p = p->next;
    }
    Node* newNode = (Node*)malloc(sizeof(Node)); // �����½ڵ�ռ�
    newNode->item = newItem; 
    newNode->next = NULL; // �½ڵ��ָ����Ϊ��
    p->next = newNode; // ���һ���ڵ��ָ����ָ���½ڵ�
    return true;
}

bool insertNewNode(List head, int index, Item newItem) {
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return false;
    }
    else if (isFull()) {
    fprintf(stderr, "MemoryAllocationException! Try again!\n");
    return false;
    }
    else if (index < 1 || index > getListLength(head)) {
        fprintf(stderr, "IndexOutOfBoundException! Try again!\n");
        return false;
    }
    else {
    puts("New node inserted!");
    }
    int count = 1;
    Node* tempNode = head;
    while (count < index - 1) {
        tempNode = tempNode->next;
        count++;
    }
    Node* insertNode = (Node*)malloc(sizeof(Node));
    insertNode->next = tempNode->next;
    insertNode->item = newItem;
    tempNode->next = insertNode;
    return true;
}

bool deteleNode(List head, int index) {
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return false;
    }
    else if (index < 1 || index > getListLength(head)) {
        fprintf(stderr, "IndexOutOfBoundException! Try again!\n");
        return false;
    }
    else if (index == 0) {
        Node* tempNode = head;
        head = head->next;
        free(tempNode);
        return true;
    }
    else puts("Node was deleted!");
    Node* tempNode = head;
    int count = 1;
    while (count < index - 1) {
        tempNode = tempNode->next;
        count++;
    }
    Node* deletedNode = tempNode->next;
    tempNode->next = deletedNode->next;
    free(deletedNode);
    return true;
}

void deleteList(List* head) {//�������
    Node* tempNode;
    while ((* head) != NULL) {
        tempNode = (* head)->next;
        free(*head);
        *head = tempNode;
    }
    head = NULL;
    return;
}

bool equalItem(Item item1, Item item2) {
    return item1.data == item2.data;
}
/*
void emptyFunction(Item item) {
    return;
}

bool traverseTo(const List head, void(*pfunc)(Item item), Item target) {//��������������abc�Ľڵ�,ִ��pfunc()����
    Node* tempNode = head;
    while (tempNode != NULL) {
        if (equalItem(tempNode->item,target)) {
            (*pfunc)(tempNode->item);
            return true;
        }
        tempNode = tempNode->next;
    }
    return false;
}*/

Node* searchNode(const List head, Item target) {
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return NULL;
    }
    Node* tempNode = head;
    while (tempNode != NULL) {
        if (equalItem(tempNode->item, target)) {
            return tempNode;
        }
        tempNode = tempNode->next;
    }
    return NULL;
}

void printList(const List head) {
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return;
    }
    Node* tempNode = head->next;
    int count = 2;
    while (tempNode != NULL) {
        fprintf(stdout, "Node %d: %d\n", count, tempNode->item.data);
        tempNode = tempNode->next;
        count++;
    }
    return;
}