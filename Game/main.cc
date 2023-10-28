#include "barco.h"
#include "tablero.h"

int main(){

    Barco b1(4);
    Barco b2(3);
    Barco b3(3);
    Barco b4(2);
    Barco b5(2);

    std::cout << "Orientacion: " << b1.getOrientacion() << "\n";
    std::cout << "Tamaño: " << b1.getSize() << "\n";

    b1.printShip();

    std::cout << "Reposicionando...\n";

    b1.realocShip();

    std::cout << "Orientacion: " << b1.getOrientacion() << "\n";
    std::cout << "Tamaño: " << b1.getSize() << "\n";

    b1.printShip();

    Tablero T1("BBBBAAAAAA;AABBBAAAAA;AAAAAABBBA;BBAAAAAAAA;BBAAAAAAAA;BBBAAAAAAA;AAAAAAAAAA;BBBBAAAAAA;BBBBAAAAAA;BBBBAAAAAA");

    T1.print();

    Tablero T2;

    T2.print();

    T2.placeShip(b1);
    T2.print();

    T2.placeShip(b2);
    T2.print();

    T2.placeShip(b3);
    T2.print();

    T2.placeShip(b4);
    T2.print();

    T2.placeShip(b5);
    T2.print();

    return 0;
}