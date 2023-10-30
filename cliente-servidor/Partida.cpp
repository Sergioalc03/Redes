#include "Partida.hpp"

Partida::Partida(){
    
}

void Partida::nuevaPartida(){
    jugadores[0].nuevaPartida();
    jugadores[1].nuevaPartida();
}

void Partida::asociarSockets(int sd1, int sd2){
    jugadores[0].AsociarSocket(sd1);
    jugadores[1].AsociarSocket(sd2);
}

Jugador Partida::getJugador(int sd){
    if(jugadores[0].getSocket()==sd)
        return jugadores[0];
    else
        return jugadores[1];
}

int Partida::DisparoRecibido(int SocketPlayer, int x, int y){
    int player=0;
    Barco* barcoTocado;

    if(SocketPlayer!=jugadores[player].getSocket())
        player=1;

    if(!turno==player){
        return -1;
    } else {
        int disparoResult = this->comprobarDisparo(player,x,y); //Comprobamos el disparo
        
        if(disparoResult != -2){
            
            if(disparoResult==1){
                
                if(barcoHundido(1-player, x, y,barcoTocado))
                {        
                        for(int i=0; i<barcoTocado->getSize(); i++)
                            cambiarTablero(player,barcoTocado->getIordenadas(i),barcoTocado->getIcoordenadas(i),2);

                        jugadores[1-player].setNumB( jugadores[1-player].getNumB()-1 );
                        if(jugadores[1-player].getNumB()==0)
                            return 3;
                
                } else if(barcoTocado!=nullptr) {
                        
                        cambiarTablero(player,x,y,1);
                        turno=1-turno;
                        return disparoResult;
                
                } else
                        turno=1-turno;
                        return -3;
            } else {
                cambiarTablero(player,x,y,0);
                turno=1-turno;
                return disparoResult;
            }
        }
        return disparoResult;
    }
}

int Partida::comprobarDisparo(int player, int x, int y){
    char casilla=jugadores[1-player].getTableroPropio()->getGridposition(x,y);
    int resultado;

    switch (casilla){
        case '*':
        case '~': resultado=0;
                break;
        
        case 'B': resultado=1;
                break;

        case 'T':
        case 'X': resultado=-2;
    }
    return resultado;
}

bool Partida::barcoHundido(int player, int x, int y, Barco* barcoTocado){
    Barco barcosEnemigos[5];
    Barco barcoEnemigo;
    bool encontrado=false, hundido=false;

    for(int i=0; i<5; i++)
      barcosEnemigos[i]= jugadores[1-player].getBarco(i);  

    int i=0;
    while(encontrado==false || i<5 ){
        barcoEnemigo = barcosEnemigos[i];

        for(int j=0; j<barcoEnemigo.getSize(); j++){
            if( x == barcoEnemigo.getIordenadas(j) && y == barcoEnemigo.getIcoordenadas(j) ) //Econtramos el barco que tiene la posicion del disparo
                encontrado=true;
        }
        i++;
    }

    int h=0;
    if(encontrado){
        for(int i=0; i<barcoEnemigo.getSize(); i++){
            if(jugadores[1-player].getTableroPropio()->getGridposition( barcoEnemigo.getIordenadas(i),barcoEnemigo.getIcoordenadas(i) ) == 'T')
                h++;
        }
    } else {
        barcoTocado==nullptr;
        return encontrado;
    }

    if(h==barcoEnemigo.getSize()){
        barcoTocado= &barcoEnemigo;
        return true;
    } else {
        barcoTocado= &barcoEnemigo;
        return false;
    }
        
}

void Partida::cambiarTablero(int player, int x, int y, int evento){
    
    //Modificacion de los tableros del jugador que ha realizado el disparo
    switch (evento)
    {
    case 0: jugadores[player].getTableroEnemigo()->setGridposition(x,y,'*');
            jugadores[player].setNumD( jugadores[player].getNumD()+1 );
            break;
    
    case 1: jugadores[player].getTableroEnemigo()->setGridposition(x,y,'T');
            jugadores[player].setNumD( jugadores[player].getNumD()+1 );
            break;
    
    case 2: jugadores[player].getTableroEnemigo()->setGridposition(x,y,'X');
            break;    
    }

    //Modificacion de los tableros enemigos
    switch (evento)
    {
    case 0: jugadores[1-player].getTableroPropio()->setGridposition(x,y,'*');
            break;
    
    case 1: jugadores[1-player].getTableroPropio()->setGridposition(x,y,'T');
            break;

    case 2: jugadores[1-player].getTableroPropio()->setGridposition(x,y,'X');
            break;
    }
}

int Partida::getSocketDelTurno(){
    return jugadores[turno].getSocket();
}
