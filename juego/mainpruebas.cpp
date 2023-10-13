#include "barco.h"
#include "tablero.h"
#include <iostream>

int main(){

    Barco B1(4);

    std::cout << "Barco uno coordenada X = " << B1.getX() << "\ncoordenada Y = " << B1.getY() << "\norientacion = " <<B1.getOrientacion() << "\n";

    Tablero T1(1);

    T1.print();

    return 0;
}