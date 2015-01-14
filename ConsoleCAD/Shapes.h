class Point {
private:
	int x, y;
	char c;
	unsigned short color;
public:
	Point(int x, int y, char c, unsigned short color);
	void Show();
	void Hide();
	void MoveX(int dx);
	void MoveY(int dy);
	void MoveXY(int dx, int dy);
	int getX();
	int getY();
	int getC();
	void setC(int c);
	int getColor();
	void setColor(int color);
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