#include "Shapes.h"
#include "ConsoleBuffer.h"

Point::Point(unsigned int _x, unsigned int _y, char _c, unsigned short _color, bool _hidden) {
	x = _x;
	y = _y;
	c = _c;
	color = _color;
	hidden = _hidden;
}

unsigned int Point::getX() {
	return x;
}

void Point::MoveX(int dx) {
	x += dx;
}

unsigned int Point::getY() {
	return y;
}

void Point::MoveY(int dy) {
	y += dy;
}

void Point::MoveXY(int dx, int dy) {
	MoveX(dx);
	MoveY(dy);
}

char Point::getC() {
	return c;
}

void Point::setC(char _c) {
	c = _c;
}

unsigned short Point::getColor() {
	return color;
}

void Point::setColor(unsigned short _color) {
	color = _color;
}

void Point::Show() {
	hidden = false;
}

void Point::Hide() {
	hidden = true;
}

void Point::draw(ConsoleBuffer* c) {
	if (getX() < c->sizeX() && getY() < c->sizeY() && !hidden) {
		ColorChar cc;
		cc.c = this->c;
		cc.color = this->color;
		c->set(
			getX(),
			getY(),
			cc);
	}
}

Line::Line(unsigned int _x, unsigned int _y, char _c, unsigned short _color, bool _hidden, int _dx, int _dy)
	: Point(_x, _y, _c, _color, _hidden) {
	dx = _dx;
	dy = _dy;
}

int Line::getDx() {
	return dx;
}

void Line::setDx(int _dx) {
	dx = _dx;
}

int Line::getDy() {
	return dy;
}

void Line::setDy(int _dy) {
	dy = _dy;
}

void Line::draw(ConsoleBuffer* cb) {
	ColorChar cc;
	cc.c = getC();
	cc.color = getColor();
	float k = (float)getDx() / getDy();
	float d = (float)getX() - k*(float)getY();

	int _dx;
	int _dy;
	int newX;
	int newY;

	if (getDx() >= 0) {
		_dx = getDx();
		newX = getX();
	}
	else {
		_dx = -getDx();
		newX = getX() - _dx;
	}
	if (getDy() >= 0) {
		_dy = getDy();
		newY = getY();
	}
	else {
		_dy = -getDy();
		newY = getY() - _dy;
	}

	float error = 0;
	float deltaerr = _dx != 0 ? abs((float)_dy / (float)_dx) : (float)_dy;
	unsigned int y = newY;
	unsigned int y1 = y + _dy;
	for (unsigned int x = newX; x <= (newX + _dx); x++) {
		cb->set(x, y, cc);
		error += deltaerr;
		while (error >= 0.5)
		{
			cb->set(x, y, cc);
			y += 1;
			error -= 1.0;
		}
	}
}

Rectangle::Rectangle(unsigned int _x, unsigned int _y, char _c, unsigned short _color, bool _hidden, unsigned int _height, unsigned int _width)
	: Point(_x, _y, _c, _color, _hidden) {
	width = _width;
	height = _height;
}

unsigned int Rectangle::getHeight() {
	return height;
}

void Rectangle::setHeight(unsigned int _height) {
	height = _height;
}

unsigned int Rectangle::getWidth() {
	return width;
}

void Rectangle::setWidth(unsigned int _width) {
	width = _width;
}

void Rectangle::draw(ConsoleBuffer* cb) {
	//disassemble a rectangle into four lines 
	Line* li1 = new Line(getX(), getY(), getC(), getColor(), false, (signed int)getWidth(), 0);
	Line* li2 = new Line(getX() + getWidth(), getY(), getC(), getColor(), false, 0, (signed int)getHeight());
	Line* li3 = new Line(getX() + getWidth(), getY() + getHeight(), getC(), getColor(), false, -(signed int)getWidth(), 0);
	Line* li4 = new Line(getX(), getY() + getHeight(), getC(), getColor(), false, 0, -(signed int)getHeight());
	li1->draw(cb);
	li2->draw(cb);
	li3->draw(cb);
	li4->draw(cb);
}

Circle::Circle(unsigned int _x, unsigned int _y, char _c, unsigned short _color, bool _hidden, unsigned int _radius)
	: Point(_x, _y, _c, _color, _hidden) {
	radius = _radius;
}

unsigned int Circle::getRadius() {
	return radius;
}

void Circle::setRadius(unsigned int _radius) {
	radius = _radius;
}

