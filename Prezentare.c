#include "Prezentare.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void filtrare_suma_ui(Repozitoriu* repo)
{
	// functie de filtrare dupa suma 
	// date de intrare: repo - pointer la tip de data Repozitoriu
	// date de iesire : -
	double suma;
	printf("Introduceti suma: ");
	scanf_s("%lf", &suma);
	Repozitoriu* repo_s = creeazaRepo();
	filtrare_suma(repo, repo_s, suma);
	if (numar_elemente_service(repo_s) == 0)
		printf("Nu exista elemente de acest tip\n");
	else
	{
		int i = 0;
		for (i; i < numar_elemente_service(repo_s); i++)
		{
			Cheltuieli* c=repo_s->vect[i];
			printf("Ziua: %d   Tipul: %s \n", c->ziua, c->tip);
		}
	}
	distrugeRepo(repo_s, distrugeCheltuieli);
}
void filtrare_zi_ui(Repozitoriu* repo)
{
	// functie de filtrare dupa zi
	// date de intrare: repo - pointer la tip de data Repozitoriu
	// date de iesire : -
	int zi;
	printf("Introduceti ziua: ");
	scanf_s("%d", &zi);
	Repozitoriu* repo_z = creeazaRepo();
	filtrare_zi(repo, repo_z, zi);
	if (numar_elemente_service(repo_z) == 0)
		printf("Nu exista elemente de acest tip\n");
	else
	{
		int i = 0;
		for (i; i < numar_elemente_service(repo_z); i++)
		{
			Cheltuieli* c = repo_z->vect[i];
			printf("Suma: %lf  Tipul: %s \n", c->suma,  c->tip);
		}
	}
	distrugeRepo(repo_z, distrugeCheltuieli);
}

void filtrare_tip_suma_ui(Repozitoriu* repo)
{
	// functie de filtrare dupa zi si suma
	// date de intrare: repo - pointer la tip de data Repozitoriu
	// date de iesire : -

	char tipul[100];
	double suma;
	printf("Introduceti tipul: ");
	scanf_s("%s", tipul, (unsigned)_countof(tipul));
	printf("Introduceti suma: ");
	scanf_s("%lf", &suma);
	Repozitoriu* repo_t = creeazaRepo();
	Repozitoriu* repo_s = creeazaRepo();
	filtrare_tip_suma(repo, repo_t,repo_s, tipul, suma);
	if (numar_elemente_service(repo_s) == 0)
		printf("Nu exista elemente de acest tip\n");
	else
	{
		int i = 0;
		for (i; i < numar_elemente_service(repo_s); i++)
		{
			Cheltuieli* c = repo_s->vect[i];
			printf("Suma: %lf  Ziua: %d \n", c->suma, c->ziua);
		}
	}
	distrugeRepo(repo_t, distrugeCheltuieli);
	distrugeRepo(repo_s, distrugeCheltuieli);
}

void filtrare_tip_ui(Repozitoriu* repo) 
{
	// functie de filtrare dupa tip 
	// date de intrare: repo - pointer la tip de data Repozitoriu
	// date de iesire : -
	char tipul[100];
	printf("Introduceti tipul: ");
	scanf_s("%s", tipul,(unsigned)_countof(tipul));
	Repozitoriu* repo_t = creeazaRepo();
	filtrare_tip(repo, repo_t,tipul);
	if (numar_elemente_service(repo_t) == 0)
		printf("Nu exista elemente de acest tip\n");
	else
	{
		int i = 0;
		for (i; i < numar_elemente_service(repo_t); i++)
		{
			Cheltuieli* c = repo_t->vect[i];
			printf("Suma: %lf  Ziua: %d \n", c->suma, c->ziua);
		}
	}
	distrugeRepo(repo_t, distrugeCheltuieli);
}

void ordonare_ui(Repozitoriu* repo)
{
	// functie care ordoneaza elementele din repozitoriu
	// date de intrare: repo - pointer la tip de data Repozitoriu
	// date de iesire : -
	char criteriu[10];
	int sens = 1;
	printf("Introduceti criteriul(suma/tip): ");
	scanf_s("%s", criteriu, (unsigned)_countof(criteriu));
	printf("Introudceti sensul(1 pentru crescator, -1 pentru descrescator): ");
	scanf_s("%d", &sens);
	if (strcmp(criteriu, "suma") == 0 && sens == 1)
	{
		Repozitoriu* aux = ordonare_suma_crescator(repo);
		afisare_ui(aux);
		distrugeRepo(aux, distrugeCheltuieli);
	}

	if (strcmp(criteriu, "suma") == 0 && sens == -1)
	{
		Repozitoriu* aux1 = ordonare_suma_descrescator(repo);
		afisare_ui(aux1);
		distrugeRepo(aux1, distrugeCheltuieli);
	}

	if (strcmp(criteriu, "tip") == 0 && sens == 1)
	{
		Repozitoriu* aux2 = ordonare_tip_crescator(repo);
		afisare_ui(aux2);
		distrugeRepo(aux2, distrugeCheltuieli);
	}

	if (strcmp(criteriu, "tip") == 0 && sens == -1)
	{
		Repozitoriu* aux3 = ordonare_tip_descrescator(repo);
		afisare_ui(aux3);
		distrugeRepo(aux3, distrugeCheltuieli);
	}

}

