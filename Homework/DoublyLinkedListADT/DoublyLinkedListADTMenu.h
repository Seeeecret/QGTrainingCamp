#define UPKEY 72//�����ϼ��ĵڶ���ֵ
#define DOWNKEY 80//�����¼��ĵڶ���ֵ, ���ߵ�һ��ֵ����ͬ��
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
void CursorPos1(int x);//������ʾ���ֵĴ�ӡ����
int CursorOpr(int line, int deta, int lower, int upper, void (*p)(int));//�����������¼��ĺ���
void Gotoxy(int x, int y);//�ƶ����ĺ���
void Operation();

void Menu()
{
    printf("                                  ��ӭʦ������˫���������ϵͳ                               \n");
    printf("*******************************************************************************************\n");
    printf("*                0) �½�һ���յ�˫������                                              *\n");
    printf("*                1) ��˫������ĩβ���ӽڵ�                                                *\n");
    printf("*                2) ��˫������ͷ�����ӽڵ�                                         *\n");
    printf("*                3) ɾ��˫������β���Ľڵ�                                           *\n");
    printf("*                4) ɾ��˫������ͷ���Ľڵ�                                                            *\n");
    printf("*                5) �����ӡ˫���������������                                                        *\n");    
    printf("*                6) �ҵ���������е㲢�������                                            *\n");
    printf("*                7) �ж������Ƿ�ɻ�                                                      *\n");
    printf("*                8) ɾ��ָ��                                                        *\n");
    printf("*                9) ָ�뷨��ת����                                                        *\n");
    printf("*                A) ��ȫ��ղ�ɾ��������                                                  *\n");
    printf("*                B) �˳�����                                                              *\n");
    printf("*******************************************************************************************\n");
    printf("��ʹ�á�������enter��ʵ��ѡ���ִ�������������ÿ������ǰ��Ĵ�����ִ������<0 - 9><A - B>\n");
    printf("                     �ڲ˵���ҳ����δ�����˵�ʱ����'q'��'Q'�˳�����\n");
    printf("                     ��ϵͳ������ͷ�����ã��ӵڶ����ڵ㿪ʼ�洢����");
    return;
}
void CursorPos1(int x)
{
    switch (x)
    {
    case 0:
        printf("*                0) �½�һ����ͷָ�뵥����                                                *\n");
        break;
    case 1:
        printf("*                1) ��������ĩβ�����ӽڵ�                                                *\n");
        break;
    case 2:
        printf("*                2) ���������ָ��λ�ô�����ڵ�                                          *\n");
        break;
    case 3:
        printf("*                3) ɾ��������ָ��λ�ô��Ľڵ�                                            *\n");
        break;
    case 4:
        printf("*                4) ��ӡ������                                                            *\n");
        break;
    case 5:
        printf("*                5) ��������ż����                                                        *\n");
        break;
    case 6:
        printf("*                6) �ҵ���������е㲢�������                                            *\n");
        break;
    case 7:
        printf("*                7) �ж������Ƿ�ɻ�                                                      *\n");
        break;
    case 8:
        printf("*                8) �ݹ鷨��ת����                                                        *\n");
        break;
    case 9:
        printf("*                9) ָ�뷨��ת����                                                        *\n");
        break;
    case 10:
        printf("*                A) ��ȫ��ղ�ɾ��������                                                  *\n");
        break;
    case 11:
        printf("*                B) �˳�����                                                              *\n");
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

int CursorOpr(int line, int deta, int lower, int upper, void (*p)(int))
{
    /*
    line����ǰ�����������
    deta��������˵�ѡ��Ĳ�ֵ��������main�˵���ѡ��(0)�ڵ�2��(������0��ʼ����)������deta����2����2 - 0
    upper, lower��ѡ������½�
    (*P)(int)������ָ�룬ѡ���ĸ����ǲ˵�
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
            (*p)(line - deta); //���ǣ�ʵ����ѡ
            if (line == upper) //����Ѿ������Ͻ磬�򷵻��½磬ʵ�ֹ�������
                line = lower;
            else
                ++line; //
            Gotoxy(0, line);
            IN_CYAN;
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
    List orginList = NULL;
    int n = 0, line = 2; // ��Ӧmenu()��0)
    char c1;
    IN_DEFAULT;
    while (1)
    {
        memset(Path, '\0', sizeof(char) * 199);
        system("cls");
        Menu();
        Gotoxy(0, 18);
        if ((c1 = _getch()) == -32) {//��VS����������Ҫ�������е�_getch�ĳ�getch

            n = CursorOpr(line, 2, 2, 13, CursorPos1);//���¼�����
        }
        else if (c1 == '\0')continue;
        else if (c1 >= '0' && c1 <= '9') {//�������ֱ�Ų���
            char tmp = c1;
            putchar(tmp);
            puts("");
            n = tmp - '0';
        }
        else if (c1 == 'q' || c1 == 'Q') {//�����������
            Gotoxy(0, 19);//�ù�굽���ʵĵط����
            putchar(c1);
            puts("");
            system("pause");
            printf("Here is end of run.\n");
        }
        else if (c1 == 'a' || c1 == 'A') {//�������
            Gotoxy(0, 19);
            putchar(c1);
            puts("");
            deleteList(&orginList);
            puts("All datas have already been cleaned.");
            system("pause");
            continue;
        }
        else if (c1 == 'b' || c1 == 'B') {//�˳�
            Gotoxy(0, 19);
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
            Gotoxy(0, 19);//
            if (orginList == NULL) orginList = createEmptyList();
            else puts("You have already created a singlylinkedlist");
            system("pause");
            break;    
        }
        case 1: {
            Gotoxy(0, 19);
            Item enterData;//�����ڵ�
            puts("Please enter intger,otherwise function will quit:");
            while (scanf("%9d", &enterData.data))
            {
                addNewNode(orginList, enterData);
            }
            fflush(stdin);
            rewind(stdin);
            system("pause");
            break;
        }
        case 2: {//
            Gotoxy(0, 19);
            Item enterData2;//����ڵ�
            int index = 0;
            puts("Please enter in format:\n \"INDEX DATA\"");
            if (scanf("%9d %9d", &index, &enterData2.data) == 2) insertNewNode(orginList, index, enterData2);
            system("pause");
            break;
        }
        case 3: {
            Gotoxy(0, 19);
            int index = 0;
            puts("Please enter the index:");//ɾ���ڵ�
            if (scanf("%9d", &index) == 1 && deleteNode(orginList, index)) puts("Successfully Deleting");
            else puts("Failing to delete");
            system("pause");
            break;
        }
        case 4: {
            Gotoxy(0, 19);
            printList(orginList);//��ӡ����
            system("pause");
            fflush(stdin);
            rewind(stdin);
            break;
        }
        case 5: {
            Gotoxy(0, 19);
            swapEvenNodeOddNode(orginList);//��ż����
            system("pause");
            break;
        }
        case 6: {
            Gotoxy(0, 19);
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
            Gotoxy(0, 19);
            if (!hasCycle(orginList)) {
                puts("Did'n find cycle");
            }
            else puts("Successfully finding a cycle");
            system("pause");
            break;
        }
        case 8: {
            Gotoxy(0, 19);
            recursiveReverse(orginList);//�ݹ鷴ת
            system("pause");
            break;
        }
        case 9: {//
            Gotoxy(0, 19);
            pointerReverse(orginList);//ָ�뷴ת
            system("pause");
            break;
        }
        case 10: {//�����������
            Gotoxy(0, 19);
            deleteList(&orginList);
            puts("All datas have already been cleaned.");
            system("pause");
            break;
        }
        case 11: {
            Gotoxy(0, 19);//�ù�굽���ʵĵط����
            puts("ʦ���ټ����´�����");
            system("pause");
            exit(0);
        }
        }
    }
    system("pause");
}
