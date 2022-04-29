﻿#include "Common.h"

HWND Common::consoleWindow = GetConsoleWindow();
HANDLE Common::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void Common::setupConsole(int fontSize, int background, int text)
{
	setFontInfo(fontSize, fontSize);
	setAndCenterWindow();
	disableMaximize();
	setConsoleTitle();
	setConsoleColor(background, text);
	hideScrollBars();
	hideCursor();
}

void Common::gotoXY(int left, int top)
{
	SetConsoleCursorPosition(consoleOutput, COORD{ short(left), short(top) });
}

void Common::setConsoleColor(int background, int text)
{
	SetConsoleTextAttribute(consoleOutput, background * 16 + text);
}

void Common::setAndCenterWindow()
{
	RECT rectClient, rectWindow;
	GetClientRect(consoleWindow, &rectClient), GetWindowRect(consoleWindow, &rectWindow);
	int width = 1152;
	int height = 648;
	int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
}

void Common::hideScrollBars()
{
	ShowScrollBar(consoleWindow, SB_BOTH, 0);
}

void Common::hideCursor()
{
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(consoleOutput, &cursorInfo);
	cursorInfo.bVisible = 0; // set the cursor visibility
	SetConsoleCursorInfo(consoleOutput, &cursorInfo);
}

void Common::setConsoleTitle()
{
	SetConsoleTitle(L"HI");
}

void Common::disableMaximize()
{
	SetWindowLong(consoleWindow, GWL_STYLE,
		GetWindowLong(consoleWindow, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME));
}

void Common::setFontInfo(int sizeX, int sizeY)
{
	CONSOLE_FONT_INFOEX info;
	info.cbSize = sizeof(info);
	GetCurrentConsoleFontEx(consoleOutput, FALSE, &info);
	info.dwFontSize.X = sizeX;
	info.dwFontSize.Y = sizeY;
	wcscpy_s(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(consoleOutput, FALSE, &info);
}

void Common::clearConsole()
{
	system("cls");
}

int Common::getConsoleInput()
{
	int c = _getch();
	if (c == 0 || c == 224)
	{
		switch (_getch())
		{
		case 72:				//lên
			return 2;
		case 75:				//trái
			return 3;
		case 77:				//phải
			return 4;
		case 80:				//xuống
			return 5;
		default:				//nút khác
			return 0;
		}
	}
	else
	{
		if (c == 27)                  //esc
			return 1;
		else if (c == 87 || c == 119) //W, w
			return 2;
		else if (c == 65 || c == 97)  //A, a
			return 3;
		else if (c == 68 || c == 100) //D, d
			return 4;
		else if (c == 83 || c == 115) //S, s
			return 5;
		else if (c == 13)             //Enter
			return 6;
		else if (c == 72 || c == 104) //H, h
			return 7;
		else if (c == 77 || c == 109) //M, m
			return 8;
		else
			return 0;                 //nút khác
	}
}