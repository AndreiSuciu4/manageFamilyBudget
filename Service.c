#include "Domeniu.h"
#include "Infrastructura.h"
#include "Service.h"
#include "Validare.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Utils.h"

int adauga_service(Repozitoriu* repo, Repozitoriu* undo, int z, double s, char t[100])
{
	// adauga un element la repozitoriu si il valideaza
	// date de intrare: repo - pointer la tip de data Repozitoriu
	// 	   	            undo-pointer la tipul Repozitoriu
	//					z - ziua , numar intreg
	//                  s - suma, numar real
	//                  t - tipul , sir de caractere
	// date de iesire: -
	char* erori = malloc(50 * sizeof(char));
	Cheltuieli* ch = creeazaCheltuieli(z, s, t);
	valideaza(ch, erori);
	int cod;
	if (strlen(erori) == 0)
	{
		adauga(undo, copie(repo));
		adauga(repo, ch);
		free(erori);
		cod = 0;
	}
	else
	{
		distrugeCheltuieli(ch);
		free(erori);
		cod = 1;
	}
	return cod;
}

int modifica_service(Repozitoriu* repo, Repozitoriu* undo, int indice, int z, double s, char t[100])
{
	// modifica un element din repozitoriu si il valideaza
	// date de intrare: repo - pointer la tip de data Repozitoriu
	// 	                undo-pointer la tipul Repozitoriu
	//                  indice - indexul elementului care va fi modificat
	//					z - ziua , numar intreg
	//                  s - suma, numar real
	//                  t - tipul , sir de caractere
	// date de iesire: 0 daca este in regula, 1 sau 2 in caz contrar
	char* erori = malloc(50 * sizeof(char));
	int cod;
	Cheltuieli* ch = creeazaCheltuieli(z, s, t);
	valideaza(ch, erori);
	if (indice < 0 || indice >= numar_elemente(repo))
	{
		distrugeCheltuieli(ch);
		free(erori);
		cod = 1;
	}
	else if (strlen(erori) != 0)
	{
		distrugeCheltuieli(ch);
		free(erori);
		cod = 2;
	}
	else
	{
		adauga(undo, copie(repo));
		modifica(repo, indice, ch); 
		free(erori);
		cod = 0;
	}
	return cod;
}
int sterge_service(Repozitoriu* repo, Repozitoriu* undo, int indice)
{
	// sterge un element din repozitoriu, daca indicele corespunde unui element
	// date de intrare: repo - pointer la tip de data Repozitoriu
	// 	                undo-pointer la tipul Repozitoriu
	//					indice - numar intreg, indicele elementului care va fi sters
	// date de iesire: -
	int cod;
	if (indice < 0 || indice >= numar_elemente(repo))
		cod = 1;
	else
	{
		adauga(undo, copie(repo));
		sterge(repo, indice);
		cod = 0;
	}
	return cod;
}

void filtrare_tip(Repozitoriu* repo, Repozitoriu* repo_t, char* parametru)
{
	// cauta elemente din repozitoriu dupa tip, toate elementele care se potrivesc cautarii sunt adaugate in vectorul auxiliar
	// date de intrare: repo - pointer la tip de data Repozitoriu
	//                  repo_t - pointer la tip de data Repozitoriu, vector auxiliar cu rezultatele cautatii
	//					parametru - sirul de caractere care impune conditia de cautare
	// date de iesire: -
	cauta_dupa_tip(repo, repo_t, parametru);
}

void filtrare_tip_suma(Repozitoriu*repo, Repozitoriu*repo_t, Repozitoriu* repo_s, char* tip, double suma)
// cauta elemente din repozitoriu dupa suma,si tip toate elementele care se potrivesc cautarii sunt adaugate in vectorul auxiliar
// date de intrare: repo - pointer la tip de data Repozitoriu
//                  repo_s - pointer la tip de data Repozitoriu, vector auxiliar cu rezultatele cautatii
//                  repo_t-pointer la tipul Repozitoriu
//					parametru - numar real care impune conditia de cautare
// date de iesire: -
{
	cauta_dupa_tip(repo, repo_t, tip);
	cauta_dupa_suma(repo_t, repo_s, suma);
}

