// ConsoleCAD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ConsoleBuffer.hpp"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	ConsoleBuffer* buf = new ConsoleBuffer(10, 11);
	cout << "buffer.size(): " << buf->getBuffer()->size() << endl;
	cout << "buffer[0].size():   " << buf->getBuffer()->front().size() << endl;



	cin.ignore();
	return 0;
}

