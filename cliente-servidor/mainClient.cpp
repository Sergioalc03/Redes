#include "cliente.h"
#include "../Game/tablero.h"

int main(int argc, char **argv){

    std::string ip, grid;
    int puerto, opcion, subopcio;

    bool salir = false, EnCurso, define = true;

    std::cout << "Intoduzca Ip del servidor\n";
    std::cin >> ip;

    std::cout << "Introduzca puerto\n";
    std::cin >> puerto;

    TCPClient NewClient(ip, puerto);

    //Logind

    std::cout << "-----Opciones-----\n1- Buscar Partida\n2- Salir\n";
    std::cin >> opcion;
    while(!salir){
        switch (opcion)
        {
        case 1:
            NewClient.sendMessage("INICIAR-PARTIDA");
            EnCurso = true;

            while(EnCurso){

                if(define){ 
                    grid = NewClient.receiveMessage();

                    Tablero MyTablero(grid);
                    Tablero EnemyTablero;
                    define = false;
                }

                std::cout << "1- Disparar\n2- Salir\n";
                std::cin >> subopcio;

                switch(subopcio){

                    case 1:
                        //Diparo
                        break;

                    case 2:
                        //Salir de la partida
                        EnCurso = false;
                        break;
                    
                    default:
                        std::cout << "Opcion no valida\n";
                        break;
                }
            }

            break;

        case 2:
            //Desconectarse del servidor
            salir = true;
            break;
        
        default:
            std::cout << "Opcion no valida\n";
            break;
        }
    }
}