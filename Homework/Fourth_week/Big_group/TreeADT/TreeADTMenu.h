#define _CRT_SECURE_NO_WARNINGS
#define UPKEY 72//�����ϼ��ĵڶ���ֵ
#define DOWNKEY 80//�����¼��ĵڶ���ֵ, ���ߵ�һ��ֵ����ͬ��
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "TreeADT.h"
#define IN_CYAN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                        BACKGROUND_GREEN |               \
                                            BACKGROUND_BLUE |            \
                                            BACKGROUND_INTENSITY)//��������˵����ݱ�����ɫ�ĺ궨��: ����ɫ
#define IN_DEFAULT SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                           FOREGROUND_RED |                 \
                                               FOREGROUND_GREEN |           \
                                               FOREGROUND_BLUE)//��������˵����ݱ�����ɫ�ĺ궨��: Ĭ��
void Menu();//�˵�����
void cursorUpdate1(int x);//������ʾ���ֵĴ�ӡ����
int cursorOperate(int line, int deta, int lower, int upper, void (*p)(int));//�����������¼��ĺ���
void Gotoxy(int x, int y);//�ƶ����ĺ���
void Operation();

void Menu()
{
    printf("                              ��ӭʦ�������������������ϵͳ                               \n");
    printf("*******************************************************************************************\n");
    printf("*                0) �½�����ʼ��һ���յĶ��������                                        *\n");
    printf("*                1) ����һ������, �����������������                                      *\n");
    printf("*                2) ����һ������, �����ж����������ɾ��                                  *\n");
    printf("*                3) ����һ������, ��ѯ���ڶ�����������Ƿ����                            *\n");
    printf("*                4) �Ե�ǰ�Ķ��������еݹ���ǰ�����                                    *\n");
    printf("*                5) �Ե�ǰ�Ķ��������е������ǰ�����                                    *\n");
    printf("*                6) �Ե�ǰ�Ķ��������еݹ����������                                    *\n");
    printf("*                7) �Ե�ǰ�Ķ��������е�������������                                    *\n");
    printf("*                8) �Ե�ǰ�Ķ��������еݹ��ĺ������                                    *\n");
    printf("*                9) �Ե�ǰ�Ķ��������е�����ĺ������                                    *\n");
    printf("*                A) �Ե�ǰ�Ķ��������в������                                            *\n");
    printf("*                B) ��ղ�ɾ���������������������                                        *\n");
    printf("*                C) �˳�����                                                              *\n");
    printf("*******************************************************************************************\n");
    printf("��ʹ�á�������enter��ʵ��ѡ���ִ�������������ÿ������ǰ��Ĵ�����ִ������<0 - 9><A - C>\n");
    printf("     �ڲ˵���ҳ����δ�����˵�ʱ����'q'��'Q'�˳�����,��ϵͳ��ӡ����ʱ�����ӡǰ50��Ԫ��     \n");
    printf("    �ļ�����ʱ������ϵͳ�������ļ����鳤�Ȳ�ƥ�䣬��ᵼ�¶���ʧ�ܻ��ļ����鲻��ȫ���롣   \n");
    return;
}
void cursorUpdate1(int x) {
    switch (x)
    {
    case 0:
        printf("*                0) �½�����ʼ��һ���յĶ��������                                        *\n");
        break;
    case 1:
        printf("*                1) ����һ������, �����������������                                      *\n");
        break;
    case 2:
        printf("*                2) ����һ������, �����ж����������ɾ��                                  *\n");
        break;
    case 3:
        printf("*                3) ����һ������, ��ѯ���ڶ�����������Ƿ����                            *\n");
        break;
    case 4:
        printf("*                4) �Ե�ǰ�Ķ��������еݹ���ǰ�����                                    *\n");
        break;
    case 5:
        printf("*                5) �Ե�ǰ�Ķ��������е������ǰ�����                                    *\n");
        break;
    case 6:
        printf("*                6) �Ե�ǰ�Ķ��������еݹ����������                                    *\n");
        break;
    case 7:
        printf("*                7) �Ե�ǰ�Ķ��������е�������������                                    *\n");
        break;
    case 8:
        printf("*                8) �Ե�ǰ�Ķ��������еݹ��ĺ������                                    *\n");
        break;
    case 9:
        printf("*                9) �Ե�ǰ�Ķ��������е�����ĺ������                                    *\n");
        break;
    case 10:
        printf("*                A) �Ե�ǰ�Ķ��������в������                                            *\n");
        break;
    case 11:
        printf("*                B) ��ղ�ɾ���������������������                                        *\n");
        break;
    case 12:
        printf("*                C) �˳�����                                                              *\n");
        break;
    }
    return;
}
void Gotoxy(int x, int y)
{
    COORD pos = { x, y };
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout, pos);
    return;
}
int cursorOperate(int line, int deta, int lower, int upper, void (*p)(int))
{
    /*
    line����ǰ�����������
    deta��������˵�ѡ��Ĳ�ֵ��������main�˵���ѡ��(0)�ڵ�2��(������0��ʼ����)������deta����2����2 - 0
    upper, lower��ѡ������½�
    (*P)(int)������ָ�룬ѡ���ĸ����ǲ˵���ֻʵ����cursorUpdate1һ��
    */
    char c1, c2;
    Gotoxy(0, line);
    do
    {
        c2 = _getch();
        if (c2 == DOWNKEY)
        {
            Gotoxy(0, line);
            IN_DEFAULT; //ѡ��Ĭ��ɫ
            (*p)(line - deta); //���ǣ�ʵ����ѡ(ʵ���Ͼ��Ǵ�ӡ)
            if (line == upper) //����Ѿ������Ͻ磬�򷵻��½磬ʵ�ֹ�������
                line = lower;
            else
                ++line; //
            Gotoxy(0, line);
            IN_CYAN; // ѡ����ɫ
            (*p)(line - deta);
        }
        if (c2 == UPKEY)
        {
            Gotoxy(0, line);
            IN_DEFAULT;
            (*p)(line - deta);
            if (line == lower)
                line = upper;
            else
                --line;
            Gotoxy(0, line);
            IN_CYAN;
            (*p)(line - deta);
        }
    } while ((c1 = _getch()) != '\r');
    Gotoxy(0, line);
    (*p)(line - deta);
    IN_DEFAULT;
    return line - deta;
}
void Operation() {
    int n = 0, line = 2; // ��Ӧmenu()��0)
    char c1;
    IN_DEFAULT;
    Tree* tree = NULL;
    while (1) {
        system("cls");
        Menu();
        Gotoxy(0, 19);
        if ((c1 = _getch()) == -32) {//��VS����������Ҫ�������е�_getch�ĳ�getch

            n = cursorOperate(line, 2, 2, 14, cursorUpdate1);//���¼�����
        }
        else if (c1 == '\0')continue;
        else if (c1 >= '0' && c1 <= '9') {//�������ֱ�Ų���
            char tmp = c1;
            putchar(tmp);
            puts("");
            n = tmp - '0';
        }
        else if (c1 == 'q' || c1 == 'Q') {//�����������
            Gotoxy(0, 21);//�ù�굽���ʵĵط����
            putchar(c1);
            puts("");
            printf("ʦ���ټ�\n");
            system("pause");
            exit(0);
        }
        else if (c1 == 'a' || c1 == 'A') {//�������
            Gotoxy(0, 20);
            putchar(c1);
            puts("");
            traverseCell(tree, levelOrder);
            system("pause");
            continue;
        }
        else if (c1 == 'b' || c1 == 'B') {
            Gotoxy(0, 20);
            putchar(c1);
            puts("");
            deleteTree(tree);
            system("pause");
            continue;
        }
        else if (c1 == 'c' || c1 == 'C') {//�˳�
            Gotoxy(0, 20);
            putchar(c1);
            puts("");
            puts("ʦ���ټ����´�����");
            system("pause");
            exit(0);
        }
        else {//�����������
            puts("�������");
            system("pause");
            continue;
        }
        switch (n) {
        case 0: {
            Gotoxy(0, 20);
            initTree(&tree);
            /*if (isNULL(tree)) {
                initTree(tree);
            }
            else {
                fprintf(stderr, "ExisitingTreeException! You have already create a tree.\n");
            }*/
            system("pause");
            break;
        }
        case 1: {
            Gotoxy(0, 20);
            int value = 0;
            puts("Please enter a integer, otherwise function will quit:");
            while (scanf("%9d", &value)&& insertNode(tree, value))
            {
                puts("New Node added!");
            }
            fflush(stdin);
            rewind(stdin);
            system("pause");
            break;
        }
        case 2: {
            Gotoxy(0, 20);
            int value = 0;
            puts("Please enter a integer, otherwise function will quit:");
            if (scanf("%9d", &value)&& deleteNode(tree, value)) {
                printf("Successfully delete the node!\n");
            }
            else {
                printf("Failing to delete the node!\n");
            }
            fflush(stdin);
            rewind(stdin);
            system("pause");
            break;
        }
        case 3: {
            Gotoxy(0, 20);
            int value = 0;
            puts("Please enter a integer, otherwise function will quit:");
            if (scanf("%9d", &value)&&!isNULL(searchNode(tree,value))) {
                printf("Successfully find the node!\n");
            }
            else {
                printf("Failing to find the node!\n");
			}
            fflush(stdin);
            rewind(stdin);
            system("pause");
            break;
        }
        case 4: {
            Gotoxy(0, 20);
            traverseCell(tree, preOrderRecursive);
            system("pause");
            break;
        }
        case 5: {
            Gotoxy(0, 20);
            traverseCell(tree, preOrderIterative);
            system("pause");
            break;
        }
        case 6: {
            Gotoxy(0, 20);
            traverseCell(tree, inOrderRecursive);
            system("pause");
            break;
        }
        case 7: {
            Gotoxy(0, 20);
            traverseCell(tree, inOrderIterative);
            system("pause");
            break;

        }
        case 8: {
            Gotoxy(0, 20);
            traverseCell(tree, postOrderRecursive);

            system("pause");
            break;

        }
        case 9: {
            Gotoxy(0, 20);
            traverseCell(tree, postOrderIterative);
            system("pause");
            break;

        }
        case 10: {
            Gotoxy(0, 20);
            traverseCell(tree, levelOrder);
            system("pause");
            break;

        }
        case 11: {
            Gotoxy(0, 20);
            deleteTree(tree);
            tree = NULL;
            break;
        }
        case 12: {
            Gotoxy(0, 20);
            puts("ʦ���ټ����´�����");
            system("pause");
            exit(0);
        }
        }
    }
}