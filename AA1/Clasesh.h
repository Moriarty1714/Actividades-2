#include <iostream>
#include <map>
#include <string>
#include <vector>

class Arma {
	std::string nombre;
	std::string categoria;
	int alcance;

	Arma(std::string n, std::string c, int a) {
		nombre = n;
		categoria = c;
		alcance = a;
	}
};

class Enemigo {
	std::string tipo;
	int vida;
	int ataque;
	int defensa;
	float fAtaque;
	int xp;
	int nArmas;
	std::vector<Arma> arma;

	Enemigo(std::string n, std::string t, int v, int a, int d, float fA, int x, int nA, std::vector<Arma> ar) {
		nombre = n;
		tipo = t;
		vida = v;
		ataque = a;
		defensa = d;
		fAtaque = fA;
		xp = x;
		nArmas = nA;
		arma = ar;
	}
};
