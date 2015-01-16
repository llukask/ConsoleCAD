#include "ShapeContainer.h"
#include <string>

ShapeContainer::ShapeContainer(int width, int height) {
	shapes = new map<string, Shape*>();
	counter = 0;
	buffer = new ConsoleBuffer(width, height);
	buffer->clearbuf();
	buffer->clrscr();
}

void ShapeContainer::add(Shape* s, string str) {
	shapes->insert(std::pair<std::string, Shape*>(str, s));
}

void ShapeContainer::add(Shape* s) {
	add(s, to_string(counter++));
}

void ShapeContainer::draw() {
	for (auto iter = shapes->begin(); iter != shapes->end(); iter++) {
		iter->second->draw(buffer);
	}
	buffer->clrscr();
	buffer->draw();
}