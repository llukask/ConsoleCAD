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
	shapesMap = new map<string, Shape*>();
	counter = 0;
	buffer = new ConsoleBuffer(width, height + IO_HEIGHT);
	separationLine = new shapes::Line(0, width, SEPARATION_CHAR, SEPARATION_COLOR, false, width, 0);
	statusLine = new shapes::Text(0, width + 1, 0, STATUSLINE_COLOR, false, "");
	buffer->clearbuf();
	buffer->clrscr();
}

ShapeContainer::~ShapeContainer() {
	delete buffer;
	delete shapesMap;
	delete separationLine;
	delete statusLine;
}

void ShapeContainer::add(Shape* s, string str) {
	mtx.lock();
	shapesMap->insert(std::pair<std::string, Shape*>(str, s));
	mtx.unlock();
}

void ShapeContainer::add(Shape* s) {
	add(s, to_string(counter++));
}

Shape* ShapeContainer::get(string str) {
	mtx.lock();
	if (shapesMap->count(str) > 0) {
		Shape* ret = shapesMap->find(str)->second;
		mtx.unlock();
		return ret;
	}
	else
	{
		return NULL;
	}
}

void ShapeContainer::draw() {
	draw(true);
}

void ShapeContainer::draw(bool clear) {
	if (clear) {
		buffer->clearbuf();
		buffer->clrscr();
	}

	for (auto iter = shapesMap->begin(); iter != shapesMap->end(); iter++) {
		if (!(iter->second->Hidden())) {
			cout << "drew" << endl;
			iter->second->draw(buffer);
		}
	}

	separationLine->draw(buffer);
	statusLine->draw(buffer);

	buffer->draw();
}

ConsoleBuffer* ShapeContainer::getCBuffer() {
	return buffer;
}

void ShapeContainer::copy(std::string name, std::string copied_name) {
	add(get(name)->copy(), copied_name);
}

void ShapeContainer::setStatusLine(string str) {
	statusLine->setText(str);
}

void ShapeContainer::resetCursor() {
	//Set cursor to last line
	buffer->setcurpos(0, buffer->sizeY() - 1);
}

void ShapeContainer::remove(string name) {
	shapesMap->erase(name);
}