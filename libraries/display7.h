
#ifndef DISPLAY7_H
#define	DISPLAY7_H

#include <pic18f4520.h>
#include<xc.h>
#include"car.h"


int indice=0;
int select=0; //1 = dezena

void set_number(int a);
void dp_update();



#endif	/* DISPLAY7_H */

