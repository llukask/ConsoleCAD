#ifndef CONSOLEBUFFER_H
#define CONSOLEBUFFER_H

#include <vector>
#include "Colors.h"

typedef struct ColorChar {
	char c;
	unsigned short color;
} ColorChar;

class ConsoleBuffer {
private:
	std::vector<std::vector<ColorChar>> *matrix;
	void setcolor(unsigned short color);
public:
	ConsoleBuffer(unsigned int sizeX, unsigned int sizeY);
	~ConsoleBuffer();
	void set(unsigned int x, unsigned int y, ColorChar c);
	ColorChar& get(unsigned int x, unsigned int y);
	void draw();
	unsigned int sizeX();
	unsigned int sizeY();
	void clrscr();
	void setcurpos(unsigned int x, unsigned int y);
	void setSize(unsigned int width, unsigned int height);
	void clearbuf();
};

#endif /* CONSOLEBUFFER_H */