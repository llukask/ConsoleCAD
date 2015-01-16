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
	std::map<string, Shape*>* shapes;
	int counter;
public:
	ShapeContainer(int width, int height);
	void add(Shape*);
	void add(Shape*, string);
	void draw();
};

#endif /* SHAPECONTAINER_H */