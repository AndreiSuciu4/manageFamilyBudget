#include <assert.h>
#include "Domeniu.h"
#include "Infrastructura.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Repozitoriu* creeazaRepo()
{
	// functie care returneaza un element de tip Repozitoriu cu capacitate 2 si 0 elemente la momentul generarii
	// date de intrare: -
	// date de iesire: repo - element de tip Repozitoriu
	Repozitoriu* repo;
	repo = malloc(sizeof(Repozitoriu));
	repo->capacitate = 2;
	repo->lungime = 0;
	repo->vect = malloc(sizeof(Element) * repo->capacitate);
	return repo;
}
void distrugereLista(Repozitoriu* list)
/*functie de distrugere a listei de liste
* date de intrare:- list-pointer la tipul Repozitoriu
* date de iesire:-
*/
{
	distrugeRepo(list, distrugeCheltuieli);
}
void distrugeRepo(Repozitoriu* repo, distrugereFunctie destroyFct)
{
	// functie care distruge repozitoriu si elibereaza memoria alocata pe heap
	// date de intrare : repo - pointer la Repozitoriu
	//					destroyFct-de tip distrugereFunctie
	// date de iesire: -
	int i;
	for (i = 0; i < repo->lungime; i++)
	{
		destroyFct(repo->vect[i]);
	}
	free(repo->vect);
	free(repo);
}

void creste_cap(Repozitoriu* repo)
{
	// functie care creste capacitatea vectorului dinamic daca acesta are toate pozitiile ocupate(capacitatea este egala cu lungimea)
	// date de intrare: repo - pointer la Repozitoriu
	// date de iesire : -
	if (repo->lungime >= repo->capacitate)
	{
		int cap2 = repo->capacitate + 2;
		Element* vect2 = malloc(cap2 * sizeof(Element));
		int i;
		for (i = 0; i < repo->lungime; i++)
			vect2[i] = repo->vect[i];
		free(repo->vect);
		repo->capacitate = cap2;
		repo->vect = vect2;

	}
}

void adauga(Repozitoriu* repo, Element el)
{
	// adauga un element la repozitoriu
	// date de intrare: repo - pointer la tip de data Repozitoriu
	//					el - variabila de tip Element
	// date de iesire: -
	creste_cap(repo);
	repo->vect[repo->lungime] = el;
	repo->lungime = repo->lungime + 1;
}

Repozitoriu* copie(Repozitoriu* repo) {
	// functie care returneaza o copie a repozitoriului gasit la adresa din variabila repo
	// date de intrare: repo - pointer la Repozitoriu
	// date de iesire: rez - copie a repozitoriului
	Repozitoriu* rez = creeazaRepo();
	for (int i = 0; i < repo->lungime; i++) {
		Element ch = repo->vect[i];
		adauga(rez, copieCh(ch));

	}
	return rez;
}

Cheltuieli* getCheltuieli(Repozitoriu* repo, int i)
/*returneaza un pointer la cheltuieli
* date de intrare:repo-pointer la Repozitoriu
*					  -i-tip int
* date de iesire:-c-tip pointer la Cheltuieli
*/
{
	Cheltuieli* c = copieCh(repo->vect[i]);
	return c;
}

void modifica(Repozitoriu* repo ,int indice , Element el)
{
	// modifica un element din repozitoriu
	// date de intrare: repo - pointer la tip de data Repozitoriu
	//                  indice - numar intreg, indicele elementului modificat
	//					ch - variabila de tip Element
	// date de iesire: -
	if (indice < repo->lungime)
	{
		distrugeCheltuieli(repo->vect[indice]);
		repo->vect[indice] = el;
	}
}
void sterge(Repozitoriu* repo, int indice)
{
	// sterge un element din repozitoriu
	// date de intrare: repo - pointer la tip de data Repozitoriu
	//					indice - numar intreg, indicele elementului care va fi sters
	// date de iesire: -
	if (indice < repo->lungime)
	{
		Element* vect2 = malloc(repo->capacitate * sizeof(Element));
		int i,ct=0;
		for (i = 0; i < repo->lungime; i++)
			if(i!=indice)
			vect2[ct++] = repo->vect[i];
		distrugeCheltuieli(repo->vect[indice]);
		free(repo->vect);
		repo->vect = vect2;
		repo->lungime = ct;
	}
}

void cauta_dupa_tip(Repozitoriu* repo, Repozitoriu* repo_t,char* tipul)
{
	// cauta elemente din repozitoriu dupa tip, toate elementele care se potrivesc cautarii sunt adaugate in vectorul auxiliar
	// date de intrare: repo - pointer la tip de data Repozitoriu
	//                  repo_t - pointer la tip de data Repozitoriu, vector auxiliar cu rezultatele cautatii
	//					tipul - sirul de caractere care impune conditia de cautare
	// date de iesire: -
	int i = 0;
	for (i; i < repo->lungime; i++)
	{
		Cheltuieli* ch = getCheltuieli(repo, i);
		char* auxiliar = ch->tip;
		if (strcmp(auxiliar, tipul) == 0)
		{
			Cheltuieli* c = copieCh(repo->vect[i]);
			adauga(repo_t, c);
		}
		distrugeCheltuieli(ch);
	}
		
}

void cauta_dupa_suma(Repozitoriu* repo, Repozitoriu* repo_s, double suma)
{
	// cauta elemente din repozitoriu dupa suma, toate elementele care se potrivesc cautarii sunt adaugate in vectorul auxiliar
	// date de intrare: repo - pointer la tip de data Repozitoriu
	//                  repo_s - pointer la tip de data Repozitoriu, vector auxiliar cu rezultatele cautatii
	//					suma - numar real care impune conditia de cautare
	// date de iesire: -
	int i;
	for (i = 0; i < repo->lungime; i++)
	{
		Cheltuieli* ch = getCheltuieli(repo, i);
		if (ch->suma <= suma)
		{
			Cheltuieli* c = copieCh(repo->vect[i]);
			adauga(repo_s, c);
		}
		distrugeCheltuieli(ch);
	}
}

void cauta_dupa_zi(Repozitoriu* repo, Repozitoriu* repo_z, int Ziua)
{
	// cauta elemente din repozitoriu dupa zi, toate elementele care se potrivesc cautarii sunt adaugate in vectorul auxiliar
	// date de intrare: repo - pointer la tip de data Repozitoriu
	//                  repo_z - pointer la tip de data Repozitoriu, vector auxiliar cu rezultatele cautatii
	//					ziua - numar natural care impune conditia de cautare
	// date de iesire: -
	int i = 0;
	for (i = 0; i < repo->lungime; i++)
	{
		Cheltuieli* ch = getCheltuieli(repo, i);
		if (ch->ziua < Ziua)
		{
			Cheltuieli* c = copieCh(repo->vect[i]);
			adauga(repo_z, c);
		}
		distrugeCheltuieli(ch);
	}
}

int numar_elemente(Repozitoriu* repo)
{
	// functie care returneaza numarul de elemente din repozitoriu
	// date de intrare: repo - pointer la tip de data Repozitoriu
	// date de iesire: numarul de elemente din repzitoriu, numar natural
	return repo->lungime;
}