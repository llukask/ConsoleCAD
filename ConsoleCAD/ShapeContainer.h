#ifndef SHAPECONTAINER_H
#define SHAPECONTAINER_H

//#include <vector>
#include <map>
#include <string>
#include "ConsoleBuffer.h"
#include "Shapes.h"

using namespace shapes;

class ShapeContainer {
private:
	ConsoleBuffer* buffer;
	std::map<string, Shape*>* shapesMap;
	int counter;
public:
	ShapeContainer(int width, int height);
	void add(Shape*);
	void add(Shape*, string);
	void copy(std::string name, std::string copied_name);
	Shape* get(string str);
	void draw();
	void draw(bool clear);
	ConsoleBuffer* getCBuffer();
};

#endif /* SHAPECONTAINER_H */