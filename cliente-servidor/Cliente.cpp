#include "cliente.h"

void TCPClient::sendMessage(const std::string &message){

    if (send(clientSocket, message.c_str(), message.length(), 0) == -1){

        std::cerr << "Error al enviar el mensaje.\n";
    }
}

void TCPClient::disparar(struct disparo mensaje){

    if (send(clientSocket, &mensaje, sizeof(mensaje), 0) == -1) {
        std::cerr << "Error al enviar el mensaje al servidor." << std::endl;
    }
}

std::string TCPClient::receiveMessage(){

    char buffer[255];
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesRead == -1){

        std::cerr << "Error al recibir datos del servidor\n";
    }
    else{

        buffer[bytesRead] = '\0';
        return buffer;
    }
}

void TCPClient::closeConnection(){

    close(clientSocket);
}