/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

const int numRows = 4;
const int numCols = 3;

char keyMap[numRows][numCols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

UnbufferedSerial serial(USBTX, USBRX, 9600);
using namespace std;
DigitalOut rowPins[numRows] = {DigitalOut(D2), DigitalOut(D3), DigitalOut(D4), DigitalOut(D5)};
DigitalIn colPins[numCols] = {DigitalIn(D6), DigitalIn(D7), DigitalIn(D8)};

char leer(){
    for (int i = 0; i < numRows; i++) {
                rowPins[i] = 0;
                
                for (int j = 0; j < numCols; j++) {
                    if (!colPins[j]) {
                        return keyMap[i][j];
                        ThisThread::sleep_for(500ms);  // Evita lecturas múltiples mientras la tecla está presionada
                    }
                    
                }
                rowPins[i] = 1;
           }
    return -1;
}
void polinomio(){
    char signo2;
    char signo1;
    char signo0;
    int a;
    int b;
    int c;
    printf("Introduzca el signo del coeficiente de grado 2 (# para positivo * para negativo):");
    signo2 = leer();
    printf("Introduzca el coeficiente de grado 2:");
    if (signo2 == '*')
        a =  (leer() - '0')*-1;
    else
        a = leer() - '0';
    
    printf("Introduzca el signo del coeficiente de grado 1 (# para positivo * para negativo):");
    signo1 = leer();
    printf("Introduzca el coeficiente de grado 1:");
    if (signo1 == '*')
        b =  (leer() - '0')*-1;
    else
        b = leer() - '0';
    
    printf("Introduzca el signo del coeficiente constante (# para positivo * para negativo):");
    signo0 = leer();
    printf("Introduzca el coeficiente constante:");
    if (signo0 == '*')
        c =  (leer() - '0')*-1;
    else
        c = leer() - '0';
    
    double discriminante = b^2 - 4*a*c;
    if (discriminante < 0){
        printf("Solución en los imaginarios");
        return;
    }
    double raiz1;
    raiz1 = (-b + sqrt(discriminante))/2*a;
    double raiz2;
    raiz2 = (-b - sqrt(discriminante))/2*a;
    
    if (raiz1 == raiz2)
        printf("La única raíz es: ", raiz1);
    else
        printf("Las raíces son: ", raiz1, " y ", raiz2);
}

void nota(){
    int N;
    printf("Ingrese su nota de 0 a 10:");
    N = leer() - '0';


    if (0 <= N && N <= 3)
        printf("A");
    else if (3 < N && N <= 4)
        printf("B");
    else if (4 < N && N <= 5)
        printf("C");
    else if (5 < N && N <= 7)
        printf("D");
    else if (7 < N && N < 9)
        printf("E");
    else if (9 <= N && N <= 10)
        printf("F");
}

void rgb(){
    PwmOut ledR(LED1);
    PwmOut ledG(LED2);
    PwmOut ledB(LED3);

    ledR.period(0.01);
    ledG.period(0.01);
    ledB.period(0.01);

        int r, g, b;   
        
        printf("Ingrese el color en formato RGB");
        printf("R:");
        r = leer()-'0';
        printf("G:");
        g = leer()-'0';
        printf("B:");
        b = leer()-'0';
        
        // Calculate PWM values
        float pwmR = (float)r ;
        float pwmG = (float)g ;
        float pwmB = (float)b ;

        ledR.write(1-pwmR);
        ledG.write(1-pwmG);
        ledB.write(1-pwmB);
}

int main() {
    
        printf("Pulse un numero para ejecutar una tarea (1 para polinomio, 2 para nota alfanumerica o 3 para LED RGB)");
        int numero = leer()-'0';
        if (numero == 1){
            polinomio();
        }else if (numero == 2){
            nota();
        }else if (numero == 3){
            rgb();
        }
    
}