// ConsoleCAD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ConsoleBuffer.h"
#include "Colors.h"
#include "Shapes.h"
#include "ShapeContainer.h"
#include "CommandParser.h"
#include <chrono>
#include <sstream>
#include <map>
#include "utility.h"
#include <thread>
#include <mutex>
#include <Windows.h>

#define WIDTH 30
#define HEIGHT 30
#define CHAR 220
#define SLEEP_TIME 50

using namespace std;
using namespace std::chrono;

ShapeContainer* sc;

vector<Shape*>* _shapes;

mutex mtx;

const map<string, unsigned short> colorMap = { { "black", BLACK },
												{ "blue", BLUE },
												{ "green", GREEN },
												{ "cyan", CYAN },
												{ "red", RED },
												{ "magenta", MAGENTA },
												{ "brown", BROWN },
												{ "lightgray", LIGHTGRAY },
												{ "darkgray", DARKGRAY },
												{ "lightblue", LIGHTBLUE },
												{ "lightgreen", LIGHTGREEN },
												{ "lightcyan", LIGHTCYAN },
												{ "lightred", LIGHTRED },
												{ "lightmagenta", LIGHTMAGENTA },
												{ "yellow", YELLOW },
												{ "white", WHITE } };

void draw_cool_things(vector<string>* args) {
	//ShapeContainer* sc = new ShapeContainer(107, 50);
	Shape* circ = (Shape*)new Circle(11, 11, '*', RED, false, 10);
	Shape* rect = (Shape*)new shapes::Rectangle(26, 1, '#', LIGHTMAGENTA, false, 20, 20);
	Shape* l1 = (Shape*)new Line(51, 1, '\\', LIGHTBLUE, false, 20, 20);
	Shape* l2 = (Shape*)new Line(51, 21, '/', LIGHTBLUE, false, 20, -20);
	Shape* tri = (Shape*)new Triangle(76, 21, 'A', LIGHTGREEN, false, 15, -20, 30, 0);
	Shape* tex = (Shape*)new Text(96, 23, ' ', WHITE, false, "\x0A9 Sony Inc.");

	sc->add(circ);
	sc->add(rect);
	sc->add(l1);
	sc->add(l2);
	sc->add(tri);
	sc->add(tex);

	for (int r = 11; r > 9; r--) {
		Shape* sg_circ_outer = (Shape*)new Circle(13, 36, '*', DARKGRAY, false, r);
		sc->add(sg_circ_outer, "sg_outer_" + to_string(r));
	}

	for (int r = 9; r > 0; r--) {
		Shape* sg_circ = (Shape*)new Circle(13, 36, '*', LIGHTBLUE, false, r);
		sc->add(sg_circ, "sg_" + to_string(r));
	}

	Shape* text1 = (Shape*)new Text(7, 49, ' ', WHITE, false, "Stargate SG-1");
	sc->add(text1);

	//Shape* ds_circ1 = (Shape*)new Circle()
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	sc->draw();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto dur = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	cout << dur;
}

void hello_world(vector<string>* args) {
	for (auto el : *args) {
		cout << el << endl;
	}
}

void create_circle(vector<string>* args) {
	int x, y, r;
	char c;
	string name;
	unsigned short color;
	x = fromString<int>(args->at(0));
	y = fromString<int>(args->at(1));
	r = fromString<int>(args->at(2));
	c = fromString<char>(args->at(3));
	name = args->at(4);
	color = colorMap.at(args->at(5));
	Circle* circle = new Circle(x, y, c, color, false, r);
	sc->add((Shape*)circle, name);
	sc->draw();
	cout << args->size() << endl;
}

void hide(vector<string>* args) {
	string name = args->at(0);
 	sc->get(name)->Hide();
	sc->draw();
}

//CommandNode* build_command_tree() {
//	CommandNode* root = new CommandNode();
//	root->AddSubcommand("hello", new CommandNode(hello_world));
//	root->AddSubcommand("pst", new CommandNode(draw_cool_things));
//	root->AddSubcommand("hide", new CommandNode(hide));
//	CommandNode* create = new CommandNode();
//	create->AddSubcommand("circle", new CommandNode(create_circle));
//	root->AddSubcommand("create", create);
//	return root;
//}

