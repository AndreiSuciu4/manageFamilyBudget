#include "Testare.h"
#include "Domeniu.h"
#include <string.h>
#include <assert.h>
#include <math.h>
#include "Validare.h"
#include "Infrastructura.h"
#include "Service.h"
#include <stdio.h>

void teste_domeniu()
{
	// funcite care efectueaza teste automate pentru elementele din domeniu
	// date de intrare: -
	// date de iesire: -, assertion error daca testul esueaza
	Cheltuieli *ch = creeazaCheltuieli(1, 0.2, "analiza");
	ch->ziua = 1;
	ch->suma = 0.2;
	char sir[] = "analiza";
	assert(ch->ziua == 1);
	assert(fabs(ch->suma-0.2)< 0.0001);
	assert(strcmp(ch->tip, sir) == 0);
	distrugeCheltuieli(ch);
}

void teste_validare()
{
	// funcite care efectueaza teste automate pentru elementele din pachetul validare
	// date de intrare: -
	// date de iesire: -, assertion error daca testul esueaza
	Cheltuieli* ch = creeazaCheltuieli(1, 0.2, "altele");
	char erori[50];
	valideaza(ch, erori);
	assert(strlen(erori) == 0);
	ch->ziua = -3;
	ch->suma = -3;
	strcpy(ch->tip, "");
	valideaza(ch, erori);
	assert(strcmp(erori, "Suma invalida!\nZi invalida!\nTip invalid!\n") == 0);
	distrugeCheltuieli(ch);
}

void teste_infrastructura()
{
	// funcite care efectueaza teste automate pentru elementele din pachetul infrastructura
	// date de intrare: -
	// date de iesire: -, assertion error daca testul esueaza
	Repozitoriu* repo = creeazaRepo();
	Cheltuieli* c1 = creeazaCheltuieli(1, 1, "mancare");
	Cheltuieli* c2 = creeazaCheltuieli(2, 2, "transport");
	Cheltuieli* c3 = creeazaCheltuieli(3, 3, "altele");
	adauga(repo, c1);
	adauga(repo, c2);
	adauga(repo, c3);
	assert(numar_elemente(repo) == 3);
	Repozitoriu* repo_2 = creeazaRepo();
	cauta_dupa_suma(repo, repo_2, 2);
	Cheltuieli* ch = repo_2->vect[0];
	assert(ch->suma == 1);
	assert(strcmp(ch->tip,"mancare") == 0);
	assert(ch->ziua == 1);
	distrugeRepo(repo_2, distrugeCheltuieli);
	Repozitoriu* repo_3 = creeazaRepo();
	cauta_dupa_zi(repo,repo_3, 2);
	Cheltuieli* ch1 = repo_3->vect[0];
	assert(ch1->suma == 1);
	assert(strcmp(ch1->tip, "mancare") == 0);
	assert(ch1->ziua == 1);
	distrugeRepo(repo_3, distrugeCheltuieli);
	Repozitoriu* repo_4 = creeazaRepo();
	cauta_dupa_tip(repo, repo_4, "mancare");
	Cheltuieli* ch2 = repo_4->vect[0];
	assert(ch2->suma == 1);
	assert(strcmp(ch2->tip, "mancare") == 0);
	assert(ch2->ziua == 1);
	distrugeRepo(repo_4, distrugeCheltuieli);
	Cheltuieli* ch_2 = creeazaCheltuieli(2, 2, "transport");
	modifica(repo, 0,ch_2);
	Cheltuieli* ch3 = repo->vect[0];
	assert(ch3->suma == 2);
	assert(strcmp(ch3->tip, "transport") == 0);
	assert(ch3->ziua == 2);
	sterge(repo, 0);
	assert(numar_elemente(repo) == 2);
	distrugeRepo(repo, distrugeCheltuieli);
}

void teste_service()
{

	// funcite care efectueaza teste automate pentru elementele din pachetul service
	// date de intrare: -
	// date de iesire: -, assertion error daca testul esueaza
	Repozitoriu* repo = creeazaRepo();
	Repozitoriu* undo = creeazaRepo();
	int nr = adauga_service(repo, undo, -1, 1, "mancare");
	assert(nr == 1);
	adauga_service(repo, undo, 1, 1, "mancare");
	Cheltuieli* ch1 = repo->vect[0];
	assert(ch1->suma == 1);
	assert(ch1->ziua == 1);
	assert(strcmp(ch1->tip, "mancare") == 0);
	assert(numar_elemente_service(repo) == 1);
	int cod = modifica_service(repo, undo, 0, 2, 2, "transport");
	cod = modifica_service(repo, undo, 10, 2, 2, "altele");
	assert(cod == 1);
	cod = modifica_service(repo, undo, 0, -1, -1, "  ");
	Cheltuieli* ch2 = repo->vect[0];
	assert(ch2->ziua == 2);
	assert(strcmp(ch2->tip, "transport") == 0);
	assert(ch2->suma == 2);
	int nr2 = sterge_service(repo, undo, -1);
	assert(nr2 == 1);
	sterge_service(repo, undo, 0);
	assert(numar_elemente_service(repo) == 0);
	adauga_service(repo, undo, 1, 1, "mancare");
	adauga_service(repo, undo, 2, 2, "transport");
	adauga_service(repo, undo, 3, 3, "altele");
	adauga_service(repo, undo, 4, 4, "altele");
	Repozitoriu* aux = creeazaRepo();
	filtrare_suma(repo, aux, 2);
	Cheltuieli* ch3 = aux->vect[0];
	assert(ch3->suma == 1);
	assert(ch3->ziua == 1);
	assert(strcmp(ch3->tip, "mancare") == 0);
	distrugeRepo(aux, distrugeCheltuieli);
	aux = creeazaRepo();
	filtrare_zi(repo, aux, 2);
	Cheltuieli* ch4 = aux->vect[0];
	assert(ch4->suma == 1);
	assert(ch4->ziua == 1);
	assert(strcmp(ch4->tip, "mancare") == 0);
	distrugeRepo(aux, distrugeCheltuieli);
	aux = creeazaRepo();
	filtrare_tip(repo, aux, "transport");
	Cheltuieli* ch5 = aux->vect[0];
	assert(ch5->suma == 2);
	assert(ch5->ziua == 2);
	assert(strcmp(ch5->tip, "transport") == 0);
	distrugeRepo(aux, distrugeCheltuieli);
	aux = creeazaRepo();
	Repozitoriu* aux2 = creeazaRepo();
	filtrare_tip_suma(repo, aux, aux2, "altele", 10);
	Cheltuieli* ch20 = aux2->vect[0];
	assert(ch20->suma == 3);
	assert(ch20->ziua == 3);
	assert(strcmp(ch20->tip, "altele") == 0);
	distrugeRepo(aux, distrugeCheltuieli);
	distrugeRepo(aux2, distrugeCheltuieli);
	distrugeRepo(undo, distrugereLista);
	distrugeRepo(repo, distrugeCheltuieli);
}

