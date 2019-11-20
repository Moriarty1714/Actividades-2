#include <iostream>
#include <fstream>
#include <stdio.h>
#include <exception>

class BufferedOutput
{
public:
	// Return number of bytes written by any object of this class.
	short BytesWritten()
	{
		return bytecount;
	}

	// Reset the counter.
	static void ResetCount()
	{
		bytecount = 0;
	}

	// Static member declaration.
	static long bytecount;
};

// Define bytecount in file scope.


class Figure{
protected:
	int perimetre;
public:
	static int area;

	virtual void Draw() = 0;
	Figure(int p) {
		perimetre = p;
	}
	
};
int Figure::area = 10;

class Square :public Figure {
public:
	static int height;
	int width;
public:
	Square(int h, int w, int p):Figure(p) {
		height = h;
		width = w;
	}
	void Draw() {
		std::cout << "This is a Square with " << height << "cm height and "<< width <<"cm widht" << std::endl;
	}
	static void SeguirJugador() {
		std::cout << "Seguimos al jugador!";
	}
};
int Square::height = 0;

class Circle :public Figure {
	int diametro;
public:
	Circle(int d, int p) :Figure( p) {
		diametro = d;
	}

	void Draw() {
		std::cout << "This is a Circle with " << diametro << "cm diametro" << std::endl;
	}
};

int main() {
	
	Figure *f;
	f = new Circle(3,5);
	f->Draw();
	delete(f);
	f = new Square(4, 6, 7);
	f->Draw();
	delete(f);
	Figure *a = new Square(4, 3, 1); Figure *b = new Square(4, 3, 1);  Figure *c = new Square(4, 3, 1); Figure *d = new Circle(3, 1); Figure *q=new Circle(2, 1);
	Square::SeguirJugador();

	return 0;
};