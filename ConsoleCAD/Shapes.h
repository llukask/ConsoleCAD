#ifndef SHAPES_H
#define SHAPES_H

#include "ConsoleBuffer.h"
#include <string>

using namespace std;


namespace shapes {

	class Shape {
	private:
		unsigned int x, y;
		char c;
		unsigned short color;
		bool hidden;
	public:
		Shape(unsigned int x, unsigned int y, char c, unsigned short color, bool hidden);
		void Show();
		void Hide();
		bool Hidden();
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
		virtual Shape* copy();
	};

	typedef Shape Point;

	class Line : public Shape {
	private:
		int dx, dy;
	public:
		Line(unsigned int x, unsigned int y, char c, unsigned short color, bool hidden, int dx, int dy);
		int getDx();
		void setDx(int dx);
		int getDy();
		void setDy(int dy);
		virtual void draw(ConsoleBuffer* cb);
		virtual Shape* copy();
	};

	class Rectangle : public Shape {
	private:
		int height, width;
	public:
		Rectangle(unsigned int x, unsigned int y, char c, unsigned short color, bool hidden, unsigned int height, unsigned int width);
		unsigned int getWidth();
		void setWidth(unsigned int width);
		unsigned int getHeight();
		void setHeight(unsigned int height);
		virtual void draw(ConsoleBuffer* cb);
		virtual Shape* copy();
	};

	typedef Rectangle MyRectangle;

	class Circle : public Shape {
	private:
		int radius;
	public:
		Circle(unsigned int x, unsigned int y, char c, unsigned short color, bool hidden, unsigned int radius);
		unsigned int getRadius();
		void setRadius(unsigned int radius);
		virtual void draw(ConsoleBuffer* cb);
		//virtual Shape* copy();
	};

	class Text : public Shape {
	private:
		string text;
	public:
		Text(unsigned int x, unsigned int y, char c, unsigned short color, bool hidden, string text);
		virtual void draw(ConsoleBuffer* cb);
		//virtual Shape* copy();
	};

	class Triangle : public Shape {
	private:

	public:
		Triangle(unsigned int _x, unsigned int _y, char _c, unsigned short _color, bool _hidden, unsigned int _dx1, unsigned int _dy1, unsigned int _dx2, unsigned int _dy2);
		unsigned int dx1, dy1, dx2, dy2;
		virtual void draw(ConsoleBuffer* cb);
		//virtual Shape* copy();
	};

}


#endif /* SHAPES_H */