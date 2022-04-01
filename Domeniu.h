#pragma once

typedef struct{
	// un tip de data numit Cheltuieli care se caracterizeaza prin :
	// ziua -numar intreg strict pozitiv
	// suma - numar real pozitiv
	// tip - sir de  caractere
	int ziua;
	double suma;
	char *tip;
} Cheltuieli;
Cheltuieli* creeazaCheltuieli(int, double, char*);
void distrugeCheltuieli(Cheltuieli*);
Cheltuieli* copieCh(Cheltuieli*);
