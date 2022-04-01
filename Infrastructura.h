#pragma once
#include "Domeniu.h"

typedef void* Element;
typedef void (*distrugereFunctie)(Repozitoriu);
//typedef Element* (*copiereFunctie)(Repozitoriu);
typedef struct Repo {
	//tipul de data Repozitoriu contine un vecotr static cu 100 de elemente de tip Cheltuieli si campul lungime care reprezinta 
	//numarul curent de elemente din vector
	Element* vect;
	int lungime;
	int capacitate;
} Repozitoriu;
// antetele functiilor din pachetul infrastructura care efectueaza operatii asupra repozitoriului
Repozitoriu* creeazaRepo();
void adauga(Repozitoriu*, Element);
void modifica(Repozitoriu*, int, Element);
Repozitoriu* copie(Repozitoriu*);
Repozitoriu* copieLista(Repozitoriu*);
Cheltuieli* getCheltuieli(Repozitoriu*, int);
void sterge(Repozitoriu*, int);
void cauta_dupa_tip(Repozitoriu*, Repozitoriu*, char*);
void cauta_dupa_suma(Repozitoriu*, Repozitoriu*, double);
void cauta_dupa_zi(Repozitoriu*, Repozitoriu*, int);
int numar_elemente(Repozitoriu*);
void distrugeRepo(Repozitoriu*, distrugereFunctie destroyFct);
void distrugereLista(Repozitoriu*);
