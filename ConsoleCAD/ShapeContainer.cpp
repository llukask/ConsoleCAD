#include "ShapeContainer.h"
#include <string>

#include <chrono>
#include <iostream>
#include "Shapes.h"
#include "Colors.h"

using namespace std::chrono;

#define IO_HEIGHT 3
#define SEPARATION_CHAR '-'
#define SEPARATION_COLOR WHITE
#define STATUSLINE_COLOR DARKGRAY

ShapeContainer::ShapeContainer(int width, int height) {
	//init map
	shapesMap = new map<string, Shape*>();
	//init counter for unnamed objects
	counter = 0;
	//init a ConsoleBuffer
	buffer = new ConsoleBuffer(width, height + IO_HEIGHT);
	//some geometry for IO Section
	separationLine = new shapes::Line(0, height, SEPARATION_CHAR, SEPARATION_COLOR, false, width, 0);
	statusLine = new shapes::Text(0, height + 1, STATUSLINE_COLOR, false, "");
	//clear screen and buffer
	buffer->clearbuf();
	buffer->clrscr();
}

ShapeContainer::~ShapeContainer() {
	delete buffer;
	delete shapesMap;
	delete separationLine;
	delete statusLine;
}

//add a shape to the container
void ShapeContainer::add(Shape* s, string str) {
	//insert pair into map
	mtx.lock();
	shapesMap->insert(std::pair<std::string, Shape*>(str, s));
	mtx.unlock();
}

//add an unnamed shape to the container
void ShapeContainer::add(Shape* s) {
	//unnamed shapes get numbered
	add(s, to_string(counter++));
}

//get pointer to a specific shape
Shape* ShapeContainer::get(string str) {
	mtx.lock();
	//check if map contains element with key str
	if (shapesMap->count(str) > 0) {
		//return requested Shape pointer
		Shape* ret = shapesMap->find(str)->second;
		mtx.unlock();
		return ret;
	}
	else
	{
		mtx.unlock();
		return NULL;
	}
}

//draw all the shapes and clear the screen
void ShapeContainer::draw() {
	draw(true);
}

//draws every shape in the map, clear determines if the screen is cleares before drawing
void ShapeContainer::draw(bool clear) {
	if (clear) {
		buffer->clearbuf();
		buffer->clrscr();
	}

	//iterate over every Shape in the map
	for (auto iter = shapesMap->begin(); iter != shapesMap->end(); iter++) {
		//if its not hidden draw it
		if (!(iter->second->Hidden())) {
			iter->second->draw(buffer);
		}
	}
	//draw the separation line and the statusText
	separationLine->draw(buffer);
	statusLine->draw(buffer);

	buffer->draw();
}

//get pointer to the ConsoleBuffer
ConsoleBuffer* ShapeContainer::getCBuffer() {
	return buffer;
}

//copy an element
void ShapeContainer::copy(std::string name, std::string copied_name) {
	add(get(name)->copy(), copied_name);
}

//set the statusLine text
void ShapeContainer::setStatusLine(string str) {
	statusLine->setText(str);
}

//set cursor to beginning of last line
void ShapeContainer::resetCursor() {
	//Set cursor to last line
	buffer->setcurpos(0, buffer->sizeY() - 1);
}

//remove a Shape
void ShapeContainer::remove(string name) {
	shapesMap->erase(name);
}