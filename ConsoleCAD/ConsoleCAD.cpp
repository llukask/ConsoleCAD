// ConsoleCAD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ConsoleBuffer.h"
#include "Colors.h"
#include "Shapes.h"
#include "ShapeContainer.h"
#include <chrono>

using namespace std;
using namespace std::chrono;


int _tmain(int argc, _TCHAR* argv[])
{
	cin.ignore();
	//ConsoleBuffer* x = new ConsoleBuffer(140,30);
	ShapeContainer* sc = new ShapeContainer(107, 50);
	Shape* circ = (Shape*)new Circle(11, 11, '*', RED, false, 10);
	Shape* rect = (Shape*)new Rectangle(26, 1, '#', LIGHTMAGENTA, false, 20, 20);
	Shape* l1 = (Shape*)new Line(51, 1, '\\', LIGHTBLUE, false, 20, 20);
	Shape* l2 = (Shape*)new Line(51, 21, '/', LIGHTBLUE, false, 20, -20);
	//Shape* l3 = (Shape*)new Line(76, 21, '-', LIGHTGREEN, false, 30, 0);
	//Shape* l4 = (Shape*)new Line(76, 21, '/', LIGHTGREEN, false, 15, -20);
	//Shape* l5 = (Shape*)new Line(106, 21, '\\', LIGHTGREEN, false, -15, -20);
	Shape* tri = (Shape*)new Triangle(76, 21, 'A', LIGHTGREEN, false, 15, -20, 30, 0);
	Shape* tex = (Shape*)new Text(96, 23, ' ', WHITE, false, "\x0A9 Sony Inc.");

	sc->add(circ);
	sc->add(rect);
	sc->add(l1);
	sc->add(l2);
	//sc->add(l3);
	//sc->add(l4);
	//sc->add(l5);
	sc->add(tri);
	sc->add(tex);

	for (int r = 11; r > 9; r--) {
		Shape* sg_circ_outer = (Shape*)new Circle(13, 36, '*', DARKGRAY, false, r);
		sc->add(sg_circ_outer);
	}

	for (int r = 9; r > 0; r--) {
		Shape* sg_circ = (Shape*)new Circle(13, 36, '*', LIGHTBLUE, false, r);
		sc->add(sg_circ);
	}

	Shape* text1 = (Shape*)new Text(7, 49, ' ', WHITE, false, "Stargate SG-1");
	sc->add(text1);

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	sc->draw();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto dur = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	//sc->add(new Text(1, 28, ' ', WHITE, false, ))
	cin.ignore();


	//cin.ignore();
	//circ->draw(x);
	//x->draw();
	//cin.ignore();
	//rect->draw(x);
	//x->draw();
	//cin.ignore();
	//l1->draw(x);
	//l2->draw(x);
	//x->draw();
	//cin.ignore();
	//l3->draw(x);
	//l4->draw(x);
	//l5->draw(x);
	//x->draw();
	//cin.ignore();
	//tex->draw(x);
	//x->draw();
	//cin.ignore();


	return 0;
}

