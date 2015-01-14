#ifndef SHAPES_H
#define SHAPES_H

#include "ConsoleBuffer.h"

class Point {
private:
	unsigned int x, y;
	char c;
	unsigned short color;
	bool hidden;
public:
	Point(unsigned int x, unsigned int y, char c, unsigned short color, bool hidden);
	void Show();
	void Hide();
	void MoveX(int dx);
	void MoveY(int dy);
	void MoveXY(int dx, int dy);
	unsigned int getX();
	unsigned int getY();
	char getC();
	void setC(char c);
	unsigned short getColor();
	void setColor(unsigned short color);
	void draw(ConsoleBuffer* c);
};

typedef Point Shape;

class Rectangle : Shape {
private:
	int height, width;
};

class Circle : Shape {
private:
	int radius;
};

class Line : Shape {
private:
	int dx, dy;
};

#endif /* SHAPES_H */