
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
} Item; //����Ԫ�ر���
typedef struct Node {
    Item item;
    struct Node* next;
    struct Node* prev;
} Node;// ����������

typedef struct List {
    Node* head;
    Node* tail;
} List;// ���������������洢����ṹͷ����β���ĵ�ַ

Node* createNode(Item newItem) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->item = newItem;
    node->prev = NULL;
    node->next = NULL;
    return node; //����һ���µĽڵ㣬��װ���˺���
}

void initList(List** list) {// ��ʼ������
    (* list) = (List*)malloc(sizeof(List));
    (* list)->head = NULL;
    (* list)->tail = NULL;
}

int getListLength(List* list) {//�������ļ�������
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
    else if (list->head == NULL) { // �������Ϊ��
        list->head = newNode;
        list->tail = newNode;
    }
    else {
        newNode->next = list->head;// ����ͷ���ĵ�ַ
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
    else if (list->tail == NULL) {  // �������Ϊ��
        list->head = newNode;
        list->tail = newNode;
       
    }
    else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;  // ����β���ĵ�ַ
    }
    puts("New node added! Enter something except integer to quit!");
    return;
}

void deleteAtHead(List* list) {//ɾ��ͷ���
    if (list == NULL) {
        fprintf(stderr, "NullPointerException! Enter something except integer to quit!\n");
        fflush(stdin);
        rewind(stdin);
        return;
    }
    else if (list->head == NULL) { // ����Ϊ�գ�ֱ�ӷ���
        fprintf(stderr, "EmptyListException! Try again!\n");
        return;
    }
    Node* oldHead = list->head;
    list->head = oldHead->next;//����ͷ���
    if (list->head != NULL) { // �µ�ͷ�ڵ㲻Ϊ�գ�����ǰ���ڵ�ָ��
        list->head->prev = NULL;
    }
    else { // �������ֻ��һ���ڵ㣬ͬʱɾ��β�ڵ�
        list->tail = NULL;
    }
    puts("Node was deleted!");
    free(oldHead);
    return;
}

Node* findMiddle(List* list) {
    // �������Ϊ�գ�����
    if (list == NULL) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return NULL;
    }
    else if (list->head == NULL) {
        fprintf(stderr, "EmptyListException! Try again!\n");
        return NULL;
    }
    else if (list->head->next == NULL) return list->head;
    // �������ָ�벢��ʼ��Ϊͷ�ڵ�
    Node* fast = list->head;
    Node* slow = list->head;
    // ѭ�����������ÿ�ָ��ÿ������������ָ��ÿ����һ��
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next; // ��ָ��������
        slow = slow->next; // ��ָ����һ��
    }
    // ����ָ���ߵ�β��ʱ����ָ������м�ڵ�
    return slow;
}

bool hasCycle(List* list) {//�ж��Ƿ��л�

    // �������Ϊ�գ���������false
    if (list == NULL) {
        fprintf(stderr, "NullPointerException! Try again!\n");
        return false;
    }
    else if (list->head == NULL) {
        fprintf(stderr, "EmptyListException! Try again!\n");
        return false;
    }
        // �������ָ�벢��ʼ��Ϊͷ�ڵ�
        Node* fast = list->head;
        Node* slow = list->head;

        // ѭ�����������ÿ�ָ��ÿ������������ָ��ÿ����һ��
        while (fast != NULL && fast->next != NULL) {
            fast = fast->next->next; // ��ָ��������
            slow = slow->next; // ��ָ����һ��
            // �������ָ�������ˣ�˵���л�
            if (fast == slow) {
                return true;
            }
        }
        return false;
}


void deleteAtTail(List* list) {//������bug������
    if (list == NULL) {
        fprintf(stderr, "NullPointerException! Enter something except integer to quit!\n");
        fflush(stdin);
        rewind(stdin);
        return;
    }
    else if (list->tail == NULL) {  // �������Ϊ��
        fprintf(stderr, "EmptyListException! Try again!\n");
        return;
    }
    Node* temp = list->tail;
    if (temp->prev == NULL) {  // ���������ֻ��һ���ڵ�
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


void printList(List* list) {//��ӡ��������
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


void deleteList(List** list) {//�������
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

