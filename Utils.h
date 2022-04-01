#pragma once
#include "Domeniu.h"
#include "Infrastructura.h"
#include "Validare.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int (*ptr_functie)(Cheltuieli*, Cheltuieli*);

void ordonat(Repozitoriu*, int, ptr_functie);
