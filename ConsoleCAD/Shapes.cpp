#include "Shapes.h"
#include "ConsoleBuffer.h"

Point::Point(unsigned int x, unsigned int y, char c, unsigned short color, bool hidden) {
	this->x = x;
	this->y = y;
	this->c = c;
	this->color = color;
	this->hidden = hidden;
}

unsigned int Point::getX() {
	return this->x;
}

void Point::MoveX(int dx) {
	this->x += dx;
}

unsigned int Point::getY() {
	return this->y;
}

void Point::MoveY(int dy) {
	this->y += dy;
}

void Point::MoveXY(int dx, int dy) {
	this->MoveX(dx);
	this->MoveY(dy);
}

char Point::getC() {
	return this->c;
}

void Point::setC(char c) {
	this->c = c;
}

unsigned short Point::getColor() {
	return this->color;
}

void Point::setColor(unsigned short color) {
	this->color = color;
}

void Point::Show() {
	this->hidden = false;
}

void Point::Hide() {
	this->hidden = true;
}