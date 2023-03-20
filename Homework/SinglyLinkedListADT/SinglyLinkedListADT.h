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
typedef struct node Node;//�����ڵ�
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
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Enter something except integer to quit!\n");
        fflush(stdin);
        rewind(stdin);
        return false;
    }
    else if (isFull()) {
        fprintf(stderr, "MemoryAllocationException! Enter something except integer to quit!\n");// ����ڴ��Ƿ��㹻
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

bool insertNewNode(List head, int index, Item newItem) {//��ĳλ�ò���ڵ㣬ԭ�ڵ����
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Enter something except integer to quit!\n");
        return false;
    }
    else if (isFull()) {
    fprintf(stderr, "MemoryAllocationException! Enter something except integer to quit!\n");
    return false;
    }
    else if (index < 1 || index > getListLength(head)) {
        fprintf(stderr, "IndexOutOfBoundException! Enter something except integer to quit!\n");
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

bool deleteNode(List head, int index) {// ɾ���ڵ�
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return false;
    }
    else if (index < 1 || index > getListLength(head)) {
        fprintf(stderr, "IndexOutOfBoundException! Try again!\n"); // ���������Խ���ˣ�����
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

bool equalItem(Item item1, Item item2) {//�ж�item1  item2�Ƿ����
    return item1.data == item2.data;
}

Node* searchNode(const List head, Item target) {//�����������Ƿ��нڵ�item��target��ȣ�����,���ؽڵ�ָ��
    if (isNULL(head)) {//�������û��ϵͳ����������ʱ�䲻����
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

void printList(const List head) {//��ӡ��������
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

void swapEvenNodeOddNode(List head) {//��ż����
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
    while (1) {//ԭ��Ϊÿ����Ϊһ�鴦��,��Ĭ��ΪA��B��C�ڵ�,a��b��c��ָ��
        pre->next = next;//��b,cָ�뽻��BC�ڵ㣬��aָ����A�ڵ��nextָ��C�ڵ㣬����aָ���ƶ���B�ڵ�,b,cָ��Ҳ��˳��ǰ�ƣ�����ѭ��
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
        return NULL;
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
    else if (isNULL(head->next)) return false;

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
    // ���ֻ��һ���ڵ㣬����head
    if (isNULL(head->next)) return head;// �ݹ�ط�תhead->next����Ĳ��֣��������µ�ͷ�ڵ�newHead
    Node* newHead = recursive(head->next); // ��head->next�ڵ�ָ��head���γɻ� 
    head->next->next = head;  
    head->next = NULL; // ��head->next�ÿգ��Ͽ���  
    return newHead; // �����µ�ͷ�ڵ�newHead
}

// �ݹ鷨������װ
void recursiveReverse(List head) {
    // �������Ϊ�գ���������head
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return;
    }
    else if (isNULL(head->next)) {
        fprintf(stderr, "EmptyListException! Try again!\n");
        return;
    }
    List recursiveHead = head->next;
    head->next = recursive(recursiveHead);
}

// ָ�뷨��ת����
List pointer(List head) {   
    // ���ֻ��һ���ڵ㣬Ҳ����head
    if (isNULL(head->next)) return head;
    Node* pre = NULL;
    Node* cur = head;
    Node* next = NULL;
    while (cur != NULL) { // ����ԭ��������ÿ�θı䵱ǰ���cur��ָ��Ϊprev������������ָ��λ�� 
        next = cur->next;  // ��¼��ǰ���cur����һ�����Ϊnext  
        cur->next = pre;  // �ı䵱ǰ���cur��ָ��Ϊpre
        pre = cur;  // ����ǰһ���preΪcurr  
        cur = next;  // ���µ�ǰ���curΪnext  
    }
    return pre;  // �������һ�θ��º�pre����λ�ã���ԭ��β��㣩��Ϊ��ͷ���  
}

// ָ�뷨������װ
void pointerReverse(List head) {
    // �������Ϊ�գ���������head
    if (isNULL(head)) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return;
    }
    else if (isNULL(head->next)) {
        fprintf(stderr, "EmptyListException! Try again!\n");
        return;
    }
    List pointerHead = head->next;
    head->next = pointer(pointerHead);
}
