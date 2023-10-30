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

bool Tablero::canPlace(int x, int y, int size, int o){

    int i, j;

    if(o == 0){

        if(x < 0 || x >= 10 || y < 0 || (y + size - 1)>= 10){
            
            return false;
        }

        for(i = (x - 1); i <= (x + 1); i++){

            for(j = (y - 1); j <= (y + size); j++){

                if(i >= 0 && i < 10 && j >= 0 && j < 10){

                    if(grid_[i][j] != '~'){

                        return false;
                    }
                }
            }
        }

        return true;
    }else{

        if(x < 0 || (x + size - 1) >= 10 || y < 0 || (y + size - 1)>= 10){
            
            return false;
        }

        for(i = (x - 1); i <= (x + size); i++){

            for(j = (y - 1); j <= (y + size); j++){

                if(i >= 0 && i < 10 && j >= 0 && j < 10){

                    if(grid_[j][i] != '~'){

                        return false;
                    }
                }
            }
        }

        return true;
    }
}

void Tablero::placeShip(Barco ship){

    int i, x, y, size, o;
    bool placed = false;

    x = ship.getIordenadas(0);
    y = ship.getIcoordenadas(0);
    size = ship.getSize();
    o = ship.getOrientacion();
            
    if(canPlace(x, y, size, o)){

        if(o == 0){ 

            for(i = y; i < (y + size); i++){

                grid_[x][i] = 'B';                
            }

            placed = true;
        }else{

            for(i = x; i < (x + size); i++){

                grid_[i][y] = 'B';
            }

            placed = true;
        }
    }else{

        ship.realocShip();
        placeShip(ship);
    }

}

std::string Tablero::ConvertiraString(){

    std::string cadena;
    for(int i = 0; i < 10; i ++){
        std::string aux;

        for(int j = 0; j < 11; j++){

            if(j != 10){
                if(grid_[i][j] == '~'){

                    aux[j] = 'A'; 
                }else{

                    aux[j] = 'B';
                }
            }else{
                aux[j] = ';';
            }
        }
        cadena = cadena + aux;
    }

    return cadena;
}