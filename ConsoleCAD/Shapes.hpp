class IDrawable {
	virtual void Draw();
};

class Point {
private:
	int x, y;
public:
	Point(int x, int y);
};

class Rectangle {
private:
	Point topLeft, bottomRight;
public:
	Rectangle(int x, int y, int width, int length);
};