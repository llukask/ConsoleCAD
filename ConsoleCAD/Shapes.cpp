#include "Shapes.h"
#include "ConsoleBuffer.h"

#include <string>

using namespace shapes;

Shape::Shape(unsigned int _x, unsigned int _y, char _c, unsigned short _color, bool _hidden) {
	x = _x;
	y = _y;
	c = _c;
	color = _color;
	hidden = _hidden;
}

unsigned int Shape::getX() {
	return x;
}

void Shape::MoveX(int dx) {
	x += dx;
}

unsigned int Shape::getY() {
	return y;
}

void Shape::MoveY(int dy) {
	y += dy;
}

void Shape::MoveXY(int dx, int dy) {
	MoveX(dx);
	MoveY(dy);
}

char Shape::getC() {
	return c;
}

void Shape::setC(char _c) {
	c = _c;
}

unsigned short Shape::getColor() {
	return color;
}

void Shape::setColor(unsigned short _color) {
	color = _color;
}

void Shape::Show() {
	hidden = false;
}

void Shape::Hide() {
	hidden = true;
}

bool Shape::Hidden() {
	return hidden;
}

Shape* Shape::copy() {
	return new Shape(getX(), getY(), getC(), getColor(), Hidden());
}

void Shape::draw(ConsoleBuffer* c) {
	if (getX() < c->sizeX() && getY() < c->sizeY()) {
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
: Shape(_x, _y, _c, _color, _hidden) {
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
		//Bresenhams line algorithm
		ColorChar cc;
		cc.c = getC();
		cc.color = getColor();

		int x0 = getX();
		int x1 = getX() + getDx();
		int y0 = getY();
		int y1 = getY() + getDy();

		int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
		int dy = abs(y1 - y0), sy = y0<y1 ? 1 : -1;
		int err = (dx>dy ? dx : -dy) / 2, e2;

		for (;;){
			cb->set(x0, y0, cc);
			if (x0 == x1 && y0 == y1) break;
			e2 = err;
			if (e2 > -dx) { err -= dy; x0 += sx; }
			if (e2 < dy) { err += dx; y0 += sy; }
		}
}

Shape* Line::copy() {
	return new Line(getX(), getY(), getC(), getColor(), Hidden(), getDx(), getDy());
}

Rectangle::Rectangle(unsigned int _x, unsigned int _y, char _c, unsigned short _color, bool _hidden, unsigned int _height, unsigned int _width)
: Shape(_x, _y, _c, _color, _hidden) {
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

Shape* Rectangle::copy() {
	return new Rectangle(getX(), getY(), getC(), getColor(), Hidden(), getHeight(), getWidth());
}

Circle::Circle(unsigned int _x, unsigned int _y, char _c, unsigned short _color, bool _hidden, unsigned int _radius)
: Shape(_x, _y, _c, _color, _hidden) {
	radius = _radius;
}

unsigned int Circle::getRadius() {
	return radius;
}

void Circle::setRadius(unsigned int _radius) {
	radius = _radius;
}

void Circle::draw(ConsoleBuffer* cb) {
	ColorChar cc;
	cc.c = getC();
	cc.color = getColor();
	/*const float PI = 3.14159f;
	float _rad = (float)getRadius();
	for (float angle = 0.0f; angle < 2 * PI; angle += 0.08f) {
		cb->set(
			getX() + (unsigned int)floor(_rad*cosf(angle) + 0.5),
			getY() + (unsigned int)floor(_rad*sinf(angle) + 0.5),
			cc);
	}*/

	unsigned int x0 = getX();
	unsigned int y0 = getY();

	int f = 1 - radius;
	int ddF_x = 0;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	cb->set(x0, y0 + radius, cc);
	cb->set(x0, y0 - radius, cc);
	cb->set(x0 + radius, y0, cc);
	cb->set(x0 - radius, y0, cc);

	while (x < y)
	{
	if (f >= 0)
	{
	y--;
	ddF_y += 2;
	f += ddF_y;
	}
	x++;
	ddF_x += 2;
	f += ddF_x + 1;
	cb->set(x0 + x, y0 + y, cc);
	cb->set(x0 - x, y0 + y, cc);
	cb->set(x0 + x, y0 - y, cc);
	cb->set(x0 - x, y0 - y, cc);
	cb->set(x0 + y, y0 + x, cc);
	cb->set(x0 - y, y0 + x, cc);
	cb->set(x0 + y, y0 - x, cc);
	cb->set(x0 - y, y0 - x, cc);
	}
}

Text::Text(unsigned int _x, unsigned int _y, char _c, unsigned short _color, bool _hidden, string _text)
: Shape(_x, _y, _c, _color, _hidden) {
	text = _text;
}

void Text::draw(ConsoleBuffer* cb) {
	int _y = getY();
	ColorChar cc;
	cc.color = getColor();
	for (unsigned int _x = getX(); _x < getX() + text.size(); _x++) {
		cc.c = text[_x - getX()];
		cb->set(_x, _y, cc);
	}
}

Triangle::Triangle(unsigned int _x, unsigned int _y, char _c, unsigned short _color, bool _hidden, unsigned int _dx1, unsigned int _dy1, unsigned int _dx2, unsigned int _dy2)
: Shape(_x, _y, _c, _color, _hidden) {
	dx1 = _dx1;
	dy1 = _dy1;
	dx2 = _dx2;
	dy2 = _dy2;
}

void Triangle::draw(ConsoleBuffer* cb) {
	unsigned int x = getX();
	unsigned int y = getY();

	Line* l1 = new Line(x, y, getC(), getColor(), false, dx1, dy1);
	Line* l2 = new Line(x + dx1, y + dy1, getC(), getColor(), false, dx2 - dx1, dy2 - dy1);
	Line* l3 = new Line(x, y, getC(), getColor(), false, dx2, dy2);

	l1->draw(cb);
	l2->draw(cb);
	l3->draw(cb);
}