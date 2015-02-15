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

#define WIDTH 200
#define HEIGHT 100
#define CHAR (unsigned char)'/'
#define SLEEP_TIME (unsigned int)50
#define NEGATIVE_COLOR RED
#define POSITIVE_COLOR GREEN
#define NEUTRAL_COLOR DARKGRAY

LPCWSTR help_text = L"Command listing \n\
\"help\" -> shows this help text \n\
\"create point <x> <y> <char> <name> <color>\" -> creates a point \n\
\"create line <x> <y> <dx> <dy> <char> <name> <color>\" -> create a line \n\
\"create circle <x> <y> <radius> <char> <name> <color>\" -> create a circle\n\
\"create rectangle <x> <y> <width> <height> <char> <name> <color>\" -> create a rectangle\n\
\"create triangle <x> <y> <dx0> <dy0> <dx1> <dx1> <char> <name> <color>\" -> create a triangle\n\
\"change char <name> <new_char>\" -> changes the char of a shape\n\
\"change color <name> <new_color>\" -> changes the color of a shape \n\
\"move <name> <dx> <dy>\" -> moves a shape \n\
\"hide <name>\" -> hides a shape \n\
\"show <name>\" -> unhide a shape \n\
\"erase <name>\" -> erase a shape \n\
\"copy <name> <new_name>\" -> copy a shape \n\
\"colors\" -> shows a list of possible colors";

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

//command functions