void testeOrdonare()
{
	Repozitoriu* repo = creeazaRepo();
	Repozitoriu* undo = creeazaRepo();
	adauga_service(repo, undo, 1, 5, "mancare");
	adauga_service(repo, undo, 2, 2, "transport");
	adauga_service(repo, undo, 3, 3, "altele");
	adauga_service(repo, undo, 4, 4, "altele");
	Repozitoriu* aux3;
	aux3 = ordonare_suma_crescator(repo);
	Cheltuieli* ch6 = aux3->vect[0];
	Cheltuieli* ch7 = aux3->vect[1];
	Cheltuieli* ch8 = aux3->vect[2];
	assert(ch6->suma == 2);
	assert(ch7->suma == 3);
	assert(ch8->suma == 4);
	distrugeRepo(aux3, distrugeCheltuieli);
	Repozitoriu* aux4;
	aux4 = ordonare_suma_descrescator(repo);
	Cheltuieli* ch9 = aux4->vect[0];
	Cheltuieli* ch10 = aux4->vect[1];
	assert(ch9->suma == 5);
	assert(ch10->suma == 4);
	Repozitoriu* aux5;
	aux5 = ordonare_tip_crescator(repo);
	Cheltuieli* ch12 = aux5->vect[0];
	Cheltuieli* ch13 = aux5->vect[1];
	assert(ch12->suma == 3);
	assert(ch13->suma == 4);
	Repozitoriu* aux6;
	aux6 = ordonare_tip_descrescator(repo);
	Cheltuieli* ch15 = aux6->vect[0];
	assert(ch15->suma == 2);
	distrugeRepo(aux4, distrugeCheltuieli);
	distrugeRepo(aux5, distrugeCheltuieli);
	distrugeRepo(aux6, distrugeCheltuieli);
	distrugeRepo(undo, distrugereLista);
	distrugeRepo(repo, distrugeCheltuieli);
}

void testeListaDeListe()
{
	Repozitoriu* repo = creeazaRepo();
	adauga(repo, creeazaCheltuieli(1, 1, "mancare"));
	Repozitoriu* repo1 = creeazaRepo();
	adauga(repo1, creeazaCheltuieli(2, 10, "altele"));
	Repozitoriu* lista = creeazaRepo();
	adauga(lista, repo);
	assert(numar_elemente(lista) == 1);
	distrugeRepo(repo1, distrugeCheltuieli);
	distrugeRepo(lista, distrugereLista);


}

void testeUndo()
{
	Repozitoriu* repo = creeazaRepo();
	Repozitoriu* undo = creeazaRepo();
	adauga_service(repo, undo, 1, 1, "mancare");
	assert(undo->lungime == 1);
	modifica_service(repo, undo, 0, 2, 2, "transport");
	Repozitoriu* repo2 = undo->vect[1];
	Cheltuieli* ch1 = repo2->vect[0];
	assert(ch1->suma == 1);
	sterge_service(repo, undo, 0);
	Repozitoriu* repo3 = undo->vect[2];
	Cheltuieli* ch2 = repo3->vect[0];
	assert(ch2->suma == 2);
	Repozitoriu* repo5;
    repo5 = undo_service(undo);
	Cheltuieli* ch3 = repo5->vect[0];
	assert(ch3->suma == 2);
	distrugeRepo(repo5, distrugeCheltuieli);
	Repozitoriu* repo6 ;
	repo6 = undo_service(undo);
	Cheltuieli* ch4 = repo6->vect[0];
	assert(ch4->suma == 1);
	distrugeRepo(repo6, distrugeCheltuieli);
	Repozitoriu* repo7;
	repo7 = undo_service(undo);
	assert(numar_elemente_service(repo7) == 0);
	distrugeRepo(repo7, distrugeCheltuieli);
	distrugeRepo(repo, distrugeCheltuieli);
	distrugeRepo(undo, distrugereLista);


}
void ruleaza_teste()
{
	// funcite care ruleaza celelalte functii automate de test din pachetul Testare
	// date de intrare: -
	// date de iesire: -
	teste_domeniu();
	teste_validare();
	teste_infrastructura();
	teste_service();
	testeOrdonare();
	testeListaDeListe();
	testeUndo();
}