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
    struct Node* next;//指向下一节点的指针
};
typedef Node* List;//声明链表,链表变量名就是指向链表头节点的指针

List createEmptyList() {
    Node* head = (Node*)malloc(sizeof(Node)); // 分配头节点空间
    head->next = NULL; // 头节点的指针域为空
    return head; // 返回头节点指针
}

bool isFull() {//判断链表是否已满(无内存剩余)
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

unsigned int getListLength(const List head) {//结点个数的计数函数
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
    Node* p = head; // 用p遍历链表
    while (p->next != NULL) { // 找到最后一个节点
        p = p->next;
    }
    Node* newNode = (Node*)malloc(sizeof(Node)); // 分配新节点空间
    newNode->item = newItem; 
    newNode->next = NULL; // 新节点的指针域为空
    p->next = newNode; // 最后一个节点的指针域指向新节点
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

void deleteList(List* head) {//清空链表
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

bool traverseTo(const List head, void(*pfunc)(Item item), Item target) {//遍历到符合条件abc的节点,执行pfunc()函数
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