#ifndef car_h
#define car_h

#include<xc.h>
#include<stdlib.h>
#include "kernel.h"
#include <pic18f4520.h>
#include "pipe.h"
#include "semaphore.h"
#include "display7.h"


#define b_stop        PORTBbits.RB1
#define b_10s         PORTBbits.RB2
#define b_60s         PORTBbits.RB3
#define b_porta       PORTBbits.RB4
#define b_start       PORTBbits.RB5

#define m_prato       PORTDbits.RD2
#define l_luz_interna PORTDbits.RD3



void micro_setup();
void task_2heat();
void task_keyboard();
void task_display();

int _mod(int number, int div);
int _div(int number, int div);


unsigned int started = 0;
unsigned int count = 0;
unsigned int time = 0;
unsigned int dezena=0;
unsigned int unidade=0;

sem_t s_count;
sem_t s_time;
sem_t s_started;






#endif