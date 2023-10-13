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
            bool libre = false;
            int cont = 0;

            if(Ship.getOrientacion() == 0){
                //El barco esta en Horizontal -----
                std::cout << "Colocando barco Horizontal\n";

                if((n + Ship.getY() - 1) >= 9){
                
                    Ship.setnewY(9 - (n-1));
                }

                if(grid_[Ship.getX()][Ship.getY()] != '~'){

                    Ship.replaceShip();
                }else{
                    
                    while(!libre){
                        
                        for(int i = Ship.getY(); i < 10; i++){

                            if(Ship.getX() == 0 and grid_[Ship.getX() + 1][i] == '~'){
                                if(cont == n){
                                    libre = true;
                                }
                            }else if(Ship.getX() == 9 and grid_[Ship.getX() - 1][i] == '~'){
                                if(cont == n){
                                    libre = true;
                                }
                            }else if((grid_[Ship.getX() + 1][i] == '~') and (grid_[Ship.getX() - 1][i] == '~')){
                                if(cont == n){
                                    libre = true;
                                }
                            }else{
                                Ship.replaceShip();
                            }
                            cont++;
                        }
                    }

                    for(int i =0; i < n; i++){

                        grid_[Ship.getX()][Ship.getY() + i] = 'B';
                    }                
                }

            }else{
                std::cout << "Colocando barco Vertical\n";

                if((n + Ship.getX() - 1) >= 9){
                
                    Ship.setnewX(9 - (n-1));
                }

                if(grid_[Ship.getX()][Ship.getY()] != '~'){

                    Ship.replaceShip();
                    std::cout << "Recolocnado barco\n";
                }else{
                    
                    while(!libre){
                        
                        for(int i = Ship.getX(); i < 10; i++){

                            if(Ship.getY() == 0 and grid_[i][Ship.getY() + 1] == '~'){
                                if(cont == n){
                                    libre = true;
                                }
                            }else if(Ship.getY() == 9 and grid_[i][Ship.getY() - 1] == '~'){
                                if(cont == n){
                                    libre = true;
                                }
                            }else if((grid_[i][Ship.getY() + 1] == '~') and (grid_[i][Ship.getY() - 1] == '~')){
                                if(cont == n){
                                    libre = true;
                                }
                            }else{
                                Ship.replaceShip();
                            }
                            cont++;
                        }
                    }

                    for(int i =0; i < n; i++){

                        grid_[Ship.getX() + i][Ship.getY()] = 'B';
                    }                
                }
            }
        }
};

#endif //TABLETO_H

/*
                    if(grid_[Ship.getX()][Ship.getY()] != '~'){   

                        Ship.replaceShip();
                        std::cout << "Reposicionando...\n";
                    }else if(Ship.getX() == 0 and grid_[(Ship.getX() + 1)][Ship.getY()] == '~'){
                            
                            std::cout << "Nada por barcon de " << n << "colocado\n"; 
                            for(int i = 0; i < n; i++){

                                grid_[Ship.getX()][Ship.getY() + i] = 'B';
                            } 
                    }else if(Ship.getX() == 9 and grid_[Ship.getX() - 1][Ship.getY()] == '~'){
                      
                            std::cout << "Nada por arriba\n"; 
                            for(int i = 0; i < n; i++){

                                grid_[Ship.getX()][Ship.getY() + i] = 'B';
                            } 
                    }else if{
                        
                    }*/