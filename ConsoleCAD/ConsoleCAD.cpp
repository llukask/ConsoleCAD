// ConsoleCAD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ConsoleBuffer.h"
#include "Colors.h"
#include "Shapes.h"
#include <Windows.h>

using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{

	ConsoleBuffer* x = new ConsoleBuffer(200,50);
	Point* p = new Point(10, 10, 'c', CYAN, false);
	cin.ignore();
	p->draw(x);
	x->draw();
	cin.ignore();
	return 0;
}

