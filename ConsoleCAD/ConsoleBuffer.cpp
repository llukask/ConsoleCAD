#include "ConsoleBuffer.h"
#include <vector>
#include <Windows.h>
#include <iostream>


using namespace std;

ConsoleBuffer::ConsoleBuffer(unsigned int x, unsigned int y) {
	ColorChar standard;
	standard.c = ' ';
	standard.color = WHITE;
	//initiate buffer 
	this->matrix = new vector<vector<ColorChar>>(y, vector<ColorChar>(x, standard));
	//set console size to buffer size
	this->setSize(x, y);
	size_x = x;
	size_y = y;
}

ConsoleBuffer::~ConsoleBuffer() {
	this->matrix->clear();
	delete matrix;
}

void ConsoleBuffer::clrscr() {
	system("cls");
}

void ConsoleBuffer::setcolor(unsigned short color)
{
	//set the output color
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}

void ConsoleBuffer::set(unsigned int x, unsigned int y, ColorChar c) {
	this->get(x,y) = c;
}

ColorChar& ConsoleBuffer::get(unsigned int x,unsigned int y) {
	if (x < this->size_x && y < this->size_y) {
		return (*this->matrix)[y][x];
	}
	else
	{
		ColorChar c;
		return c;
	}
}

void ConsoleBuffer::draw() {
	//obtain handle to console
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	//construnt an array of CHAR_INFO as input to WriteConsoleOutput 
	CHAR_INFO* screenBuffer = new CHAR_INFO[sizeX()*sizeY()];
	int i = 0;
	for (unsigned int _y = 0; _y < size_y; _y++) {
		for (unsigned int _x = 0; _x < size_x; _x++) {
			ColorChar& cc = this->get(_x, _y);
			CHAR_INFO temp;
			temp.Attributes = cc.color;
			temp.Char.UnicodeChar = cc.c;
			screenBuffer[i] = temp;
			i++;
		}
	}

	COORD dwBufferSize = { sizeX(), sizeY() };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, sizeX() - 1, sizeY() - 1 };

	WriteConsoleOutput(hCon, screenBuffer, dwBufferSize, dwBufferCoord, &rcRegion);
}

unsigned int ConsoleBuffer::sizeY() {
	return size_y;
}

unsigned int ConsoleBuffer::sizeX() {
	return size_x;
}

void ConsoleBuffer::setcurpos(unsigned int x, unsigned int y) {
	//set cursir position
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD co;
	co.X = x;
	co.Y = y;
	SetConsoleCursorPosition(hCon, co);
}

//sets console window and buffer size using WinAPI
void ConsoleBuffer::setSize(unsigned int width, unsigned int height) {
	SMALL_RECT r;
	COORD      c;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

	r.Left = r.Top = 0;
	r.Right = width - 1;
	r.Bottom = height - 1;
	SetConsoleWindowInfo(hConOut, TRUE, &r);

	c.X = width;
	c.Y = height;
	SetConsoleScreenBufferSize(hConOut, c);
}

//resets the buffer (empties it)
void ConsoleBuffer::clearbuf() {
	ColorChar c;
	c.c = ' ';
	c.color = WHITE;
	for (unsigned int i = 0; i < this->sizeY(); i++) {
		this->matrix->at(i).assign(this->sizeX(), c);
	}
}