// ConsoleCAD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ConsoleBuffer.h"
#include "Colors.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	ConsoleBuffer* x = new ConsoleBuffer(200, 25);
	cin.ignore();
	ColorChar c;
	c.c = 'x';
	c.color = GREEN;
	x->set(5, 5, c);
	x->draw();
	cin.ignore();
	return 0;
}

