#include <vector>
#include "ConsoleBuffer.h"
#include "Shapes.h"

class ShapeContainer {
private:
	ConsoleBuffer* buffer;
	std::vector<Shape> shapes;
};