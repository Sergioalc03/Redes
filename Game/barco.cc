#include "barco.h"

void Barco::fullShip(){

    int x, y, i;

    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<int> distribution(0, (9 - size_));

    x = distribution(gen);
    y = distribution(gen);

    if(orientacion == 0){

        for(i = 0; i < size_; i++){

            coordenadas.push_back(y+i);
            ordenadas.push_back(x);
        }
    }else{

        for(i = 0; i < size_; i++){

            coordenadas.push_back(y);
            ordenadas.push_back(x+i);
        }
    }
}

 void Barco::printShip(){

    int i; 

    for(i = 0; i < size_; i++){

        std::cout << "Posicion : " << ordenadas[i] << " " << coordenadas[i] << "\n";
    }
 }

 void Barco::realocShip(){

    int x, y, i;

    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<int> distribution(0, (9 - size_));

    x = distribution(gen);
    y = distribution(gen);

    ordenadas.clear();
    coordenadas.clear();

    if(orientacion == 0){

        for(i = 0; i < size_; i++){

            coordenadas.push_back(y+i);
            ordenadas.push_back(x);
        }
    }else{

        for(i = 0; i < size_; i++){

            coordenadas.push_back(y);
            ordenadas.push_back(x+i);
        }
    }
 }