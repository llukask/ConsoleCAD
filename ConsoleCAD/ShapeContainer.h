#ifndef SHAPECONTAINER_H
#define SHAPECONTAINER_H

#include <vector>
#include "ConsoleBuffer.h"
#include "Shapes.h"

class ShapeContainer {
private:
	ConsoleBuffer* buffer;
	std::vector<Shape> shapes;
public:
	ShapeContainer();
	void add(Shape);
	void draw();
};

#emdif /* SHAPECONTAINER_H */