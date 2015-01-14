// ConsoleCAD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ConsoleBuffer.h"
#include "Colors.h"
#include <Windows.h>

using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{

	ConsoleBuffer* x = new ConsoleBuffer(200,50);
	cin.ignore();
	ColorChar c;
	for (int i = 0; i < 10; i++) {
		c.c = (char)i + 48;
		c.color = LIGHTCYAN;
		x->set(0, i, c);
	}
	x->draw();
	cin.ignore();
	for (int i = 0; i < 10; i++) {
		c.c = (char)i + 48;
		c.color = GREEN;
		x->set(5, i, c);
	}
	x->draw();
	cin.ignore();
	x->clearbuf();
	x->draw();
	cin.ignore();
	return 0;
}