void circles() {
	for (int i = WIDTH / 2; i >= 0; i--) {
		Circle* c = new Circle(WIDTH / 2, HEIGHT / 2, CHAR, (rand() % 14) + 1, false, i);
		sc->add((Shape*)c);
		mtx.lock();
		_shapes->push_back(c);
		mtx.unlock();
		Sleep(SLEEP_TIME);
		/*for (Shape* cp : *_shapes) {
			cp->setColor((rand() % 14) + 1);
			}*/
		//sc->draw(false);
	}
}

void rects() {
	for (int x = 0, y = 0; x <= HEIGHT / 2 && y <= WIDTH / 2; x++, y++) {
		MyRectangle* rec = new MyRectangle(x, y, CHAR, (rand() % 14) + 1, false, HEIGHT - 2 * x, WIDTH - 2 * y);
		sc->add((Shape*)rec);
		mtx.lock();
		_shapes->push_back(rec);
		mtx.unlock();
		Sleep(SLEEP_TIME);
		/*for (Shape* cp : *_shapes) {
			cp->setColor((rand() % 14) + 1);
		}*/
		//sc->draw(false);
	}
}

void lines() {
	for (int x = 0, y = 0; y <= HEIGHT; x++, y++) {
		Line* lin = new Line(x, 0, CHAR, (rand() % 14) + 1, false, -x, y);
		sc->add((Shape*)lin);
		mtx.lock();
		_shapes->push_back(lin);
		mtx.unlock();
		Sleep(SLEEP_TIME);
		/*for (Shape* cp : *_shapes) {
			cp->setColor((rand() % 14) + 1);
		}*/
		//sc->draw(false);
		//mtx.unlock();
	}

	for (int x = 0, y = HEIGHT; x + HEIGHT <= WIDTH - 1; x++) {
		Line* lin = new Line(x, y, CHAR, (rand() % 14) + 1, false, HEIGHT, -HEIGHT);
		sc->add((Shape*)lin);
		mtx.lock();
		_shapes->push_back(lin);
		mtx.unlock();
		Sleep(SLEEP_TIME);
		/*for (Shape* cp : *_shapes) {
			cp->setColor((rand() % 14) + 1);
		}*/
		//sc->draw(false);
		//mtx.unlock();
	}

	for (int x = HEIGHT, y = HEIGHT; x <= WIDTH - 1; x++) {
		Line* lin = new Line(x, y, CHAR, (rand() % 14) + 1, false, (2 * HEIGHT) - x, -((2 * HEIGHT) - x));
		sc->add((Shape*)lin);
		mtx.lock();
		_shapes->push_back(lin);
		mtx.unlock();
		Sleep(SLEEP_TIME);
		/*for (Shape* cp : *_shapes) {
			cp->setColor((rand() % 14) + 1);
		}*/
		//sc->draw(false);
	}
}

void change_color() {
	for (;;) {
		mtx.lock();
		for (Shape* cp : *_shapes) {
			cp->setColor((rand() % 14) + 1);
		}
		mtx.unlock();
		Sleep(SLEEP_TIME);
	}
}

void drawt() {
	for (;;) {
		/*for (Shape* cp : *_shapes) {
			cp->setColor((rand() % 14) + 1);
		}*/
		sc->draw(false);
	}
}

int _tmain(int argc, _TCHAR* argv[]) {
	//CommandNode* root = build_command_tree();
	sc = new ShapeContainer(WIDTH, HEIGHT);

	/*do {
		sc->getCBuffer()->setcurpos(0, 50);
		std::string cmd;
		std::getline(std::cin, cmd);
		root->walk(cmd);
	} while (true);
	cin.ignore();*/


	//draw_cool_things(NULL);

	/*std::thread l_thread(lines);
	std::thread r_thread(rects);
	std::thread c_thread(circles);*/
	//std::thread cc_thread(change_color);

	_shapes = new vector<Shape*>();

	SetConsoleOutputCP(437);

	std::thread l_thr(lines);
	std::thread r_thr(rects);
	std::thread c_thr(circles);
	std::thread cc_thr(change_color);
	std::thread drawer(drawt);

	cin.ignore();
 
	return 0;
}

