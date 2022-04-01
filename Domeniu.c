#include "Domeniu.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Cheltuieli* creeazaCheltuieli(int z, double s , char* t)
{
	//functie care creeaza o variabila de tip Cheltuieli din parametri dati
	// date de intrare: z(ziua) - numar natural, s(suma) - numar real pozitiv, t(tipul) - sir de caractere
	// date de iesire: ch - variabila de tip Cheltuieli
	Cheltuieli *ch = malloc(sizeof(Cheltuieli));
	ch->ziua = z;
	ch->suma = s;
	ch->tip = malloc((strlen(t) + 1) * sizeof(char));
	strcpy(ch->tip,t);
	return ch;
}

void distrugeCheltuieli(Cheltuieli* ch)
{
	// functie care elibereaza memoria de pe heap de la adresa din variabila ch
	// date de intrare: ch - pointer la tipul de data Cheltuieli
	// date de iesire : -
	free(ch->tip);
	ch->tip = NULL;
	free(ch);
}

Cheltuieli* copieCh(Cheltuieli* ch) {
	//functie care returneaza o copie e variabilei gasite la adresa din ch
	// date de intrare: ch - pointer la variabila de tip Cheltuieli
	// date de iesire : copie a variabilei de tip Cheltuieli
	return creeazaCheltuieli(ch->ziua, ch->suma, ch->tip);
}