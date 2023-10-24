#ifndef BARCO_H
#define BARCO_H

#include <random>
#include <vector>
#include <iostream>

class Barco{
    
private:

    int size_;
    std::vector<int> ordenadas;
    std::vector<int> coordenadas;
    int orientacion;

public: 

    Barco(){

        std::random_device seed;
        std::mt19937 gen(seed());
        std::uniform_int_distribution<int> orientado(0, 1);

        orientacion = orientado(gen);
    }

    Barco(int size){

        size_ = size;
        
        std::random_device seed;
        std::mt19937 gen(seed());
        std::uniform_int_distribution<int> orientado(0, 1);

        orientacion = orientado(gen);

        this->fullShip();
    }

    void fullShip();


    inline int getSize(){return size_;}
    inline int getOrientacion(){return orientacion;}

    void printShip();

    void realocShip();

    inline int getIordenadas(int i){return ordenadas[i];}
    inline int getIcoordenadas(int i){return coordenadas[i];}

    inline void setSize(int size){size_ = size;}
};

#endif //BARCO_H