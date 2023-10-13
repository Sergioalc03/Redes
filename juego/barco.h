#ifndef BARCO_H
#define BARCO_H

#include <random>

class Barco{
    
    private:

        int tamaño_;
        int x_;
        int y_;
        int orientacion_;
    
    public:

    Barco(int tamaño){

        tamaño_ = tamaño;

        std::random_device seed;
        std::mt19937 gen(seed());
        std::uniform_int_distribution<int> distribution(0, 9);
        std::uniform_int_distribution<int> orientado(0, 1);

        x_ = distribution(gen);
        y_ = distribution(gen);

        orientacion_ = orientado(gen); //if orientacio == 0 --> Horizontal else vertical
    }

    Barco(int tamaño, int x, int y, int orientacion){

        tamaño_ = tamaño;
        x_ = x;
        y_ = y;
        orientacion_ = orientacion;
    }

    inline int getSize(){return tamaño_;}
    inline int getX(){return x_;}
    inline int getY(){return y_;}
    inline int getOrientacion(){return orientacion_;}

    inline void setnewX(int x){x_ = x;}
    inline void setnewY(int y){y_ = y;}

    void replaceShip(){

        std::random_device seed;
        std::mt19937 gen(seed());
        std::uniform_int_distribution<int> distribution(0, 9);

        x_ = distribution(gen);
        y_ = distribution(gen);        
    }

};

#endif //BARCO_H