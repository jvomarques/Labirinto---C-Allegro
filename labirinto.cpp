#include <iostream>
#include "labirinto.h"
using namespace std;

void Labirinto::set(char campo) {
	this->campo = campo;
}

char Labirinto::get() {
	return this->campo;
}

void Labirinto::show_dados() {
	
	cout << this->campo << " ";
}
