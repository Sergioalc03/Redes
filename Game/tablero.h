#ifndef TABLERO_H
#define TABLERO_H

#include "barco.h"
#include <vector>
#include <iostream>
#include <string>

class Tablero{

    private:

        std::vector<std::vector<char>> grid_;
    
    public: 

        Tablero(){

            grid_ = std::vector<std::vector<char>>(10, std::vector<char>(10, '~'));
        }

        Tablero(std::string Base){

            int x, y, n = Base.size();
            grid_ = std::vector<std::vector<char>>(10, std::vector<char>(10, '~'));
            for(x = 0; x < 10; x++){
                for(y = 0; y < 10; y++){
                    if(Base[10*x+y+x] == 'B'){
                        
                        grid_[x][y] = 'B';
                    }
                }
            }
        }

        void print();

        bool canPlace(int x, int y, int size, int o);

        void placeShip(Barco ship);

        inline void setGridposition(int x, int y, char c){grid_[x][y] = c;}
        inline char getGridposition(int x, int y){return grid_[x][y];}
};

#endif //TABLETO_H
