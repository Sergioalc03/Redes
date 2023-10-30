#include "cliente.h"
#include "../Game/tablero.h"

int main(int argc, char **argv){

    std::string ip, grid, server;
    int puerto, opcion, subopcio, seleccion;
    std::string shot = "DISPARO";
    std::string seraux;


    bool salir = false, EnCurso, define = true;

    std::cout << "Intoduzca Ip del servidor\n";
    std::cin >> ip;

    std::cout << "Introduzca puerto\n";
    std::cin >> puerto;

    TCPClient NewClient(ip, puerto);

    std::cout << "Por favor seleccione:\n1- login\n2- Registarse\n";
    std::cin >> seleccion;
    if(seleccion == 1){

        std::string aux;
        std::string user;
        std::string pass;

        std::cout << "Intoduzca usuario\n";
        std::cin >> aux;

        user = "USUARIO " + aux;

        NewClient.sendMessage(user);

        aux = NewClient.receiveMessage();

        if(aux != "+Ok. Usuario correcto"){

            std::cout << aux << "\n";
            exit(EXIT_SUCCESS);
        }

        std::cout << "Introduzca contraseña\n";
        std::cin >> aux;

        pass = "PASSWORD" + aux;

        NewClient.sendMessage(pass);

        aux = NewClient.receiveMessage();

        if(aux != "+Ok. Usuario validado"){

            std::cout << aux << "\n";
            exit(EXIT_SUCCESS);
        }        

    }else if(seleccion == 2){

        std::string aux;
        std::string user;
        std::string pass;

        std::cout << "Indique su usuario\n";
        std::cin >> user;
        std::cout << "Indique su contraseña\n";
        std::cin >> pass;

        aux = "REGISTRO -u " + user + "-p " + pass;

        NewClient.sendMessage(aux);
    }else{

        exit(EXIT_SUCCESS);
    }


    std::cout << "-----Opciones-----\n1- Buscar Partida\n2- Salir\n";
    std::cin >> opcion;
    bool waiting;
    while(!salir){
        switch (opcion)
        {
        case 1:
            NewClient.sendMessage("INICIAR-PARTIDA");

            server = NewClient.receiveMessage();
			if((strcmp((char *)server[0], "+Ok.") == 0) && (strcmp((char *)server[1], "Empieza") == 0) && (strcmp((char *)server[2], "la") == 0) && (strcmp((char *)server[3], "partida.") == 0)){
					
                const char * buffer = server.c_str();
				strcpy((char *)buffer, "+Ok. Empieza la partida. \n");
				std::cout << "\n" << buffer << "\n";

                Tablero T1(buffer);
				T1.print();

                std::cout << "1- Disparar\n2- Salir\n";
                std::cin >> subopcio;

                switch(subopcio){

                    case 1:

                        server = NewClient.receiveMessage();
                        if(server == "+Ok. Turno de partida"){
                            int num;
                            char letra;
                            std::cout << "Introduzca Letra de la columna\n";
                            std::cin >> letra;
                            std::cout << "Introduzca Numero de fila\n";
                            std::cin >> num;
                            
                            struct disparo piun;
                            std::strncpy(piun.cadena, shot.c_str(), sizeof(piun.cadena));
                            piun.numero = num;
                            piun.caracter = letra;
                            NewClient.disparar(piun);

                            server = NewClient.receiveMessage();
                            

                            if(server == "+Ok. Tu oponente ha terminado la partida"){

                                std::cout << "Has ganado\n";
                                NewClient.sendMessage("SALIR");

                            }
                        }
                        break;

                    case 2:
                        NewClient.sendMessage("SALIR");
                        break;
                    
                    default:
                        std::cout << "Opcion no valida\n";
                        NewClient.sendMessage("SALIR");
                        exit(EXIT_FAILURE);
                        break;
                }
						
	
			}else if((strcmp((char *)server[0], "+Ok.") == 0) && (strcmp((char *)server[1], "Mostrando") == 0) && (strcmp((char *)server[2], "los") == 0) && (strcmp((char *)server[3], "tableros.") == 0)){
					
                    const char * buffer2 = server.c_str();
                    strcpy((char *)buffer2, " ");
					std::cout << buffer2 << "\n";

                    Tablero T2(buffer2);

				}else{
                    
                    std::cout << server << "\n";
				}
        case 2:
            NewClient.sendMessage("SALIR");
            salir = true;
            break;
        
        default:
            std::cout << "Opcion no valida\n";
            break;
        }
    }
}

/*            EnCurso = true;

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
                        int num;
                        char letra;
                        std::cout << "Introduzca Letra de la columna\n";
                        std::cin >> letra;
                        std::cout << "Introduzca Numero de fila\n";
                        std::cin >> num;
                        
                        struct disparo piun;
                        std::strncpy(piun.cadena, shot.c_str(), sizeof(piun.cadena));
                        piun.numero = num;
                        piun.caracter = letra;
                        NewClient.disparar(piun);
                        break;

                    case 2:
                        NewClient.sendMessage("SALIR");
                        EnCurso = false;
                        break;
                    
                    default:
                        std::cout << "Opcion no valida\n";
                        break;
                }
            }

            break;*/