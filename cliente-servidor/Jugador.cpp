#include "Jugador.hpp"

Jugador::Jugador(){
    barcos[0]=Barco(4);
    barcos[1]=Barco(3);
    barcos[2]=Barco(3);
    barcos[3]=Barco(2);
    barcos[4]=Barco(2);
    for(int i=0;i<5;i++)
        tablero_propio.placeShip(barcos[i]);    
}

void Jugador::AsociarIP(unsigned long ip){
    userIP=ip;
}

unsigned long Jugador::getIP(){
    return userIP;
}

int Jugador::getNumD(){
    return numDisp;
}

void Jugador::setNumD(int disp){
    numDisp=disp;
}

int Jugador::getNumB(){
    return numBarcos;
}

void Jugador::setNumB(int barcos){
    numBarcos=barcos;
}

Tablero* Jugador::getTableroPropio(){
    return &tablero_propio;
}

Tablero* Jugador::getTableroEnemigo(){
    return &tablero_enemigo;
}

Barco Jugador::getBarco(int i){
    return barcos[i];
}