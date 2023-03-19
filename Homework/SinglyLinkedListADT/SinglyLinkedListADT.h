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
    struct node* next;//ָ����һ�ڵ��ָ��
};
typedef struct node Node;
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
     // �������Ϊ�գ�����
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return NULL;
    } 
    else if (head->next == NULL) {
    // ���ֻ��һ���ڵ㣬ֱ�ӷ���ͷ�ڵ�
        return head;
    }
    // �������ָ�벢��ʼ��Ϊͷ�ڵ�
    Node* fast = head;
    Node* slow = head;
    // ѭ�����������ÿ�ָ��ÿ������������ָ��ÿ����һ��
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next; // ��ָ��������
        slow = slow->next; // ��ָ����һ��
    }
    // ����ָ���ߵ�β��ʱ����ָ������м�ڵ�
    return slow;
}


bool hasCycle(List head) {

    // �������Ϊ�գ���������false
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return false;
    }
    else if(isNULL(head->next)) return false;

    // �������ָ�벢��ʼ��Ϊͷ�ڵ�
    Node* fast = head;
    Node* slow = head;

    // ѭ�����������ÿ�ָ��ÿ������������ָ��ÿ����һ��
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next; // ��ָ��������
        slow = slow->next; // ��ָ����һ��
        // �������ָ�������ˣ�˵���л�
        if (fast == slow) {
            return true;
        }
    }

    // �����ָ���ߵ���β����˵��û�л�
    return false;
}

//  �ݹ鷨��ת����
List recursive(List head) {
    // �������Ϊ�գ���������head
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return head;
    }// ���ֻ��һ���ڵ㣬Ҳ����head
    else if (isNULL(head->next)) return head;
    // �ݹ�ط�תhead->next����Ĳ��֣��������µ�ͷ�ڵ�newHead
    Node* newHead = recursive(head->next);
    // ��head->next�ڵ�ָ��head���γɻ�
    head->next->next = head;
    // ��head->next�ÿգ��Ͽ���
    head->next = NULL;
    // �����µ�ͷ�ڵ�newHead
    return newHead;
}

// �ݹ鷨������װ
void recursiveReverse(List head) {
    List recursiveHead = head->next;
    head->next = recursive(recursiveHead);
}

// ָ�뷨��ת����
List pointer(List head) {
     // �������Ϊ�գ���������head
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return head;
    }// ���ֻ��һ���ڵ㣬Ҳ����head
    else if (isNULL(head->next)) return head;
    // ��������ָ��pre��cur��next������ʼ��ΪNULL��head��NULL 
    Node* pre = NULL;
    Node* cur = head;
    Node* next = NULL;
    // ����ԭ��������ÿ�θı䵱ǰ���cur��ָ��Ϊprev������������ָ��λ�� 
    while (cur != NULL) {
        next = cur->next;  // ��¼��ǰ���cur����һ�����Ϊnext  
        cur->next = pre;  // �ı䵱ǰ���cur��ָ��Ϊprev  
        pre = cur;  // ����ǰһ���preΪcurr  
        cur = next;  // ���µ�ǰ���curΪnext  
    }
    return pre;  // �������һ�θ��º�pre����λ�ã���ԭ��β��㣩��Ϊ��ͷ���  
}

// ָ�뷨������װ
void pointerReverse(List head) {
    List pointerHead = head->next;
    head->next = recursive(pointerHead);
}
