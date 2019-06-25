#include "car.h"
#include <conio.h>
#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include "display7.h"

    unsigned int data = 0;

pipe_t pipe_time;
sem_t  s_pipe_time;

pipe_t pipe_start;
sem_t  s_pipe_start;


void micro_setup(){
    TRISB = 0xFF;
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    sem_init(&s_pipe_time, 1);
    pipe_create(&pipe_time, &s_pipe_time);
    sem_init(&s_pipe_start, 1);
    pipe_create(&pipe_start, &s_pipe_start);
    
    sem_init(&s_count, 1);    
    sem_init(&s_time, 1);
    sem_init(&s_started, 1);


}

void task_keyboard(){

    while(1){
        if(b_start == 0){
            if(b_porta == 0){
                sem_wait(&s_started);
                started = 1;
                sem_post(&s_started);

                sem_wait(&s_time);
                sem_wait(&s_count);
                count = time;
                sem_post(&s_count);
                sem_post(&s_time);
            }
        
        lunos_delayTask(100);

        }
        
    }
}

void task_2heat(){//motor prato
    while(1){
        if( started == 1 ){
            m_prato = 1;
            l_luz_interna = 1;
        }else{
            m_prato = 0;
            if(b_porta = 0){
                l_luz_interna = 0;
            }else{
                l_luz_interna = 1;
            }
        }
        
        lunos_delayTask(100);
    }
}


int _mod(int number, int div){
    int result = number;
    while(result >= div){
        result = result - div;
    }
    return result;
}

int _div(int number, int div){
    int result = 0;
    while(number >= div){
        number = number - div;
        result++;
    }
    return result;
}









