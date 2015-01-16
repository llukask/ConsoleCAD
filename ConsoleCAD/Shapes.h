#ifndef SHAPES_H
#define SHAPES_H

#include "ConsoleBuffer.h"
#include <string>

using namespace std;

namespace shapes {
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
		virtual void draw(ConsoleBuffer* c);
	};

	typedef Point Shape;

	class Line : Shape {
	private:
		int dx, dy;
	public:
		Line(unsigned int x, unsigned int y, char c, unsigned short color, bool hidden, int dx, int dy);
		int getDx();
		void setDx(int dx);
		int getDy();
		void setDy(int dy);
		virtual void draw(ConsoleBuffer* cb);
	};

	class Rectangle : Shape {
	private:
		int height, width;
	public:
		Rectangle(unsigned int x, unsigned int y, char c, unsigned short color, bool hidden, unsigned int height, unsigned int width);
		unsigned int getWidth();
		void setWidth(unsigned int width);
		unsigned int getHeight();
		void setHeight(unsigned int height);
		virtual void draw(ConsoleBuffer* cb);
	};

	typedef Rectangle MyRectangle;

	class Circle : Shape {
	private:
		int radius;
	public:
		Circle(unsigned int x, unsigned int y, char c, unsigned short color, bool hidden, unsigned int radius);
		unsigned int getRadius();
		void setRadius(unsigned int radius);
		virtual void draw(ConsoleBuffer* cb);
	};

	class Text : Shape {
	private:
		string text;
	public:
		Text(unsigned int x, unsigned int y, char c, unsigned short color, bool hidden, string text);
		virtual void draw(ConsoleBuffer* cb);
	};

	class Triangle : Point {
	private:

	public:
		Triangle(unsigned int _x, unsigned int _y, char _c, unsigned short _color, bool _hidden, unsigned int _dx1, unsigned int _dy1, unsigned int _dx2, unsigned int _dy2);
		unsigned int dx1, dy1, dx2, dy2;
		virtual void draw(ConsoleBuffer* cb);
	};

}


#endif /* SHAPES_H */