//pst
void draw_cool_things(vector<string>* args) {
	//ShapeContainer* sc = new ShapeContainer(107, 50);
	Shape* circ = (Shape*)new Circle(11, 11, '*', RED, false, 10);
	Shape* rect = (Shape*)new shapes::Rectangle(26, 1, '#', LIGHTMAGENTA, false, 20, 20);
	Shape* l1 = (Shape*)new Line(51, 1, '\\', LIGHTBLUE, false, 20, 20);
	Shape* l2 = (Shape*)new Line(51, 21, '/', LIGHTBLUE, false, 20, -20);
	Shape* tri = (Shape*)new Triangle(76, 21, 'A', LIGHTGREEN, false, 15, -20, 30, 0);
	Shape* tex = (Shape*)new Text(96, 23, WHITE, false, "\x0A9 Sony Inc.");

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

	Shape* text1 = (Shape*)new Text(7, 49, WHITE, false, "Stargate SG-1");
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

//create point <x> <y> <char> <name> <color>
void create_point(vector<string>* args) {
	try {
		int x, y;
		char c;
		string name;
		unsigned int color;
		x = fromString<int>(args->at(0));
		y = fromString<int>(args->at(1));
		c = fromString<char>(args->at(2));
		name = args->at(3);
		color = colorMap.at(args->at(4));
		Point* p = new Point(x, y, c, color, false);
		sc->add((Shape*)p, name);
		sc->setStatusLineColor(POSITIVE_COLOR);
		sc->setStatusLine("created point " + name);
		return;
	}
	catch (...) {
		sc->setStatusLineColor(NEGATIVE_COLOR);
		sc->setStatusLine("ERROR, syntax for create point is \"create point <x> <y> <char> <name> <color>\"");
	}
}

//create line <x> <y> <dx> <dy> <char> <name> <color>
void create_line(vector<string>* args) {
	try {
		int x, y, dx, dy;
		char c;
		string name;
		unsigned short color;
		x = fromString<int>(args->at(0));
		y = fromString<int>(args->at(1));
		dx = fromString<int>(args->at(2));
		dy = fromString<int>(args->at(3));
		c = fromString<char>(args->at(4));
		name = args->at(5);
		color = colorMap.at(args->at(6));
		shapes::Line* rec = new shapes::Line(x, y, c, color, false, dx, dy);
		sc->add((Shape*)rec, name);
		sc->setStatusLineColor(POSITIVE_COLOR);
		sc->setStatusLine("created line " + name);
	}
	catch (...) {
		sc->setStatusLineColor(NEGATIVE_COLOR);
		sc->setStatusLine("ERROR, syntax for create line is \"create line <x> <y> <dx> <dy> <char> <name> <color>\"");
	}
}

//create circle <x> <y> <radius> <char> <name> <color>
void create_circle(vector<string>* args) {
	try {
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
		sc->setStatusLineColor(POSITIVE_COLOR);
		sc->setStatusLine("created circle " + name);
	}
	catch (...) {
		sc->setStatusLineColor(NEGATIVE_COLOR);
		sc->setStatusLine("ERROR, syntax for create circle is \"create circle <x> <y> <radius> <char> <name> <color>\"");
	}
}

//create rectangle <x> <y> <width> <height> <char> <name> <color>
void create_rectangle(vector<string>* args) {
	try {
		int x, y, width, height;
		char c;
		string name;
		unsigned short color;
		x = fromString<int>(args->at(0));
		y = fromString<int>(args->at(1));
		width = fromString<int>(args->at(2));
		height = fromString<int>(args->at(3));
		c = fromString<char>(args->at(4));
		name = args->at(5);
		color = colorMap.at(args->at(6));
		shapes::Rectangle* rec = new shapes::Rectangle(x, y, c, color, false, height, width);
		sc->add((Shape*)rec, name);
		sc->setStatusLineColor(POSITIVE_COLOR);
		sc->setStatusLine("created rectangle " + name);
	}
	catch (...) {
		sc->setStatusLineColor(NEGATIVE_COLOR);
		sc->setStatusLine("ERROR, syntax for create rectangle is \"create rectangle <x> <y> <width> <height> <char> <name> <color>\"");
	}
}

//create triangle <x> <y> <dx0> <dy0> <dx1> <dx1> <char> <name> <color>
void create_triangle(vector<string>* args) {
	try {
		int x, y, dx0, dy0, dx1, dy1;
		char c;
		string name;
		unsigned short color;
		x = fromString<int>(args->at(0));
		y = fromString<int>(args->at(1));
		dx0 = fromString<int>(args->at(2));
		dy0 = fromString<int>(args->at(3));
		dx1 = fromString<int>(args->at(4));
		dy1 = fromString<int>(args->at(5));
		c = fromString<char>(args->at(6));
		name = args->at(7);
		color = colorMap.at(args->at(8));
		shapes::Triangle* rec = new shapes::Triangle(x, y, c, color, false, dx0, dy0, dx1, dy1);
		sc->add((Shape*)rec, name);
		sc->setStatusLineColor(POSITIVE_COLOR);
		sc->setStatusLine("created line " + name);
	}
	catch (...) {
		sc->setStatusLineColor(NEGATIVE_COLOR);
		sc->setStatusLine("ERROR, syntax for create triangle is \"create triangle <x> <y> <dx0> <dy0> <dx1> <dx1> <char> <name> <color>\"");
	}
}

//change char <name> <new_char>
void change_char(vector<string>* args) {
	try {
		sc->get(args->at(0))->setC(fromString<char>(args->at(1)));
		sc->setStatusLineColor(POSITIVE_COLOR);
		sc->setStatusLine("changed char of " + args->at(0));
	}
	catch (...) {
		sc->setStatusLineColor(NEGATIVE_COLOR);
		sc->setStatusLine("ERROR, syntax for change char is \"change char <name> <new_char>\"");
	}
}

//change color <name> <new_color>
void change_color(vector<string>* args) {
	try {
		sc->get(args->at(0))->setColor(colorMap.at(args->at(1)));
		sc->setStatusLineColor(POSITIVE_COLOR);
		sc->setStatusLine("changed color of " + args->at(0));
	}
	catch (...) {
		sc->setStatusLineColor(NEGATIVE_COLOR);
		sc->setStatusLine("ERROR, syntax for change color \"change color <name> <new_color>\"");
	}
}

//hide <name>
void hide(vector<string>* args) {
	try {
		string name = args->at(0);
		Shape* elem = sc->get(name);
		if (elem) {
			elem->Hide();
			sc->setStatusLineColor(POSITIVE_COLOR);
			sc->setStatusLine("hid " + name);
			return;
		}
		sc->setStatusLineColor(NEGATIVE_COLOR);
		sc->setStatusLine("could not find " + name);
	}
	catch (...) {
		sc->setStatusLineColor(NEGATIVE_COLOR);
		sc->setStatusLine("ERROR, syntax for hide is \"hide <name>\"");
	}
}

//show <name>
void show(vector<string>* args) {
	try {
		string name = args->at(0);
		Shape* elem = sc->get(name);
		if (elem) {
			elem->Show();
			sc->setStatusLineColor(POSITIVE_COLOR);
			sc->setStatusLine("hid " + name);
			return;
		}
		sc->setStatusLineColor(NEGATIVE_COLOR);
		sc->setStatusLine("could not find " + name);
	}
	catch (...) {
		sc->setStatusLineColor(NEGATIVE_COLOR);
		sc->setStatusLine("ERROR, syntax for show \"show <name>\"");
	}
}

//help
void help(vector<string>* args) {
	MessageBox(NULL, help_text, L"Console CAD Help", MB_OK);
}

//move <name> <dx> <dy>
void move(vector<string>* args) {
	try {
		string name = args->at(0);
		unsigned int dx = fromString<int>(args->at(1)), dy = fromString<int>(args->at(2));
		Shape* elem = sc->get(name);
		if (elem) {
			elem->MoveXY(dx, dy);
			sc->setStatusLineColor(POSITIVE_COLOR);
			sc->setStatusLine("moved " + name);
			return;
		}
		sc->setStatusLineColor(NEGATIVE_COLOR);
		sc->setStatusLine("could not find " + name);
	}
	catch (...) {
		sc->setStatusLineColor(NEGATIVE_COLOR);
		sc->setStatusLine("ERROR, syntax for move is \"move <name> <dx> <dy>\"");
	}
}

//delete <name>
void erase(vector<string>* args) {
	try {
		string name = args->at(0);
		sc->remove(name);
		sc->setStatusLineColor(POSITIVE_COLOR);
		sc->setStatusLine("removed " + name);
	}
	catch (...) {
		sc->setStatusLineColor(NEGATIVE_COLOR);
		sc->setStatusLine("ERROR, syntax for delete is \"delete <name>\"");
	}
}

//copy <name> <new_name>
void shape_copy(vector<string>* args) {
	try {
		sc->copy(args->at(0), args->at(1));
		sc->setStatusLineColor(POSITIVE_COLOR);
		sc->setStatusLine("copied " + args->at(0));
	}
	catch (...) {
		sc->setStatusLineColor(NEGATIVE_COLOR);
		sc->setStatusLine("ERROR, syntax for copy is \"copy <name> <new_name>\"");
	}
}

//colors
void colors(vector<string>* args) {
	string colors = "";
	bool first = true;
	for (auto color : colorMap) {
		if (!first) {
			colors += ", ";
		}
		else
		{
			first = false;
		}
		colors += color.first;
	}
	sc->setStatusLineColor(NEUTRAL_COLOR);
	sc->setStatusLine(colors);
}

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
	}

	for (int x = 0, y = HEIGHT; x + HEIGHT <= WIDTH - 1; x++) {
		Line* lin = new Line(x, y, CHAR, (rand() % 14) + 1, false, HEIGHT, -HEIGHT);
		sc->add((Shape*)lin);
		mtx.lock();
		_shapes->push_back(lin);
		mtx.unlock();
		Sleep(SLEEP_TIME);
	}

	for (int x = HEIGHT, y = HEIGHT; x <= WIDTH - 1; x++) {
		Line* lin = new Line(x, y, CHAR, (rand() % 14) + 1, false, (2 * HEIGHT) - x, -((2 * HEIGHT) - x));
		sc->add((Shape*)lin);
		mtx.lock();
		_shapes->push_back(lin);
		mtx.unlock();
		Sleep(SLEEP_TIME);
	}
}

