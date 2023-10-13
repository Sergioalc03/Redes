#ifndef TABLERO_H
#define TABLERO_H

#include "barco.h"
#include <vector>
#include <iostream>

class Tablero{

    private:

        int id_;
        std::vector<std::vector<char>> grid_;
    
    public: 

        Tablero(int id){

            id_ = id;
            grid_ = std::vector<std::vector<char>>(10, std::vector<char>(10, '~'));
        }

        void print(){
            
            std::cout << "   A B C D E F G H I J\n";

            for(int i = 0; i < 10; i++){
                
                if(i < 9){

                std::cout << i+1 << "  ";
                }else{

                std::cout << i+1 << " ";
                }
                
                for(int j = 0; j < 10; j++){
                    
                    std::cout << grid_[i][j] << " ";
                }

                std::cout << "\n";
            }
        }

        void placeShip(Barco Ship){

            int n = Ship.getSize();

            if(Ship.getOrientacion() == 0){
                //El barco esta en Horizontal -----
                
            }else{


            }
        }
};

#endif //TABLETO_H