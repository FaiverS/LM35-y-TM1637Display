/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "DisplayController.h"

// Define los pines según tu placa
#define SCLK_PIN D2
#define DIO_PIN D3


BufferedSerial pc(USBTX,USBRX);
AnalogIn Lm35_pin(A0); 

DigitalIn bnt1 (BUTTON1);
DigitalOut celsius (D4);
DigitalOut fahrenheit(D5);
DigitalOut Temperatura(D6);


void Lm35(void);
void TM1637(int k);

Thread T_Lm35(osPriorityNormal, 4096, NULL, NULL);
//Thread T_TM1637(osPriorityNormal, 4096, NULL, NULL);

int F;
int C;

int main() {
    T_Lm35.start(Lm35);
    while (true) {
  
    }
}





void Lm35(void) {
    
    while(true) {
        // Leer el valor del LM35
        float valor = Lm35_pin.read_u16();
        int valorLM35 = valor;  
        int l=valorLM35/230;

        printf("valor medido: %d\r\n", l);
        printf("valor medido: %d\r\n", valorLM35);
        int C=l;
        
         TM1637(C);
      
        // Esperar un tiempo antes de la próxima lectura
        ThisThread::sleep_for(400ms);
        
}  
}


void TM1637(int C) {
    DisplayController display(SCLK_PIN, DIO_PIN);
    display.iniciarContador();

   if (bnt1) {
     celsius =1;
     fahrenheit=0;
    int c=0;
    int h=(C%10);
    int x=(C/10)%10;
    int y=(C/100)%10;
    int i=0;
    while(i<1)
    {
        display.send_digit(c, 0);
        
        display.send_digit(h, 1);
        
        display.send_digit(x, 2);
       
        display.send_digit(y, 3);

       i++;
        ThisThread::sleep_for(50ms);
   }
  
   }
   else {
    celsius =0;
    fahrenheit=1;
    F=C*1.8+32;

   
   int c=0;
    int h=(F%10);
    int x=(F/10)%10;
    int y=(F/100)%10;
    int i=0;
    while(i<1)
    {
        
        display.send_digit(c, 0);
        
        display.send_digit(h, 1);
        
        display.send_digit(x, 2);
       
        display.send_digit(y, 3);

        
       i++;
        ThisThread::sleep_for(50ms);
   }
  
   }


   if(C>=60)
    {
    Temperatura=1;
    }

    if(C<=60)
    {
    Temperatura=0;
    }
}