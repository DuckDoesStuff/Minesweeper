#include "Common.h"

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
	return 0;
}