#include "barco.h"

int main(){

    Barco b1(4);

    std::cout << "Orientacion: " << b1.getOrientacion() << "\n";
    std::cout << "Tamaño: " << b1.getSize() << "\n";

    b1.printShip();

    std::cout << "Reposicionando...\n";

    b1.realocShip();

    std::cout << "Orientacion: " << b1.getOrientacion() << "\n";
    std::cout << "Tamaño: " << b1.getSize() << "\n";

    b1.printShip();

    return 0;
}