/**
 * LunOS - Luan Operating System
 */

#include <pic18f4520.h>

#include "int0_test.h"
#include "kernel.h"
#include "car.h"

extern t_r_queue ready_queue;
int quantum = QUANTUM;
int timer_index = 0;

void config_INT0() {
  TRISDbits.RD0 = 0;
  INTCONbits.GIE = 1;
  
  INTCONbits.PEIE_GIEL = 1; //peripheral interrupt
  INTCONbits.GIEL = 1;  //peripheral interrupt
  
  INTCONbits.INT0E = 1;
  INTCONbits.INT0IE = 1;
  INTCONbits.INT0IF = 0;
  INTCON2bits.RBPU = 0;
  INTCON2bits.INTEDG0 = 1;
  
}

void config_timer0() {
  // Timer
  // Configuração para o timer estourar a cada
  // 4 ms
  // Configuração considerando o timer 0 8 bits
  
  T0CONbits.T0CS = 0;
  T0CONbits.PSA = 0;
  T0CONbits.T0PS = 0b111;
  INTCONbits.PEIE = 1;
  INTCONbits.TMR0IE = 1;
  TMR0L = 252;
}

//void interrupt() ISR_Int0(void) {
  //DISABLE_ALL_INTERRUPTS();

  //if (INTCONbits.INT0IF) {
  //  PORTDbits.RD0 = 1;
  //  INTCONbits.INT0IF = 0;
  //  SAVE_CONTEXT(READY);
    // Decrementa o tempo de espera por delay de cada
    // tarefa que está na fila de aptos em estado de 
       // WAITING
   // delay_decrement();
  //  ready_queue.task_running = round_robin();
   // PORTDbits.RD0 = 0;
    //RESTORE_CONTEXT(RUNNING);
  //}

  //ENABLE_ALL_INTERRUPTS();

//}

void __interrupt() ISR_timer0() {
  DISABLE_ALL_INTERRUPTS();
    
    //SE A INTERRUPÇÃO FOI CHAMADA POR UM BOTÃO
    if (INTCONbits.INT0IF) {
        INTCONbits.INT0IF = 0;
       //SE FOI O BOTAO DE STOP
        if( b_stop == 0 ){
            sem_wait(&s_started);
            PORTCbits.RC0 = 1; 
            PORTDbits.RD7 = ~PORTDbits.RD7;
            started = 0;
            time = 0;
            count = 0;
            dezena = 0;
            unidade = 0;
            sem_post(&s_started);

        }
        //SE FOI O BOTAO +10s
        if( b_10s == 0 ){
            PORTCbits.RC1 = 1;
            if(started == 1){
                sem_wait(&s_count);
                count += 10;
                sem_post(&s_count);
            }else{
                sem_wait(&s_time);
                time += 10;
                unidade = _mod(time, 10);
                dezena  = _div(time, 10);
                sem_post(&s_time);
            }
        }
        //SE FOI O BOTAO +60s
        if( b_60s == 0 ){
            PORTCbits.RC2 = 1;
            if(started == 1){
                sem_wait(&s_count);
                count += 60;
                sem_post(&s_count);
            }else{
                sem_wait(&s_time);
                time += 60;
                unidade = _mod(time, 10);
                dezena  = _div(time, 10);
                sem_post(&s_time);
            }
        }
        //SE FOI A PORTA
        if( b_porta == 1 ){
            sem_wait(&s_started);
            started = 0;
            sem_post(&s_started);
            
            sem_wait(&s_time);
            sem_wait(&s_count);
            time = count;
            sem_post(&s_count);
            sem_post(&s_time);
        }
        
    }else{
        //SE A INTERRUPÇÃO FOI CHAMADA PELO TIMER
        if(INTCONbits.TMR0IF){
            dp_update(); //update na varredura do display
            INTCONbits.TMR0IF = 0;
            TMR0L = 252;    
            delay_decrement();

            if(started == 1){
                timer_index++;
                if(timer_index == 250){
                    sem_wait(&s_count);
                    count--;
                    unidade = _mod(count, 10);
                    dezena  = _div(count, 10);
                    sem_post(&s_count);
                    
                    timer_index = 0;
                    if(count == 0){
                        sem_wait(&s_started);
                        sem_wait(&s_time);
                        started = 0;
                        time = 0;
                        sem_post(&s_time);
                        sem_post(&s_started);
                    }
                }
            }
            #if RR_SCH
            quantum--;
            if (quantum <= 0) {
                quantum = QUANTUM;
                SAVE_CONTEXT(READY);
                ready_queue.task_running = round_robin();
                RESTORE_CONTEXT(RUNNING);
            }
            #endif

            PORTDbits.RD0 = 1;
            // Decrementa o tempo de espera por delay de cada
            // tarefa que está na fila de aptos em estado de 
            // WAITING
            delay_decrement();
        }
        
        
    }
  
  ENABLE_ALL_INTERRUPTS();
}

