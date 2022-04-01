#pragma once
#include "Infrastructura.h"

int adauga_service( Repozitoriu*, Repozitoriu*, int, double, char[100]);
int modifica_service( Repozitoriu*, Repozitoriu*, int, int, double, char[100]);
int sterge_service( Repozitoriu*, Repozitoriu*, int);
void filtrare_tip( Repozitoriu*,Repozitoriu*, char*);
void filtrare_suma( Repozitoriu*, Repozitoriu*, double);
void filtrare_zi( Repozitoriu*, Repozitoriu*, int);
void filtrare_tip_suma(Repozitoriu*, Repozitoriu*,Repozitoriu*, char*, double);
int numar_elemente_service(Repozitoriu*);
Repozitoriu* ordonare_suma_crescator(Repozitoriu*);
Repozitoriu* ordonare_suma_descrescator(Repozitoriu*);
Repozitoriu* ordonare_tip_descrescator(Repozitoriu*);
Repozitoriu* ordonare_tip_crescator(Repozitoriu*);
Repozitoriu* undo_service( Repozitoriu*);