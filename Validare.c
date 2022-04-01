#include "Validare.h"
#include "Domeniu.h"
#include <assert.h>
#include <string.h>

void valideaza(Cheltuieli* ch, char* erori)
{
	// functia validare transforma un sir de caractere numit erori in sirul nul daca datele de intrare sunt valide, respectiv in mesaje de eroare
	// care vor fi transmise ulterior daca datele nu sunt valide
	// date de intrare: ch - variabila de tip Cheltuieli
	//                  erori - sir de caractere
	// date de iesire: -
	char* variante[] = { "mancare" , "transport", "telefon&internet","inbracaminte", "altele" };
	strcpy(erori, "");
	int nr_variante = 5;
	if ( ch->suma < 0)
		strcat(erori, "Suma invalida!\n");
	if (ch->ziua <= 0)
		strcat(erori,"Zi invalida!\n");
	int i = 0;
	int ok = 0;
	for (i; i < nr_variante; i++)
	{
		if (strcmp(ch->tip, variante[i]) == 0)
			ok = 1;
	}
	if(ok!=1)
		strcat(erori, "Tip invalid!\n");
}
