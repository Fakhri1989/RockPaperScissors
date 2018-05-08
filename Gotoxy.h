#ifndef _Gotoxy_
#define _Gotoxy_

#include <iostream>
#include <string.h>
using namespace std;

#include <Windows.h>
#include <process.h>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>

enum { BLACK, DARK_BLUE, DARK_GREEN, DARK_CYAN, DARK_RED, DARK_PURPLE, OLIVE, WHITE, GREY, BLUE, GREEN, CYAN, RED, PURPLE, YELLOW };
void gotoxy(int, int); // prototype
void clrscr(); // prototype
void hideCursor();
void setTextColor(int foreground_color, int background_color);
void setTextColor(int foreground_color);

#endif
