#include "tablero.h"

void Tablero::print()
{

    std::cout << "   A B C D E F G H I J\n";

    for (int i = 0; i < 10; i++){

        if (i < 9){

            std::cout << i + 1 << "  ";
        }else{

            std::cout << i + 1 << " ";
        }

        for (int j = 0; j < 10; j++){

            std::cout << grid_[i][j] << " ";
        }

        std::cout << "\n";
    }
}

bool Tablero::disponible(int x, int y, int n, int o){

    int i;

    if(o == 0){

        if((y + n - 1) == 9){
            
            if(grid_[x][y - 1] == '~'){

                return true;
            }
        }else{

            for(i = (y - 1); i < (y + n); i ++){

                if(grid_[x][i] != '~'){

                    return false;
                }
            }

            return true;
        }

        return false;
    }else{

        if((x + n - 1) == 9){
            
            if(grid_[x - 1][y] == '~'){

                return true;
            }
        }else{

            for(i = (x - 1); i < (x + n); i ++){

                if(grid_[i][y] != '~'){

                    return false;
                }
            }

            return true;
        }

        return false;
    }
}

bool Tablero::colisiones(int x, int y, int n, int o){

    int i; 

    if(o == 0){

        if(x == 0){
            if(y + n - 1 == 9){
 
                for(i = (y - 1); i < 9; i++){
                    
                    if(grid_[x][i] != '~'){

                    return false;
                }
                }
            }else{

                for(i = (y - 1); i < (y + n); i++){
                
                }
            }
        }else if( x == 9){

        }else{

        }   
    }
}

void Tablero::placeShip(Barco ship){

    int n = ship.getSize();
    int orientacion = ship.getOrientacion();
    int x, y, i;
    x = ship.getIordenadas(0);
    y = ship.getIcoordenadas(0);

    if(orientacion == 0){

    }    
}