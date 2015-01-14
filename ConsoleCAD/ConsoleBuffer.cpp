#include "ConsoleBuffer.h"
#include <vector>
#include <windows.h>
#include <iostream>


using namespace std;

ConsoleBuffer::ConsoleBuffer(int x, int y) {
	ColorChar standard;
	standard.c = ' ';
	standard.color = WHITE;
	this->matrix = new vector<vector<ColorChar>>(y, vector<ColorChar>(x, standard));
}

ConsoleBuffer::ConsoleBuffer() {
	HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hndl, &csbi);
	ColorChar standard;
	standard.c = ' ';
	standard.color = WHITE;
	this->matrix = new vector<vector<ColorChar>>(csbi.dwSize.Y, vector<ColorChar>(csbi.dwSize.X, standard));
}

ConsoleBuffer::~ConsoleBuffer() {
	this->matrix->clear();
}

void ConsoleBuffer::clrscr() {
		/*HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hndl, &csbi);
		DWORD written;
		DWORD N = csbi.dwSize.X * csbi.dwCursorPosition.Y +
			csbi.dwCursorPosition.X + 1;
		COORD curhome = { 0, 0 };

		FillConsoleOutputCharacter(hndl, ' ', N, curhome, &written);
		csbi.srWindow.Bottom -= csbi.srWindow.Top;
		csbi.srWindow.Top = 0;
		SetConsoleWindowInfo(hndl, TRUE, &csbi.srWindow);
		SetConsoleCursorPosition(hndl, curhome);*/
	system("cls");
}

void ConsoleBuffer::setcolor(unsigned short color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}

void ConsoleBuffer::set(int x, int y, ColorChar c) {
	this->get(x,y) = c;
}

ColorChar& ConsoleBuffer::get(int x, int y) {
	return this->matrix->at(y).at(x);
}

void ConsoleBuffer::draw() {
	this->clrscr();
	vector<vector<ColorChar>>* _matrix = this->matrix;
	for (unsigned int _y = 0; _y < this->sizeY(); _y++) {
		for (unsigned int _x = 0; _x < this->sizeX(); _x++) {
			ColorChar& cc = this->get(_x,_y);
			this->setcolor(cc.color);
			printf("%c", cc.c);
		}
		cout << endl;
	}
	this->setcurpos(0, 0);
}

unsigned int ConsoleBuffer::sizeY() {
	return this->matrix->size();
}

unsigned int ConsoleBuffer::sizeX() {
	unsigned int minSize = MAXUINT;
	for (vector<vector<ColorChar>>::size_type _y = 0; _y < this->matrix->size(); _y++) {
		unsigned int size = this->matrix->at(_y).size();
		minSize = size < minSize ? size : minSize;
	}
	return minSize;
}

void ConsoleBuffer::setcurpos(int x, int y) {
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD co;
	co.X = x;
	co.Y = y;
	SetConsoleCursorPosition(hCon, co);
}