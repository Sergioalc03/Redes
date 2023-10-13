#include "barco.h"
#include <iostream>

int main(){

    Barco B1(4);

    std::cout << "Barco uno coordenada X = " << B1.getX() << "\ncoordenada Y = " << B1.getY() << "\norientacion = " <<B1.getOrientacion() << "\n";

    return 0;
}