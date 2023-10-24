#ifndef TABLERO_H
#define TABLERO_H

#include "barco.h"
#include <vector>
#include <iostream>

class Tablero{

    private:

        std::vector<std::vector<char>> grid_;
    
    public: 

        Tablero(){

            grid_ = std::vector<std::vector<char>>(10, std::vector<char>(10, '~'));
        }

        void print();

        bool disponible(int x, int y, int n, int o);

        bool colisiones(int x, int y, int n, int o);

        void placeShip(Barco ship);

};

#endif //TABLETO_H
