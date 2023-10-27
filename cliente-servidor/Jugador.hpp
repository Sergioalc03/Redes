#include <string.h>
#include "../Game/tablero.h"

using namespace std;

class Jugador {
    private:
        unsigned long userIP;
        Tablero tablero_propio;
        Tablero tablero_enemigo;
        Barco barcos[5];
        int numDisp;
        int numBarcos;

    public:
        Jugador();
        void AsociarIP(unsigned long ip);
        unsigned long getIP();
        int getNumD();
        void setNumD(int disp);
        int getNumB();
        void setNumB(int barcos);
        Tablero* getTableroPropio();
        Tablero* getTableroEnemigo();
        Barco getBarco(int i);
};