void color_change() {
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


void lsd(vector<string>* args) {

	_shapes = new vector<Shape*>();
	SetConsoleOutputCP(437);

	std::thread l_thr(lines);
	std::thread r_thr(rects);
	std::thread c_thr(circles);
	std::thread cc_thr(color_change);
	std::thread drawer(drawt);
}

CommandNode* build_command_tree() {
	CommandNode* root = new CommandNode();
	root->AddSubcommand("hello", new CommandNode(hello_world));
	root->AddSubcommand("pst", new CommandNode(draw_cool_things));
	root->AddSubcommand("hide", new CommandNode(hide));
	root->AddSubcommand("show", new CommandNode(show));
	root->AddSubcommand("move", new CommandNode(move));
	root->AddSubcommand("help", new CommandNode(help));
	root->AddSubcommand("delete", new CommandNode(erase));
	root->AddSubcommand("copy", new CommandNode(shape_copy));
	root->AddSubcommand("lsd", new CommandNode(lsd));
	root->AddSubcommand("colors", new CommandNode(colors));
	CommandNode* create = new CommandNode();
	create->AddSubcommand("point", new CommandNode(create_point));
	create->AddSubcommand("circle", new CommandNode(create_circle));
	create->AddSubcommand("rectangle", new CommandNode(create_rectangle));
	create->AddSubcommand("line", new CommandNode(create_line));
	create->AddSubcommand("triangle", new CommandNode(create_triangle));
	root->AddSubcommand("create", create);

	CommandNode* change = new CommandNode();
	change->AddSubcommand("char", new CommandNode(change_char));
	change->AddSubcommand("color", new CommandNode(change_color));
	root->AddSubcommand("change", change);
	return root;
}



int _tmain(int argc, _TCHAR* argv[]) {
	//initiate ShapeContainer and command tree
	sc = new ShapeContainer(WIDTH, HEIGHT);
	CommandNode* root = build_command_tree();
	sc->setStatusLine("type \"help <enter>\" to get help!");
	sc->setStatusLineColor(DARKGRAY);
	sc->setPrompt("Command > ");
	sc->setPromptColor(DARKGRAY);
	sc->draw();

	//do forever 
	do
	{	
		//set cursor to last line
		sc->resetCursor();
		//get 1 line of input
		string input;
		getline(cin, input);
		if (input.empty()) {
			break;
		}
		//walk the command tree with input
		root->walk(input);
		//redraw
		sc->draw();
	} while (true);

	return 0;
}

