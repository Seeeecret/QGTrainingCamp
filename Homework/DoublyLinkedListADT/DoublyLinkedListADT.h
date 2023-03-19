#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct item {
    int data;
    item(int a) {
        data = a;
    }
} Item;
typedef struct Node {
    Item item;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct List {
    Node* head;
    Node* tail;
} List;

Node* createNode(Item newItem) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->item = newItem;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void initList(List* list) {
    list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
}

int getListLength(List* list) {//结点个数的计数函数
    int cnt = 0;
    Node* tempNode = list->head;
    while (tempNode != NULL) {
        cnt++;
        tempNode = tempNode->next;
    }
    return cnt;
}

void addAtHead(List* list, Item newItem) {
    Node* newNode = createNode(newItem);
    if (list == NULL) {
        fprintf(stderr, "NullPointerException! Enter something except integer to quit!\n");
        fflush(stdin);
        rewind(stdin);
        return;
    }
    else if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    }
    else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    puts("New node added!");
    return;
}

void addAtTail(List* list, Item newItem) {
    Node* newNode = createNode(newItem);
    if (list == NULL) {
        fprintf(stderr, "NullPointerException! Enter something except integer to quit!\n");
        fflush(stdin);
        rewind(stdin);
        return;
    }
    else if (list->tail == NULL) {  // 如果链表为空
        list->head = newNode;
        list->tail = newNode;
       
    }
    else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;  // 更新尾结点的地址
    }
    puts("New node added!");
    return;
}

void deleteAtHead(List* list) {
    if (list == NULL) {
        fprintf(stderr, "NullPointerException! Enter something except integer to quit!\n");
        fflush(stdin);
        rewind(stdin);
        return;
    }
    else if (list->head == NULL) { // 链表为空，直接返回
        fprintf(stderr, "EmptyListException! Try again!\n");
        return;
    }
    Node* oldHead = list->head;
    list->head = oldHead->next;
    if (list->head != NULL) { // 新的头节点不为空，更新前驱节点指针
        list->head->prev = NULL;
    }
    else { // 如果链表只有一个节点，同时删除尾节点
        list->tail = NULL;
    }
    puts("Node was deleted!");
    free(oldHead);
    return;
}


void deleteAtTail(List* list) {
    if (list == NULL) {
        fprintf(stderr, "NullPointerException! Enter something except integer to quit!\n");
        fflush(stdin);
        rewind(stdin);
        return;
    }
    else if (list->tail == NULL) {  // 如果链表为空
        fprintf(stderr, "EmptyListException! Try again!\n");
        return;
    }
    Node* temp = list->tail;
    if (temp->prev == NULL) {  // 如果链表中只有一个节点
        list->head = NULL;
        list->tail = NULL;
    }
    else {
        list->tail = temp->prev;
        list->tail->next = NULL;
    }
    puts("Node was deleted!");
    free(temp);
    return;
}

void insertAtIndex(List* list, int index, Item newItem) {
    int length = getListLength(list);
    if (list==NULL) {
        fprintf(stderr, "NullPointerException! Enter something except integer to quit!\n");
        return;
    }
    else if (index < 0 || index > length) {
        fprintf(stderr, "IndexOutOfBoundException! Enter something except integer to quit!\n");
        return;
    }
    else {
        puts("New node inserted!");
        if (index < length / 2) {
            Node* cur = list->head;
            for (int i = 0; i < index; i++) {
                cur = cur->next;
            }
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->item = newItem;
            newNode->next = cur;
            newNode->prev = cur->prev;
            cur->prev->next = newNode;
            cur->prev = newNode;
        }
        else {
            Node* cur = list->tail;
            for (int i = length; i >= index; i--) {
                cur = cur->prev;
            }
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->item = newItem;
            newNode->next = cur;
            newNode->prev = cur->prev;
            cur->prev->next = newNode;
            cur->prev = newNode;
        }
    }
}

void deleteAtIndex(List* list, int index) {
    int length = getListLength(list);
    if (list == NULL) {
        fprintf(stderr, "NullPointerException! Enter something except integer to quit!\n");
        return;
    }
    else if (index < 0 || index > length) {
        fprintf(stderr, "IndexOutOfBoundException! Enter something except integer to quit!\n");
        return;
    }
    else if (index == 1) deleteAtHead(list);
    else if (index == length)deleteAtTail(list);
    else
    {
        puts("New node was deleted!");
        if (index < length / 2) {
            Node* cur = list->head;
            for (int i = 1; i < index; i++) {
                cur = cur->next;
            }
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            free(cur);
            cur = NULL;
        }
        else {
            Node* cur = list->tail;
            for (int i = length; i > index; i--) {
                cur = cur->prev;
            }
            Node* newNode = (Node*)malloc(sizeof(Node));
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            free(cur);
            cur = NULL;
        }
    }
}

void printList(List* list) {//打印链表数据
    if (list==NULL || list->head==NULL) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return;
    }
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->item.data);
        current = current->next;
    }
    puts("");
    return;
}


void deleteList(List** list) {//清空链表
    Node* tempNode;
    Node* head = (* list)->head;
    while ((head) != NULL) {
        tempNode = (head)->next;
        free(head);
        head = tempNode;
    }
    list = NULL;
    return;
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

