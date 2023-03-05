#include <stdio.h>//标准输入输出头文件

#include <windows.h>//Windows头文件

#include <stdlib.h>//通用工具头文件

#include <time.h>//时间函数头文件

HANDLE hout;//控制台输出句柄
CONSOLE_SCREEN_BUFFER_INFO csbi;//控制台屏幕缓冲区信息结构体

//占位数组（暂时不知道放几个）
//todo 多行左右上下交叉输出
char letter[1][1][5] = {
        {

                1,
                1,
                1,
                1,
                1,

        }
};
//实际输出内容
char *symbol[] = {".", ".", ".", ".", ".", ".", ".", ".", ".", "."};
//颜色数组
WORD cols[] = {
        FOREGROUND_RED | FOREGROUND_INTENSITY, //红色
        FOREGROUND_RED, //浅红色
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, //黄色
        FOREGROUND_GREEN | FOREGROUND_INTENSITY,//绿色
        FOREGROUND_BLUE | FOREGROUND_INTENSITY, //蓝色
};

//绘制文字的函数
void DrawWord()
{
    int row, col, cut;//行，列，个数
    COORD pos;//坐标，用于光标的定位
    DWORD dwLen;//无符号整型
    for(cut = 0; cut < 4; cut++)//按照字符个数循环
    {
        for(row = 0; row < 5; row++)//每字符5行
        {
//把光标定位到该行的行首位置
            pos.X = cut * 10;
            pos.Y = row;
            SetConsoleCursorPosition(hout, pos);//把光标定位到pos指定的位置
                if(letter[cut][row][col] == 1)
                {
                    GetConsoleScreenBufferInfo(hout, &csbi);
//数组长度：sizeof 数组名 / sizeof 数组元素
                    printf("%s", symbol[rand() % (sizeof symbol / sizeof symbol[0])]);
//上色
                    FillConsoleOutputAttribute(hout,
                                               cols[rand() % (sizeof cols / sizeof cols[0])], 2,
                                               csbi.dwCursorPosition, &dwLen);
                }
                else
                {
                    printf(" ");//两个空格
                }
            }
    }
}
int main()
{
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    while(1)
    {
        DrawWord(); 
        Sleep(120);//1000ms=1s
    }
    getchar();
    return 0;
}
