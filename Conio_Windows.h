#ifndef CONIOWIN_H
#define CONIOWIN_H
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
/*
#define black 0
#define blue 1
#define green 2
#define cyan 3
#define red 4
#define purple 5
#define yellow 6
#define white 7
*/
#define black 8
#define blue 9
#define green 10
#define cyan 11
#define red 12
#define purple 13
#define yellow 14
#define white 15
#define Hblack 8
#define Hblue 9
#define Hgreen 10
#define Hcyan 11
#define Hred 12
#define Hpurple 13
#define Hyellow 14
#define Hwhite 15

#define on_(x,y) (x+16*y)

#define Clear() system("cls")

void gotoxy(int x,int y)
{ 
	COORD c; 
	c.X=x-1; 
	c.Y=y-1; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}


int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO pBuffer;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&pBuffer);
	return (pBuffer.dwCursorPosition.X+1);
}


int wherey()  
{  
	CONSOLE_SCREEN_BUFFER_INFO pBuffer;  
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&pBuffer);  
	return (pBuffer.dwCursorPosition.Y+1);  
}

/*隐藏光标*/
void HideCursor() 
{ 
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info); 
} 
/*显示光标*/
void UnHideCursor() 
{ 
	CONSOLE_CURSOR_INFO cursor_info = {1, 25};  
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info); 
} 
//改变颜色
//color(WORD a,WORD b);字为颜色a,背景为颜色b
int color(WORD a,WORD b)
{
	if ((a>15)||(b>15)) return -1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),on_(a,b));
	return on_(a,b);
}

void foreground(WORD a) {
	color(a,white);
}

double pro_time()
{
	return (double)clock()/CLOCKS_PER_SEC;
}

int readkey(double _time__)
{
	double time_last=pro_time();
	while (!kbhit()&&(pro_time()-time_last<_time__))  ;
	if (!kbhit()) return 0;
	return getch();
}

#define HighLight()
#define ClearColor()
#endif
