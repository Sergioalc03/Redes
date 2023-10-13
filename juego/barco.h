#ifndef BARCO_H
#define BARCO_H

#include <random>

class Barco{
    
    private:

        int tamaño_;
        int x_;
        int y_;
        int orientacio_;
    
    public:

    Barco(int tamaño){

        tamaño_ = tamaño;

        std::random_device seed;
        std::mt19937 gen(seed());
        std::uniform_int_distribution<int> distribution(0, 9);

        x_ = distribution(gen);
        y_ = distribution(gen);

        orientacio_ = distribution(gen)%2; //if orientacio == 0 --> Horizontal else vertical
    }

    inline int getTamaño(){return tamaño_;}
    inline int getX(){return x_;}
    inline int getY(){return y_;}
    inline int getOrientacion(){return orientacio_;}

    inline void setnewX(int x){x_ = x;}
    inline void setnewY(int y){y_ = y;}

};

#endif //BARCO_H