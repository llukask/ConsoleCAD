#include "ConsoleBuffer.hpp"
#include <vector>

ConsoleBuffer::ConsoleBuffer(int x, int y) {
	buffer = new std::vector<std::vector<char>>();
	buffer->resize(x, std::vector<char>(y, ' '));
}

ConsoleBuffer::~ConsoleBuffer() {
	buffer->clear();
}

matrix* ConsoleBuffer::getBuffer() {
	return buffer;
}

char ConsoleBuffer::get(int x, int y) {
	if (x < buffer->size() && y < buffer[0].size()) {
		return buffer[x][y];
	}
}