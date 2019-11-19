#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void SaveVector(std::vector<int> o, std::string fileName) {
	std::ofstream file;
	file.open(fileName, std::ios::in | std::ios::binary);
	if (file.is_open()) {
		size_t len = o.size();
		file.write(reinterpret_cast<char*>(&len), sizeof(size_t));
		for (int i{ 0 }; i < len; i++) {
			file.write(reinterpret_cast<char*>(&o[i]), sizeof(int));
		}

		file.close();
	}
	else std::cout << "No se ha podido abrir el archivo";
}

void RecoverVector(std::vector<int> &o, std::string fileName) {
	std::ifstream file;
	file.open(fileName, std::ios::in | std::ios::binary);
	if (file.is_open()) {
		o.clear();
		size_t len = o.size();
		file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
		for (int i{ 0 }; i < len; i++) {
			//file.read((o.push_back), sizeof(int));
		};

		file.close();
	}
	else std::cout << "No se ha podido abrir el archivo";
}

int main() {
	std::vector<int> a({ 1,2,3,4,5,6,7,8,9,10 });
	SaveVector(a, "TestSaveVector.bin");
	for (int i = 0; i < 10; i++) { a[i] = a[i] + 10; };
	RecoverVector(a, "TestSaveVector.bin");
	for (int i = 0; i < 10; i++) { std::cout << a[i]; };	return 0;
}
