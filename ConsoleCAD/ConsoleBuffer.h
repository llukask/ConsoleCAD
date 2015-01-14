#include <vector>
#include "Colors.h"

typedef struct ColorChar {
	char c;
	unsigned short color;
} ColorChar;

class ConsoleBuffer {
private:
	std::vector<std::vector<ColorChar>> *matrix;
	void ConsoleBuffer::setcolor(unsigned short color);
public:
	ConsoleBuffer(int sizeX, int sizeY);
	ConsoleBuffer();
	~ConsoleBuffer();
	void set(int x, int y, ColorChar c);
	ColorChar& get(int x, int y);
	void draw();
	unsigned int sizeX();
	unsigned int sizeY();
	void clrscr();
	void setcurpos(int x, int y);
};