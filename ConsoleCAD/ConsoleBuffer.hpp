#include <vector>

typedef std::vector<std::vector<char>> matrix;

class ConsoleBuffer {
private:
	matrix* buffer;
public:
	ConsoleBuffer(int x, int y);
	~ConsoleBuffer();
	matrix* getBuffer();
	char get(int x, int y);
	void set(int x, int y, int val);
};