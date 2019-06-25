/**
 * LunOS - Luan Operating System
 */

#include <xc.h>
#include "kernel.h"
#include "tasks.h"
#include "int0_test.h"
#include "semaphore.h"
#include "car.h"

#pragma config PBADEN = OFF
#pragma config WDT    = OFF

asm("GLOBAL _task_idle, _task_2heat, _micro_setup, _task_keyboard");


void main(void) {

  lunos_init();

  config_INT0();
  config_timer0();
  
  micro_setup();
  
  
  lunos_createTask(5, &task_keyboard);
  lunos_createTask(5, &task_2heat);


  

 
  
  dispatcher(READY);

  while (1);

  return;
}
