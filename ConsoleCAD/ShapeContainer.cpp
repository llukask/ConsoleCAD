#include "ShapeContainer.h"
#include <string>

ShapeContainer::ShapeContainer(int width, int height) {
	shapesMap = new map<string, Shape*>();
	counter = 0;
	buffer = new ConsoleBuffer(width, height);
	buffer->clearbuf();
	buffer->clrscr();
}

void ShapeContainer::add(Shape* s, string str) {
	shapesMap->insert(std::pair<std::string, Shape*>(str, s));
}

void ShapeContainer::add(Shape* s) {
	add(s, to_string(counter++));
}

Shape* ShapeContainer::get(string str) {
	return shapesMap->find(str)->second;
}

void ShapeContainer::draw() {
	for (auto iter = shapesMap->begin(); iter != shapesMap->end(); iter++) {
		iter->second->draw(buffer);
	}
	buffer->clrscr();
	buffer->draw();
}