#define UPKEY 72//�����ϼ��ĵڶ���ֵ
#define DOWNKEY 80//�����¼��ĵڶ���ֵ, ���ߵ�һ��ֵ����ͬ��
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "DoublyLinkedListADT.h"
char Path[200];
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
void gotoXY(int x, int y);//�ƶ����ĺ���
void Operation();

void Menu()
{
    printf("                                 ��ӭʦ������˫���������ϵͳ                              \n");
    printf("*******************************************************************************************\n");
    printf("*                0) �½�һ���յ�˫������                                                  *\n");
    printf("*                1) ��˫������ĩβ���ӽڵ�                                                *\n");
    printf("*                2) ��˫������ͷ�����ӽڵ�                                                *\n");
    printf("*                3) ɾ��˫������β���Ľڵ�                                                *\n");
    printf("*                4) ɾ��˫������ͷ���Ľڵ�                                                *\n");
    printf("*                5) �����ӡ˫���������������                                            *\n");    
    printf("*                6) �ҵ�˫��������е㲢�������                                          *\n");
    printf("*                7) �ж������Ƿ�ɻ�                                                      *\n");
    printf("*                8) ��ȫ��ղ�ɾ��˫����                                                  *\n");
    printf("*                9) �˳�����                                                              *\n");
    printf("*******************************************************************************************\n");
    printf("   ��ʹ�á�������enter��ʵ��ѡ���ִ�������������ÿ������ǰ��Ĵ�����ִ������<0 - 9>    \n");
    printf("                     �ڲ˵���ҳ����δ�����˵�ʱ����'q'��'Q'�˳�����\n");
    printf("               ��ϵͳ˫������ͷβ�ڵ���洢���ݣ�����ά��ͷβ����ַΪ�������Ż�");
    return;
}
void cursorUpdate1(int x)// ���²˵���ĳһ�еĺ���
{
    switch (x)
    {
    case 0:
        printf("*                0) �½�һ���յ�˫������                                                  *\n");
        break;
    case 1:
        printf("*                1) ��˫������ĩβ���ӽڵ�                                                *\n");
        break;
    case 2:
        printf("*                2) ��˫������ͷ�����ӽڵ�                                                *\n");
        break;
    case 3:
        printf("*                3) ɾ��˫������β���Ľڵ�                                                *\n");
        break;
    case 4:
        printf("*                4) ɾ��˫������ͷ���Ľڵ�                                                *\n");
        break;
    case 5:
        printf("*                5) �����ӡ˫���������������                                            *\n");
        break;
    case 6:
        printf("*                6) �ҵ�˫��������е㲢�������                                          *\n");
        break;
    case 7:
        printf("*                7) �ж������Ƿ�ɻ�                                                      *\n");
        break;
    case 8:
        printf("*                8) ��ȫ��ղ�ɾ��˫����                                                  *\n");
        break;
    case 9:
        printf("*                9) �˳�����                                                              *\n");
        break;
    }
    return;
}
void gotoXY(int x, int y) // �ƶ����ĺ���
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
    (*P)(int)������ָ�룬ѡ���ĸ����ǲ˵�����ֻ����cursorUpdate1һ��
    */
    char c1, c2;
    gotoXY(0, line);
    do
    {
        c2 = _getch();
        if (c2 == DOWNKEY)
        {
            gotoXY(0, line);
            IN_DEFAULT; //ѡ��Ĭ��ɫ
            (*p)(line - deta); //���ǣ�ʵ����ѡ
            if (line == upper) //����Ѿ������Ͻ磬�򷵻��½磬ʵ�ֹ�������
                line = lower;
            else
                ++line; //
            gotoXY(0, line);
            IN_CYAN; // ѡ����ɫ
            (*p)(line - deta);
        }
        if (c2 == UPKEY)
        {
            gotoXY(0, line);
            IN_DEFAULT;
            (*p)(line - deta);
            if (line == lower)
                line = upper;
            else
                --line;
            gotoXY(0, line);
            IN_CYAN;
            (*p)(line - deta);
        }
    } while ((c1 = _getch()) != '\r');
    gotoXY(0, line);
    (*p)(line - deta);
    IN_DEFAULT;
    return line - deta;
}

void Operation() {
    List* orginList = NULL;
    int n = 0, line = 2; // ��Ӧmenu()��0)
    char c1;
    IN_DEFAULT;
    while (1)
    {
        memset(Path, '\0', sizeof(char) * 199);
        system("cls");
        Menu();
        gotoXY(0, 16);
        if ((c1 = _getch()) == -32) {//��VS����������Ҫ�������е�_getch�ĳ�getch

            n = cursorOperate(line, 2, 2, 11, cursorUpdate1);//���¼�����
        }
        else if (c1 == '\0')continue;
        else if (c1 >= '0' && c1 <= '9') {//�������ֱ�Ų���
            char tmp = c1;
            putchar(tmp);
            puts("");
            n = tmp - '0';
        }
        else if (c1 == 'q' || c1 == 'Q') {//�����������
            gotoXY(0, 17);//�ù�굽���ʵĵط����
            putchar(c1);
            puts("");
            system("pause");
            printf("Here is end of run.\n");
        
        }
        else {//�����������
            puts("�������");
            system("pause");
            continue;
        }
        switch (n) {
        case 0: {
            gotoXY(0, 17);// ��ʼ������
            if (orginList == NULL) initList(&orginList);
            else puts("You have already created a doublylinkedlist");
            system("pause");
            break;    
        }
        case 1: {
            gotoXY(0, 17);
            Item enterData = 0;//�����ڵ�
            puts("Please enter intger,otherwise function will quit:");
            while (scanf("%9d", &enterData.data))
            {
                addAtTail(orginList, enterData);
            }
            fflush(stdin);
            rewind(stdin);
            system("pause");
            break;
        }
        case 2: {//
            gotoXY(0, 17);
            Item enterData = 0;//�����ڵ�
            puts("Please enter intger,otherwise function will quit:");
            while (scanf("%9d", &enterData.data))
            {
                addAtHead(orginList, enterData);
            }
            fflush(stdin);
            rewind(stdin);
            system("pause");
            break;
        }
        case 3: {
            gotoXY(0, 17);// ɾβ���
            deleteAtTail(orginList);
            system("pause");
            break;
        }
        case 4: {
            gotoXY(0, 17);// ɾͷ���
            deleteAtHead(orginList);
            system("pause");
            break;
        }
        case 5: {
            gotoXY(0, 17);
            printList(orginList);//��ӡ����
            system("pause");
            fflush(stdin);
            rewind(stdin);
            break;
        }
        case 6: {
            gotoXY(0, 17);
            Node* tempNode;
            if ((tempNode = findMiddle(orginList)) != NULL) {//�����е�
                puts("Successfully Finding");
                printf("Data is %d\n", tempNode->item.data);
            }
            else puts("Failing to find");
            system("pause");
            break;
        }
        case 7: {
            gotoXY(0, 17);
            if (!hasCycle(orginList)) {//�ж��Ƿ��л�
                puts("Did'n find cycle");
            }
            else puts("Successfully finding a cycle");
            system("pause");
            break;
        }
        case 8: {
            gotoXY(0, 17);//�������
            deleteList(&orginList);
           
            system("pause");
            break;
        }
        case 9: {//
            gotoXY(0, 17);//�ù�굽���ʵĵط����
            puts("ʦ���ټ����´�����");
            system("pause");
            exit(0);
        }
        }
    }
    system("pause");
}
