#include "servidor.h"
#include "cliente.h"

int main(int argc, char **argv){

    TCPserver servidor1(12345);

    servidor1.escuchaOn();

    sleep(3);
    servidor1.closeConect();

    exit(EXIT_SUCCESS);
}