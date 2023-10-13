#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

class TCPserver{

    private:

        int serverSocket;
        int clientSocket;
        struct sockaddr_in serverAddr;
        struct sockaddr_in clientAddr;

    public:

        TCPserver(int port){

            serverSocket = socket(AF_INET, SOCK_STREAM, 0);
            if(serverSocket == -1){

                std::cerr << "Error al abrir el socket\n";
                exit(EXIT_FAILURE);
            }

            serverAddr.sin_family = AF_INET;
            serverAddr.sin_port = htons(port);
            serverAddr.sin_addr.s_addr = INADDR_ANY;

            if(bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1){

                std::cerr << "Error al conectar el socket al puerto\n";
                exit(EXIT_FAILURE);
            }
        }

        void escuchaOn();
        void sendM(const std::string &mensaje);
        void closeConect();
};

#endif //SERVIDOR_H