#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Domeniu.h"
#include "Testare.h"
#include "Validare.h"
#include <assert.h>
#include "Infrastructura.h"
#include "Prezentare.h"
#include "saptamana_3_oop.h"

void meniu()
{
	printf("Optiunti:\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("1-Adauga un element- \"adaugare\" \n");
	printf("2-Sterge un element- \"stergere\" \n");
	printf("3-Modifica un element- \"modificare\" \n");
	printf("4-Filtreaza dupa datele anterioare unei zile anume a lunii- \"filtrare_zi\" \n");
	printf("5-Filtreaza dupa sumele mai mici sau egale cu suma introdusa-  \"filtrare_suma\" \n");
	printf("6-Filtreaza dupa un anume tip de cheltuiala- \"filtrare_tip\" \n");
	printf("7-Ordoneaza lista dupa tip sau dupa suma crescator/ descrescator-\"ordoneaza\"+ \"tip\"/\"suma\"+ 1/-1 \n");
	printf("8-Undo\n");
	printf("9-Afisare\n");
	printf("10-Filtrare dupa un anumit tip de cheltuiala si cu sumele mai mici sau egale cu suma introdusa - \"filtrare_tip_suma\"\n");
	printf("11-Iesire - \"exit\"\n");
	printf("12-adaugare_10\n");
	printf("------------------------------------------------------------------------------------------------------------- \n");
}

void run()
{
	Repozitoriu* repo = creeazaRepo();
	Repozitoriu* undo = creeazaRepo();
	char* actiuni[] = { "adaugare", "stergere", "modificare", "filtrare_zi","filtrare_suma","filtrare_tip","ordonare" ,"undo","afisare","filtrare_tip_suma","exit","adaugare_10" };
	int nr_optiuni = 12;
	int i = 0;
	int existent = 0;
	while (1)
	{
		existent = 0;
		printf("Introduceti o optiune: ");
		char optiune[20];
		scanf_s("%19s", optiune, (unsigned)_countof(optiune));
		for (i = 0; i < nr_optiuni; i++)
			if (strcmp(optiune, actiuni[i]) == 0)
			{
				existent = 1;
				switch (i) {
				case 0:
					adauga_ui(repo, undo);
					break;
				case 1:
					sterge_ui(repo, undo);
					break;
				case 2:
					modifica_ui(repo, undo);
					break;
				case 3:
					filtrare_zi_ui(repo);
					break;
				case 4:
					filtrare_suma_ui(repo);
					break;
				case 5:
					filtrare_tip_ui(repo);
					break;
				case 6:
					ordonare_ui(repo);
					break;
				case 7:
					undo_ui(&repo, undo);
					break;
				case 8:
					afisare_ui(repo);
					break;
				case 9:
					filtrare_tip_suma_ui(repo);
					break;
				case 10:
					distrugeRepo(repo, distrugeCheltuieli);
					distrugeRepo(undo, distrugereLista);
					return;

				case 11:
					adauga_10_ui(repo, undo);
					break;
				}
			}
		if (!existent)
			printf("Optiunea nu este valida.Alegeti alta optiune.\n");
	}
}
int main()
{	// functia main unde este rulat programul principal cu meniul intr-o bucla infinita, pentru a iesi se foloseste functionalitatea exit
	ruleaza_teste();
	meniu();
	run();
	_CrtDumpMemoryLeaks();
	return;
}
