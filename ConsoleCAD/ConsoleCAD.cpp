// ConsoleCAD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ConsoleBuffer.h"
#include "Colors.h"
#include "Shapes.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	ConsoleBuffer* x = new ConsoleBuffer(50,10);
	Shape* rect = (Shape*)new Rectangle(3, 3, '+', GREEN, false, 5, 10);

	cin.ignore();
	rect->draw(x);
	x->draw();
	cin.ignore();
	return 0;
}

