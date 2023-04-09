#define _CRT_SECURE_NO_WARNINGS
#define UPKEY 72//键入上键的第二个值
#define DOWNKEY 80//键入下键的第二个值, 二者第一个值是相同的
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
                                            BACKGROUND_INTENSITY)//更改输出菜单内容背景颜色的宏定义: 天蓝色
#define IN_DEFAULT SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                           FOREGROUND_RED |                 \
                                               FOREGROUND_GREEN |           \
                                               FOREGROUND_BLUE)//更改输出菜单内容背景颜色的宏定义: 默认
void Menu();//菜单函数
void cursorUpdate1(int x);//高亮显示部分的打印函数
int cursorOperate(int line, int deta, int lower, int upper, void (*p)(int));//处理键入的上下键的函数
void Gotoxy(int x, int y);//移动光标的函数
void Operation();

void Menu()
{
    printf("                              欢迎师兄来到二叉查找树测试系统                               \n");
    printf("*******************************************************************************************\n");
    printf("*                0) 新建并初始化一个空的二叉查找树                                        *\n");
    printf("*                1) 输入一个整数, 插入至二叉查找树中                                      *\n");
    printf("*                2) 输入一个整数, 将其中二叉查找树中删除                                  *\n");
    printf("*                3) 输入一个整数, 查询其在二叉查找树中是否存在                            *\n");
    printf("*                4) 对当前的二叉树进行递归版的前序遍历                                    *\n");
    printf("*                5) 对当前的二叉树进行迭代版的前序遍历                                    *\n");
    printf("*                6) 对当前的二叉树进行递归版的中序遍历                                    *\n");
    printf("*                7) 对当前的二叉树进行迭代版的中序遍历                                    *\n");
    printf("*                8) 对当前的二叉树进行递归版的后序遍历                                    *\n");
    printf("*                9) 对当前的二叉树进行迭代版的后序遍历                                    *\n");
    printf("*                A) 对当前的二叉树进行层序遍历                                            *\n");
    printf("*                B) 清空并删除二叉查找树和其中数据                                        *\n");
    printf("*                C) 退出程序                                                              *\n");
    printf("*******************************************************************************************\n");
    printf("请使用↑、↓和enter来实现选择和执行命令，或者输入每个命令前面的代号来执行命令<0 - 9><A - C>\n");
    printf("     在菜单主页面且未操作菜单时键入'q'或'Q'退出程序,本系统打印数组时仅会打印前50个元素     \n");
    printf("    文件读入时若存在系统数组与文件数组长度不匹配，则会导致读入失败或文件数组不完全读入。   \n");
    return;
}
void cursorUpdate1(int x) {
    switch (x)
    {
    case 0:
        printf("*                0) 新建并初始化一个空的二叉查找树                                        *\n");
        break;
    case 1:
        printf("*                1) 输入一个整数, 插入至二叉查找树中                                      *\n");
        break;
    case 2:
        printf("*                2) 输入一个整数, 将其中二叉查找树中删除                                  *\n");
        break;
    case 3:
        printf("*                3) 输入一个整数, 查询其在二叉查找树中是否存在                            *\n");
        break;
    case 4:
        printf("*                4) 对当前的二叉树进行递归版的前序遍历                                    *\n");
        break;
    case 5:
        printf("*                5) 对当前的二叉树进行迭代版的前序遍历                                    *\n");
        break;
    case 6:
        printf("*                6) 对当前的二叉树进行递归版的中序遍历                                    *\n");
        break;
    case 7:
        printf("*                7) 对当前的二叉树进行迭代版的中序遍历                                    *\n");
        break;
    case 8:
        printf("*                8) 对当前的二叉树进行递归版的后序遍历                                    *\n");
        break;
    case 9:
        printf("*                9) 对当前的二叉树进行迭代版的后序遍历                                    *\n");
        break;
    case 10:
        printf("*                A) 对当前的二叉树进行层序遍历                                            *\n");
        break;
    case 11:
        printf("*                B) 清空并删除二叉查找树和其中数据                                        *\n");
        break;
    case 12:
        printf("*                C) 退出程序                                                              *\n");
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
    line：当前光标所在行数
    deta：行数与菜单选项的差值。比如在main菜单中选项(0)在第2行(行数从0开始计算)，所以deta等于2，即2 - 0
    upper, lower：选项的上下界
    (*P)(int)：函数指针，选择哪个覆盖菜单。只实现了cursorUpdate1一种
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
            (*p)(line - deta); //覆盖，实现退选(实际上就是打印)
            if (line == upper) //如果已经到了上界，则返回下界，实现滚动高亮
                line = lower;
            else
                ++line; //
            Gotoxy(0, line);
            IN_CYAN; // 选择青色
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
    int n = 0, line = 2; // 对应menu()的0)
    char c1;
    IN_DEFAULT;
    Tree* tree = NULL;
    while (1) {
        system("cls");
        Menu();
        Gotoxy(0, 19);
        if ((c1 = _getch()) == -32) {//非VS环境运行需要将代码中的_getch改成getch

            n = cursorOperate(line, 2, 2, 14, cursorUpdate1);//上下键操作
        }
        else if (c1 == '\0')continue;
        else if (c1 >= '0' && c1 <= '9') {//输入数字编号操作
            char tmp = c1;
            putchar(tmp);
            puts("");
            n = tmp - '0';
        }
        else if (c1 == 'q' || c1 == 'Q') {//处理键入数据
            Gotoxy(0, 21);//让光标到合适的地方输出
            putchar(c1);
            puts("");
            printf("师兄再见\n");
            system("pause");
            exit(0);
        }
        else if (c1 == 'a' || c1 == 'A') {//清空链表
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
        else if (c1 == 'c' || c1 == 'C') {//退出
            Gotoxy(0, 20);
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
            puts("师兄再见，下次再来");
            system("pause");
            exit(0);
        }
        }
    }
}