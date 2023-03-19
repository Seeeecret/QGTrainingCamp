#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
struct item
{
    int data;
};
typedef struct item Item;
struct node {
    Item item;
    struct node* next;//指向下一节点的指针
};
typedef struct node Node;
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

void swapEvenNodeOddNode(List head) {
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return;
        
    }
    else if (isNULL(head->next)) {
        fprintf(stderr, "EmptyListException! Try again!\n");
        return;
    }
    else if (isNULL(head->next->next)) {
        return;
    }
    Node* cur, * next, * pre;
    cur = head->next;
    next = head->next->next;
    pre = head;
    while (1) {
        pre->next = next;
        cur->next = next->next;
        next->next = cur;
        pre = cur;
        cur = cur->next;
        if (cur == NULL || cur->next == NULL) return;
        else next = cur->next;
    }
}
Node* findMiddle(List head) {
     // 如果链表为空，报错
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return NULL;
    } 
    else if (head->next == NULL) {
    // 如果只有一个节点，直接返回头节点
        return head;
    }
    // 定义快慢指针并初始化为头节点
    Node* fast = head;
    Node* slow = head;
    // 循环遍历链表，让快指针每次走两步，慢指针每次走一步
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next; // 快指针走两步
        slow = slow->next; // 慢指针走一步
    }
    // 当快指针走到尾部时，慢指针就在中间节点
    return slow;
}


bool hasCycle(List head) {

    // 如果链表为空，报错并返回false
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return false;
    }
    else if(isNULL(head->next)) return false;

    // 定义快慢指针并初始化为头节点
    Node* fast = head;
    Node* slow = head;

    // 循环遍历链表，让快指针每次走两步，慢指针每次走一步
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next; // 快指针走两步
        slow = slow->next; // 慢指针走一步
        // 如果快慢指针相遇了，说明有环
        if (fast == slow) {
            return true;
        }
    }

    // 如果快指针走到了尾部，说明没有环
    return false;
}

//  递归法反转链表
List recursive(List head) {
    // 如果链表为空，报错并返回head
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return head;
    }// 如果只有一个节点，也返回head
    else if (isNULL(head->next)) return head;
    // 递归地反转head->next后面的部分，并返回新的头节点newHead
    Node* newHead = recursive(head->next);
    // 将head->next节点指向head，形成环
    head->next->next = head;
    // 将head->next置空，断开环
    head->next = NULL;
    // 返回新的头节点newHead
    return newHead;
}

// 递归法的外层包装
void recursiveReverse(List head) {
    List recursiveHead = head->next;
    head->next = recursive(recursiveHead);
}

// 指针法反转链表
List pointer(List head) {
     // 如果链表为空，报错并返回head
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return head;
    }// 如果只有一个节点，也返回head
    else if (isNULL(head->next)) return head;
    // 定义三个指针pre、cur和next，并初始化为NULL、head和NULL 
    Node* pre = NULL;
    Node* cur = head;
    Node* next = NULL;
    // 遍历原来的链表，每次改变当前结点cur的指向为prev，并更新三个指针位置 
    while (cur != NULL) {
        next = cur->next;  // 记录当前结点cur的下一个结点为next  
        cur->next = pre;  // 改变当前结点cur的指向为prev  
        pre = cur;  // 更新前一结点pre为curr  
        cur = next;  // 更新当前结点cur为next  
    }
    return pre;  // 返回最后一次更新后pre所在位置（即原来尾结点）作为新头结点  
}

// 指针法的外层包装
void pointerReverse(List head) {
    List pointerHead = head->next;
    head->next = recursive(pointerHead);
}
