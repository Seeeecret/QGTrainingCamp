#define UPKEY 72//键入上键的第二个值
#define DOWNKEY 80//键入下键的第二个值, 二者第一个值是相同的
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
                                            BACKGROUND_INTENSITY)//更改输出菜单内容背景颜色的宏定义: 天蓝色
#define IN_DEFAULT SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                           FOREGROUND_RED |                 \
                                               FOREGROUND_GREEN |           \
                                               FOREGROUND_BLUE)//更改输出菜单内容背景颜色的宏定义: 默认
void Menu();//菜单函数
void CursorPos1(int x);//高亮显示部分的打印函数
int CursorOpr(int line, int deta, int lower, int upper, void (*p)(int));//处理键入的上下键的函数
void Gotoxy(int x, int y);//移动光标的函数
void Operation();

void Menu()
{
    printf("                                  欢迎师兄来到双向链表测试系统                               \n");
    printf("*******************************************************************************************\n");
    printf("*                0) 新建一个空的双向链表                                              *\n");
    printf("*                1) 往双向链表末尾增加节点                                                *\n");
    printf("*                2) 往双向链表头部增加节点                                         *\n");
    printf("*                3) 删除双向链表尾部的节点                                           *\n");
    printf("*                4) 删除双向链表头部的节点                                                            *\n");
    printf("*                5) 输出打印双向链表的所有数据                                                        *\n");    
    printf("*                6) 找到单链表的中点并输出数据                                            *\n");
    printf("*                7) 判断链表是否成环                                                      *\n");
    printf("*                8) 删除指定                                                        *\n");
    printf("*                9) 指针法反转链表                                                        *\n");
    printf("*                A) 完全清空并删除单链表                                                  *\n");
    printf("*                B) 退出程序                                                              *\n");
    printf("*******************************************************************************************\n");
    printf("请使用↑、↓和enter来实现选择和执行命令，或者输入每个命令前面的代号来执行命令<0 - 9><A - B>\n");
    printf("                     在菜单主页面且未操作菜单时键入'q'或'Q'退出程序\n");
    printf("                     本系统单链表头结点空置，从第二个节点开始存储数据");
    return;
}
void CursorPos1(int x)
{
    switch (x)
    {
    case 0:
        printf("*                0) 新建一个空头指针单链表                                                *\n");
        break;
    case 1:
        printf("*                1) 往单链表末尾中增加节点                                                *\n");
        break;
    case 2:
        printf("*                2) 往单链表的指定位置处插入节点                                          *\n");
        break;
    case 3:
        printf("*                3) 删除单链表指定位置处的节点                                            *\n");
        break;
    case 4:
        printf("*                4) 打印单链表                                                            *\n");
        break;
    case 5:
        printf("*                5) 单链表奇偶调换                                                        *\n");
        break;
    case 6:
        printf("*                6) 找到单链表的中点并输出数据                                            *\n");
        break;
    case 7:
        printf("*                7) 判断链表是否成环                                                      *\n");
        break;
    case 8:
        printf("*                8) 递归法反转链表                                                        *\n");
        break;
    case 9:
        printf("*                9) 指针法反转链表                                                        *\n");
        break;
    case 10:
        printf("*                A) 完全清空并删除单链表                                                  *\n");
        break;
    case 11:
        printf("*                B) 退出程序                                                              *\n");
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
    line：当前光标所在行数
    deta：行数与菜单选项的差值。比如在main菜单中选项(0)在第2行(行数从0开始计算)，所以deta等于2，即2 - 0
    upper, lower：选项的上下界
    (*P)(int)：函数指针，选择哪个覆盖菜单
    */
    char c1, c2;
    Gotoxy(0, line);
    do
    {
        c2 = _getch();
        if (c2 == DOWNKEY)
        {
            Gotoxy(0, line);
            IN_DEFAULT; //选择默认色
            (*p)(line - deta); //覆盖，实现退选
            if (line == upper) //如果已经到了上界，则返回下界，实现滚动高亮
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
    int n = 0, line = 2; // 对应menu()的0)
    char c1;
    IN_DEFAULT;
    while (1)
    {
        memset(Path, '\0', sizeof(char) * 199);
        system("cls");
        Menu();
        Gotoxy(0, 18);
        if ((c1 = _getch()) == -32) {//非VS环境运行需要将代码中的_getch改成getch

            n = CursorOpr(line, 2, 2, 13, CursorPos1);//上下键操作
        }
        else if (c1 == '\0')continue;
        else if (c1 >= '0' && c1 <= '9') {//输入数字编号操作
            char tmp = c1;
            putchar(tmp);
            puts("");
            n = tmp - '0';
        }
        else if (c1 == 'q' || c1 == 'Q') {//处理键入数据
            Gotoxy(0, 19);//让光标到合适的地方输出
            putchar(c1);
            puts("");
            system("pause");
            printf("Here is end of run.\n");
        }
        else if (c1 == 'a' || c1 == 'A') {//清空链表
            Gotoxy(0, 19);
            putchar(c1);
            puts("");
            deleteList(&orginList);
            puts("All datas have already been cleaned.");
            system("pause");
            continue;
        }
        else if (c1 == 'b' || c1 == 'B') {//退出
            Gotoxy(0, 19);
            putchar(c1);
            puts("");
            puts("师兄再见，下次再来");
            system("pause");
            exit(0);
        }
        else {//处理键入数据
            puts("输入错误");
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
            Item enterData;//新增节点
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
            Item enterData2;//插入节点
            int index = 0;
            puts("Please enter in format:\n \"INDEX DATA\"");
            if (scanf("%9d %9d", &index, &enterData2.data) == 2) insertNewNode(orginList, index, enterData2);
            system("pause");
            break;
        }
        case 3: {
            Gotoxy(0, 19);
            int index = 0;
            puts("Please enter the index:");//删除节点
            if (scanf("%9d", &index) == 1 && deleteNode(orginList, index)) puts("Successfully Deleting");
            else puts("Failing to delete");
            system("pause");
            break;
        }
        case 4: {
            Gotoxy(0, 19);
            printList(orginList);//打印链表
            system("pause");
            fflush(stdin);
            rewind(stdin);
            break;
        }
        case 5: {
            Gotoxy(0, 19);
            swapEvenNodeOddNode(orginList);//奇偶交换
            system("pause");
            break;
        }
        case 6: {
            Gotoxy(0, 19);
            Node* tempNode;
            if ((tempNode = findMiddle(orginList)) != NULL) {//查找中点
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
            recursiveReverse(orginList);//递归反转
            system("pause");
            break;
        }
        case 9: {//
            Gotoxy(0, 19);
            pointerReverse(orginList);//指针反转
            system("pause");
            break;
        }
        case 10: {//清空链表数据
            Gotoxy(0, 19);
            deleteList(&orginList);
            puts("All datas have already been cleaned.");
            system("pause");
            break;
        }
        case 11: {
            Gotoxy(0, 19);//让光标到合适的地方输出
            puts("师兄再见，下次再来");
            system("pause");
            exit(0);
        }
        }
    }
    system("pause");
}
