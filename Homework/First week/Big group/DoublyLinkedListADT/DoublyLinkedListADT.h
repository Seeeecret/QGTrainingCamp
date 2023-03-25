
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
} Item; //声明元素变量
typedef struct Node {
    Item item;
    struct Node* next;
    struct Node* prev;
} Node;// 声明结点变量

typedef struct List {
    Node* head;
    Node* tail;
} List;// 声明链表变量，其存储链表结构头结点和尾结点的地址

Node* createNode(Item newItem) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->item = newItem;
    node->prev = NULL;
    node->next = NULL;
    return node; //创造一个新的节点，封装成了函数
}

void initList(List** list) {// 初始化链表
    (* list) = (List*)malloc(sizeof(List));
    (* list)->head = NULL;
    (* list)->tail = NULL;
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
    else if (list->head == NULL) { // 如果链表为空
        list->head = newNode;
        list->tail = newNode;
    }
    else {
        newNode->next = list->head;// 更新头结点的地址
        list->head->prev = newNode;
        list->head = newNode;
    }
    puts("New node added! Enter something except integer to quit!");
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
    puts("New node added! Enter something except integer to quit!");
    return;
}

void deleteAtHead(List* list) {//删除头结点
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
    list->head = oldHead->next;//更新头结点
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

Node* findMiddle(List* list) {
    // 如果链表为空，报错
    if (list == NULL) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return NULL;
    }
    else if (list->head == NULL) {
        fprintf(stderr, "EmptyListException! Try again!\n");
        return NULL;
    }
    else if (list->head->next == NULL) return list->head;
    // 定义快慢指针并初始化为头节点
    Node* fast = list->head;
    Node* slow = list->head;
    // 循环遍历链表，让快指针每次走两步，慢指针每次走一步
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next; // 快指针走两步
        slow = slow->next; // 慢指针走一步
    }
    // 当快指针走到尾部时，慢指针就在中间节点
    return slow;
}

bool hasCycle(List* list) {//判断是否有环

    // 如果链表为空，报错并返回false
    if (list == NULL) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return false;
    }
    else if (list->head == NULL) {
        fprintf(stderr, "EmptyListException! Try again!\n");
        return false;
    }
        // 定义快慢指针并初始化为头节点
        Node* fast = list->head;
        Node* slow = list->head;

        // 循环遍历链表，让快指针每次走两步，慢指针每次走一步
        while (fast != NULL && fast->next != NULL) {
            fast = fast->next->next; // 快指针走两步
            slow = slow->next; // 慢指针走一步
            // 如果快慢指针相遇了，说明有环
            if (fast == slow) {
                return true;
            }
        }
        return false;
}


void deleteAtTail(List* list) {//有严重bug先弃用
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


void printList(List* list) {//打印链表数据
    if (list==NULL || list->head==NULL) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return;
    }
    Node* current = list->head;
    int count = 1;
    while (current != NULL) {
        printf("Node %d data: %d \n", count,current->item.data);
        current = current->next;
        count++;
    }
    puts("");
    return;
}


void deleteList(List** list) {//清空链表
    if (list == NULL||(* list) == NULL) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return;
    }
    Node* tempNode;
    Node* head = (* list)->head;
    while ((head) != NULL) {
        tempNode = (head)->next;
        free(head);
        head = tempNode;
    }
    *list = NULL;
    puts("All datas have already been cleaned.");
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

