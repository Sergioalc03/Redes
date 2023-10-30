#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>

struct disparo
{
        char cadena[255];
        int numero;
        char caracter;
};



class TCPClient {
private:
    int clientSocket;
    struct sockaddr_in serverAddr;

public:
    TCPClient(std::string& serverIP, int serverPort) {

        clientSocket = socket(AF_INET, SOCK_STREAM, 0);

        if (clientSocket == -1){

            std::cerr << "Error al crear el socket del cliente." << "\n";
            exit(EXIT_FAILURE);
        }

        serverIP.pop_back();
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverPort);
        serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());

        if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1){

            std::cerr << "Error al conectar con el servidor\n";
            exit(EXIT_FAILURE);
        }

        std::cout << "Conexión establecida con el servidor\n";
    }

    void sendMessage(const std::string& message);
    void disparar(struct disparo mensaje);
    std::string receiveMessage();
    void closeConnection();
};

#endif //CLIENTE_H