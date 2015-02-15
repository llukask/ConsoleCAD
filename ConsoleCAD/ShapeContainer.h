#ifndef SHAPECONTAINER_H
#define SHAPECONTAINER_H

//#include <vector>
#include <map>
#include <string>
#include "ConsoleBuffer.h"
#include "Shapes.h"
#include <mutex>

using namespace shapes;

class ShapeContainer {
private:
	ConsoleBuffer* buffer;
	std::map<string, Shape*>* shapesMap;
	int counter;
	mutex mtx;
	Line* separationLine;
	Text* statusLine;
public:
	ShapeContainer(int width, int height);
	~ShapeContainer();
	void add(Shape*);
	void add(Shape*, string);
	void copy(std::string name, std::string copied_name);
	Shape* get(string str);
	void remove(string name);
	void draw();
	void draw(bool clear);
	ConsoleBuffer* getCBuffer();
	void setStatusLine(string str);
	void resetCursor();
};

#endif /* SHAPECONTAINER_H */