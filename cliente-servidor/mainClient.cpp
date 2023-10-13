#include "cliente.h"

int main(int argc, char **argv){

    TCPClient cliente1("127.0.0.1", 12345); 
    TCPClient cliente2("127.0.0.1", 12345);

    cliente1.closeConnection();

    cliente2.sendMessage("Soy el cliente2\n");
    cliente2.closeConnection();
}