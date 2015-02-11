#include "ShapeContainer.h"
#include <string>

#include <chrono>
#include <iostream>

using namespace std::chrono;

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
	draw(true);
}

void ShapeContainer::draw(bool clear) {
	for (auto iter = shapesMap->begin(); iter != shapesMap->end(); iter++) {
		if (!iter->second->Hidden()) {
			iter->second->draw(buffer);
		}
	}
	if (clear) {
		buffer->clrscr();
	}
	//high_resolution_clock::time_point t1 = high_resolution_clock::now();
	buffer->draw();
	//high_resolution_clock::time_point t2 = high_resolution_clock::now();
	//auto dur = duration_cast<microseconds>(t2 - t1).count();
	//cout << dur;
}

ConsoleBuffer* ShapeContainer::getCBuffer() {
	return buffer;
}

void ShapeContainer::copy(std::string name, std::string copied_name) {

}