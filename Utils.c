#include "Domeniu.h"
#include "Infrastructura.h"
#include "Validare.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Utils.h"

void ordonat(Repozitoriu* repo,int sens, ptr_functie functie_comparare)
{
	// functie care ordoneaza repozitoriul dupa un criteriu dat
	// date de intrare: repo - pointer la tip de data Repozitoriu
	//                 sens -numar intreg: 1 pentru crescator, -1 pentru descrescator
	// date de iesire: aux - copie a repozitoriului dat ca parametru cu elementele sortate
	int i, j;
	for (i = 0; i < repo->lungime - 1; i++)
		for (j = i + 1; j < repo->lungime; j++)
		{
			Cheltuieli* c1 = repo->vect[i];
			Cheltuieli* c2 = repo->vect[j];
			if (sens * functie_comparare(c1, c2) > 0)
			{
				Cheltuieli sub = *c1;
				 *c1 = *c2;
				*c2 = sub;
			}
		}
}