void sterge_ui(Repozitoriu* repo, Repozitoriu* undo)
{
	// functie care sterge un element din repozitoriu
	// date de intrare: repo - pointer la tip de data Repozitoriu
	// 	                undo-pointer la tipul Repozitoriu
	// date de iesire : -
	int indice;
	printf("Introduceti indicele: ");
	scanf_s("%d", &indice);
	int cod =sterge_service(repo,undo, indice);
	if(cod ==1)
		printf("Indice invalid!\n");
}
void modifica_ui(Repozitoriu* repo, Repozitoriu* undo)
{
	// functie care modifica un element din repozitoriu
	// date de intrare: repo - pointer la tip de data Repozitoriu
	// 	               undo-pointer la tipul Repozitoriu
	// date de iesire : -
	int zi, indice;
	double suma;
	char tipul[100];
	printf("Introduceti indicele: ");
	scanf_s("%d", &indice);
	printf("Introduceti ziua: ");
	scanf_s("%d", &zi);
	printf("Introduceti suma: ");
	scanf_s("%lf", &suma);
	printf("Introduceti tipul: ");
	scanf_s("%s", tipul,(unsigned)_countof(tipul));
	int cod =modifica_service(repo,undo, indice, zi, suma, tipul);
	if (cod == 0)
		return;
	if(cod == 1)
		printf("Indice invalid!\n");
	else if(cod ==2)
		printf("Date incorecte!\n");
}
void adauga_ui(Repozitoriu* repo, Repozitoriu* undo)
{
	// functie care adauga un element in repozitoriu
	// date de intrare: repo - pointer la tip de data Repozitoriu
	//                 undo-pointer la tipul Repozitoriu
	// date de iesire : -
	int zi;
	double suma;
	char tipul[100];
	printf("Introduceti ziua: ");	
	scanf_s("%d", &zi);
	printf("Introduceti suma: ");
	scanf_s("%lf", &suma);
	printf("Introduceti tipul: ");
	scanf_s("%s", tipul, (unsigned)_countof(tipul));
	int cod =adauga_service(repo,undo, zi, suma, tipul);
	if(cod ==1)
		printf("Date incorecte!\n");
}
void undo_ui(Repozitoriu** repo, Repozitoriu* undo)
/*functie de undo
* date de inrare:-repo -pointer la pointer la tipul Repozitoriu
* 	 	                undo-pointer la tipul Repozitoriu
date de iesire:-
*/
{
	if (undo->lungime == 0)
	{  
		printf("nu se mai poate face undo\n");
		return;
	}
	distrugeRepo(*repo, distrugeCheltuieli);
	*repo = undo_service(undo);
}

void afisare_ui(Repozitoriu*repo)
/*functie de afisare
* date de intrare:-repo-pinter la Repozitoriu
* date de iesire:-
*/
{
	for (int i = 0; i < repo->lungime; i++)
	{
		Cheltuieli* c = repo->vect[i];
		printf("%d-Ziua: %d  Suma: %lf  Tipul: %s \n",i, c->ziua, c->suma, c->tip);
	}
}

void adauga_10_ui(Repozitoriu*repo,Repozitoriu*undo)
{
	adauga_service(repo,undo, 1, 100, "mancare");
	adauga_service(repo, undo, 2, 120, "imbracaminte");
	adauga_service(repo, undo, 9, 1000, "altele");
	adauga_service(repo, undo, 4, 700, "mancare");
	adauga_service(repo, undo, 5, 90, "transport");
	adauga_service(repo, undo, 12, 60, "transport");
	adauga_service(repo, undo, 30, 30, "mancare");
	adauga_service(repo, undo, 21, 740, "telefon&internet");
	adauga_service(repo, undo, 13, 520, "altele");
	adauga_service(repo, undo, 22, 310, "mancare");

}