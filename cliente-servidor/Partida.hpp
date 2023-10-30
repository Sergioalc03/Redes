#include "Jugador.hpp"

using namespace std;

class Partida
{
private:
    int turno;
    Jugador jugadores[2];
public:
    // Codigos result: -3 error en caso de barco no encontrado al buscar el hundimiento, -2 error disparado en un barco ya tocado o hundido, -1 error si no es el turno del jugador,
    // 0 si es agua, 1 si es barco tocado, 2 si es barco hundido
    Partida();
    
    void nuevaPartida();
    void asociarSockets(int sd1, int sd2);
    Jugador getJugador(int sd);
    int DisparoRecibido(int socketPlayer,int x, int y); 

    int comprobarDisparo(int player, int x, int y); //Comprueba disparo
                                                       // Devuelve 0 si ha sido fallo, 1 si ha sido acierto,
                                                       // -2 si es barco ya tocado o hundido
    
    bool barcoHundido(int player, int x, int y,Barco* barcoTocado); //Comprobar que algun barco esté hundido

    void cambiarTablero(int player, int x, int y, int evento);

    int getSocketDelTurno();//Devuelve el socket del ganador
};
