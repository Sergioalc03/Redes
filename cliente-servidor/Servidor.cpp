#include "servidor.h"

void TCPserver::escuchaOn(){

    if (listen(serverSocket, 5) == -1){

        std::cerr << "Error al escuchar conexiones\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "Esperando escuchar conexiones\n";

    socklen_t clientAddrLen = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);

    if (clientSocket == -1){

        std::cerr << "Error al aceptar la conexión." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Cliente conectado\n";
}

void TCPserver::sendM(const std::string &mensaje){

    if (send(clientSocket, mensaje.c_str(), mensaje.length(), 0)){

        std::cerr << "Error al enviar el mensaje\n";
        exit(EXIT_FAILURE);
    }
}

void TCPserver::closeConect(){

    close(clientSocket);
    close(serverSocket);
}