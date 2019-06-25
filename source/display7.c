#include <pic18f4520.h>

#include"../libraries/display7.h"



void dp_update()
{
   indice++;   
   
  
   
   if( indice == 1 ){
       PORTDbits.RD1 = 1;
       
       set_number(dezena);
     
   }else{
       PORTDbits.RD1 = 0; 
       set_number(unidade);
         indice = 0 ;
       
   }
}

void set_number(int a){
    switch(a){
        case 0:
            PORTC = 0b00111111;
            break;
        case 1:
            PORTC = 0b00000110;
            break;
        case 2:
            PORTC = 0b01011011;
            break;
        case 3:
            PORTC = 0b01001111;
            break;
        case 4:
            PORTC = 0b01100110;
            break;
        case 5:
            PORTC = 0b01101101;
            break;
        case 6:
            PORTC = 0b01111101;
            break;
        case 7:
            PORTC = 0b00000111;
            break;
        case 8:
            PORTC= 0b01111111;
            break;
        case 9:
            PORTC = 0b01101111;
            break;
        default:
            PORTC = 0b01111001;
            break;
            
           
    }
}
