#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

struct Object{
	char type;
	int x;
	int y;
}; std::vector <Object> objects;

void SaveIntVector(std::vector<int> o, std::string fileName) {
	std::ofstream file;
	file.open(fileName, std::ios::out | std::ios::binary);
	if (file.is_open()) {
		size_t len = o.size();
		file.write(reinterpret_cast<char*>(&len), sizeof(size_t));
		for (int i{ 0 }; i < len; i++) {
			file.write(reinterpret_cast<char*>(&o[i]), sizeof(int));
			
		}
		file.close();
		std::cout << "Int vector saved." << std::endl;
	}
	else std::cout << "No se ha podido abrir el archivo" <<std::endl;
}

void RecoverIntVector(std::vector<int> &o, std::string fileName) {
	std::ifstream file;
	file.open(fileName, std::ios::in | std::ios::binary);
	if (file.is_open()) {
		o.clear();
		std::cout << "Int vector cleared." << std::endl;
		size_t len;
		int tmp;
		file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
		for (int i{ 0 }; i < len; i++) {
			file.read(reinterpret_cast<char*>(&tmp), sizeof(int));
			o.push_back(tmp);
		}
		file.close();
		std::cout << "Int vector recovered." << std::endl << std::endl;
	}
	else std::cout << "No se ha podido abrir el archivo" << std::endl;
}

void SaveStructVector(std::vector<Object> o, std::string fileName) {
	std::ofstream file;
	file.open(fileName, std::ios::out | std::ios::binary);
	if (file.is_open()) {
		size_t len = o.size();
		file.write(reinterpret_cast<char*>(&len), sizeof(size_t));
		for (int i{ 0 }; i < len; i++) {
			file.write(reinterpret_cast<char*>(&o[i].type), sizeof(char));
			file.write(reinterpret_cast<char*>(&o[i].x), sizeof(int));
			file.write(reinterpret_cast<char*>(&o[i].y), sizeof(int));
		}
		file.close();
		std::cout << "Object vector saved." << std::endl;
	}
	else std::cout << "No se ha podido abrir el archivo" << std::endl;
}

void RecoveStructVector(std::vector<Object> &o, std::string fileName) {
	std::ifstream file;
	file.open(fileName, std::ios::in | std::ios::binary);
	if (file.is_open()) {	
		o.clear();
		std::cout << "Object vector cleared!" << std::endl;
		size_t len;
		Object tmp;
		file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
		for (int i{ 0 }; i < len; i++) {
			file.read(reinterpret_cast<char*>(&tmp.type), sizeof(char));
			file.read(reinterpret_cast<char*>(&tmp.x), sizeof(int));
			file.read(reinterpret_cast<char*>(&tmp.y), sizeof(int));
			o.push_back(tmp);
		}
		file.close();
		std::cout << "Object vector recovered." << std::endl << std::endl;
	}
	else std::cout << "No se ha podido abrir el archivo" << std::endl;
}

int main() {
	std::vector<int> a({ 1,2,3,8,5,6,7,8,9,10 });
	SaveIntVector(a, "TestSaveVector.bin");
	for (int i = 0; i < 10; i++) { a[i] = a[i] + 10; };
	RecoverIntVector(a, "TestSaveVector.bin");
	std::cout << "Recovered Vector: ";

	for (int i = 0; i < a.size(); i++) { std::cout << a[i] << " "; }
	std::cout << std::endl <<std::endl;

	Object tmp;
	int rnd;

	std::vector<Object> b;

	for (int i{ 0 }; i < 6; i++) {
		rnd = (rand() % 96) + 31;
		tmp.type = (char)rnd;
		rnd = rand() % 101;
		tmp.x = rnd;
		rnd = rand() % 101;
		tmp.y = rnd;
		b.push_back(tmp);
	}
	std::cout << std::endl << "Vector objects created!" << std::endl << std::endl;
	
	SaveStructVector(b, "TestSaveVector.bin");
	b.erase(b.begin() + 2); b.erase(b.begin() + 4);
	RecoveStructVector(b, "TestSaveVector.bin");
	
	for (int i{ 0 }; i < 6; i++) {
		std::cout << "Object " << i << ":" << "	" ;
	}std::cout << std::endl;

	for (int i{ 0 }; i < 6; i++) {
		std::cout << "Type: " << b[i].type << "		";	
	}std::cout << std::endl;

	for (int i{ 0 }; i < 6; i++) {
		std::cout << "X: " << b[i].x << "		";
	}std::cout << std::endl;

	for (int i{ 0 }; i < 6; i++) {
		std::cout << "Y: " << b[i].y << "		";
	}std::cout << std::endl << std::endl;

	std::cout << "DONE!" <<std::endl;

	return 0;
}