void filtrare_suma(Repozitoriu* repo, Repozitoriu* repo_s, double parametru)
{
	// cauta elemente din repozitoriu dupa suma, toate elementele care se potrivesc cautarii sunt adaugate in vectorul auxiliar
	// date de intrare: repo - pointer la tip de data Repozitoriu
	//                  repo_s - pointer la tip de data Repozitoriu, vector auxiliar cu rezultatele cautatii
	//					parametru - numar real care impune conditia de cautare
	// date de iesire: -
	cauta_dupa_suma(repo, repo_s, parametru);
}

void filtrare_zi(Repozitoriu* repo, Repozitoriu* repo_z, int parametru)
{
	// cauta elemente din repozitoriu dupa zi, toate elementele care se potrivesc cautarii sunt adaugate in vectorul auxiliar
	// date de intrare: repo - pointer la tip de data Repozitoriu
	//                  repo_z - pointer la tip de data Repozitoriu, vector auxiliar cu rezultatele cautatii
	//					parametru - numar natural care impune conditia de cautare
	// date de iesire: -
	cauta_dupa_zi(repo, repo_z, parametru);
}

int compara_sir(Cheltuieli* c1, Cheltuieli* c2)
{
	// functie care compara campurile tip ale variabilelor c1 si c2 si returneaza 1 daca valoarea campului lui c1 este mai mare lexicografic 
	// decat valoarea campului lui c2, returneaza -1 in caz contrar
	// date de intrare: c1, c2, variabile de tip cheltuiala
	// date de iesire: 1 sau -1, numar intreg
	return strcmp(c1->tip, c2->tip);
}

int compara_numar(Cheltuieli* c1, Cheltuieli* c2)
{
	// functie care compara campurile suma ale variabilelor c1 si c2 si returneaza 1 daca valoarea campului lui c1 este mai mare decat valoarea campului lui c2,
	// returneaza -1 in caz contrar
	// date de intrare: c1, c2, variabile de tip cheltuiala
	// date de iesire: 1 sau -1, numar intreg
	int cod;
	if (c1->suma > c2->suma)
		cod = 1;
	else
		cod = -1;
	return cod;
}

Repozitoriu* ordonare_tip_descrescator(Repozitoriu* lista)
/*returneaza lista sortata descrescator dupa tip
* date de intrare:-lista-poiter la Repozitoriu
* date de iesire:-list-poiter la Repozitoriu
*/
{
	Repozitoriu* list = copie(lista);
	ordonat(list, -1, compara_sir);
	return list;
}

Repozitoriu* ordonare_tip_crescator(Repozitoriu* lista)
/*returneaza lista sortata crescator dupa tip
* date de intrare:-lista-poiter la Repozitoriu
* date de iesire:-list-poiter la Repozitoriu
*/
{
	Repozitoriu* list = copie(lista);
	ordonat(list, 1, compara_sir);
	return list;
}

Repozitoriu* ordonare_suma_crescator(Repozitoriu* lista)
/*returneaza lista sortata crescator dupa suma
* date de intrare:-lista-poiter la Repozitoriu
* date de iesire:-list-poiter la Repozitoriu
*/
{
	Repozitoriu* list = copie(lista);
	ordonat(list, 1, compara_numar);
	return list;

}

Repozitoriu* ordonare_suma_descrescator(Repozitoriu* lista)
/*returneaza lista sortata descrescator dupa suma
* date de intrare:-lista-poiter la Repozitoriu
* date de iesire:-list-poiter la Repozitoriu
*/
{
	Repozitoriu* list = copie(lista);
	ordonat(list, -1, compara_numar);
	return list;

}


int numar_elemente_service(Repozitoriu* repo)
{
	// functie care returneaza numarul de elemente din repozitoriu
	// date de intrare: repo - pointer la tip de data Repozitoriu
	// date de iesire: numarul de elemente din repzitoriu, numar natural
	return numar_elemente(repo);
}

Repozitoriu* undo_service(Repozitoriu*undo)
/*functi de undo
* date de intrare:-undo-pointer catre Repozitoriu
* date de iesire-repo2-pointer catre Repozitoriu daca lungimea lui undo este 1
*			    -repo2-pointer catre Repozitoriu
*/
{
	Repozitoriu* repo1 = copie(undo->vect[undo->lungime-1]);
	distrugeRepo(undo->vect[undo->lungime - 1], distrugeCheltuieli);
	undo->lungime = undo->lungime - 1;
	return repo1;
}