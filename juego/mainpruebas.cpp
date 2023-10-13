#include "barco.h"
#include "tablero.h"
#include <iostream>

int main(){


    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<int> distribution(0, 9);

    int x = distribution(gen);
    int y = distribution(gen);

    Barco B1(4);
    Barco B2(3);
    Barco B3(2);
    Barco B4(2);

    std::cout << "\nTamaño del barco: " << B1.getSize() <<"\ncoordenada X = " << B1.getX() << "\ncoordenada Y = " << B1.getY() << "\norientacion = " <<B1.getOrientacion() << "\n";
    std::cout << "\nTamaño del barco: " << B2.getSize() <<"\ncoordenada X = " << B2.getX() << "\ncoordenada Y = " << B2.getY() << "\norientacion = " <<B2.getOrientacion() << "\n";
    std::cout << "\nTamaño del barco: " << B3.getSize() <<"\ncoordenada X = " << B3.getX() << "\ncoordenada Y = " << B3.getY() << "\norientacion = " <<B3.getOrientacion() << "\n";
    std::cout << "\nTamaño del barco: " << B4.getSize() <<"\ncoordenada X = " << B4.getX() << "\ncoordenada Y = " << B4.getY() << "\norientacion = " <<B4.getOrientacion() << "\n";


    Tablero T1;

    T1.placeShip(B1);
    T1.placeShip(B2);
    T1.placeShip(B3);
    T1.placeShip(B4);
    
    T1.print();

    return 0;
}