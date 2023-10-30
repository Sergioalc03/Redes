#include <string.h>
#include "../Game/tablero.h"

using namespace std;

class Jugador {
    private:
        int userSocket;
        Tablero tablero_propio;
        Tablero tablero_enemigo;
        Barco barcos[5];
        int numDisp;
        int numBarcos;

    public:
        Jugador();
        void nuevaPartida();
        void AsociarSocket(int socket);
        int getSocket();
        int getNumD();
        void setNumD(int disp);
        int getNumB();
        void setNumB(int barcos);
        Tablero* getTableroPropio();
        Tablero* getTableroEnemigo();
        string getTableroPropioString();
        string getTableroEnemigoString();
        Barco getBarco(int i);
};