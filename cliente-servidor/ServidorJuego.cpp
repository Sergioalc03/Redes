#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <string>
#include "Partida.hpp"
#include <fstream>

#define MSG_SIZE 250
#define MAX_CLIENTS 20
#define NumPartidas 10

//TODO
//leer y escribir usuarios, analizar mensajes

//DONE
//Recibir usuarios

struct Usuario{
    std::string username;
    std::string password;
};

struct Cliente{
    Usuario credenciales;
    int sd;
    bool conectado = false;
    bool listo = false;
};

struct Pareja{
    int sd1;
    int sd2;
};

enum class TipoMensaje {
    USUARIO,
    REGISTRO,
    INICIAR_PARTIDA,
    DISPARO,
    SALIR,
    DESCONOCIDO
};

TipoMensaje MSGparser(string msg){
    if(msg.find("USUARIO") != -1)
        return TipoMensaje::USUARIO;
    if(msg.find("REGISTRO") != -1)
        return TipoMensaje::REGISTRO;
    if(msg.find("INICIAR-PARTIDA") != -1)
        return TipoMensaje::INICIAR_PARTIDA;
    if(msg.find("DISPARO") != -1)
        return TipoMensaje::DISPARO;
    if(msg.find("SALIR") != -1)
        return TipoMensaje::SALIR;
    else
        return TipoMensaje::DESCONOCIDO;
}

void leerUsuariosDesdeArchivo(std::vector<Usuario>& usuarios) {
    std::ifstream archivo("Usuarios.txt");
    std::string linea;
    Usuario usuario;

    while (std::getline(archivo, linea)) {
        usuario.username = linea;
        if (std::getline(archivo, linea)) {
            usuario.password = linea;
            usuarios.push_back(usuario);
        } else {
            std::cerr << "Error: Formato incorrecto en el archivo." << std::endl;
            break;
        }
    }

    archivo.close();
}

int BuscarUsuario(string username, std::vector<Usuario> user){
    bool encontrado = false;
    int i=0;
    while(i<50 && !encontrado){
        if(username == user[i].username)
            encontrado = true;
        else
            i++;
    }
    if (encontrado)
        return i;
    else
        return -1;
}

void registrarUsuario(string username, string passw){
    std::ofstream archivo("Usuarios.txt",ios::ate);
    archivo << username <<"\n";
    archivo << passw <<"\n";
    archivo.close();
}

int charToInt(char c){
    switch (c)
    {
    case 'A':
        return 0;
        
    case 'B':
        return 1;

    case 'C':
        return 2;

    case 'D':
        return 3;

    case 'E':
        return 4;
        
    case 'F':
        return 5;
        
    case 'G':
        return 6;
        
    case 'H':
        return 7;
        
    case 'I':
        return 8;
        
    case 'J':
        return 9;
        
    }
}

int main(){
    //VARIABLES PARA CONEXION
    int sd, new_sd;
    sockaddr_in sockname, from;
    char buffer[MSG_SIZE];
	socklen_t from_len;
    fd_set readfds, auxfds;

    //VARIABLES PARA GESTION DE PARTIDAS Y CLIENTES
    std::vector<Usuario> usuarios;
    std::vector<Cliente> Clientes;
    std::vector<Partida> Partidas;
    std::vector<bool> PartidasLibres;
    std::vector<Pareja> parejas;
    int numClientes = 0;
    
    //VARIABLES AUXILIARES
    char username[30]; 
    char passw[20];
    char disparoLetra;
    int disparoNumero;
    int salida;
    int recibidos;
   	//contadores
    int i,j,k,l,m,n;
 

  	sd = socket (AF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		perror("No se puede abrir el socket cliente\n");
    		exit (1);	
	}
    sockname.sin_family = AF_INET;
	sockname.sin_port = htons(4200);
	sockname.sin_addr.s_addr =  INADDR_ANY;

    if (bind (sd, (struct sockaddr *) &sockname, sizeof (sockname)) == -1)
	{
		perror("Error en la operación bind");
		exit(1);
	}
    
    /*---------------------------------------------------------------------
		Del las peticiones que vamos a aceptar sólo necesitamos el 
		tamaño de su estructura, el resto de información (familia, puerto, 
		ip), nos la proporcionará el método que recibe las peticiones.
   	----------------------------------------------------------------------*/
	from_len = sizeof (from);
    
    if(listen(sd,1) == -1){
		perror("Error en la operación de listen");
		exit(1);
	}

    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_SET(sd,&readfds);
    FD_SET(0,&readfds);

    while(1){
        auxfds = readfds;
        salida = select(FD_SETSIZE,&auxfds,NULL,NULL,NULL);
        
        if(salida > 0){
            for (i=0; i<FD_SETSIZE; i++){
                if(FD_ISSET(i, &auxfds)){
                    if(i == sd){
                        if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1){
                            perror("Error aceptando peticiones");
                            exit(1);
                        }
                        //Nuevo usuario conectado(comprueba si hay sitio y manda mensaje al resto de usuarios)
                        else{
                            if(numClientes < MAX_CLIENTS){
                                Clientes[numClientes].sd = new_sd;
                                numClientes++;
                                FD_SET(new_sd,&readfds);
                            
                                strcpy(buffer, "OK. Usuario conectado\n");
                            
                                send(new_sd,buffer,sizeof(buffer),0);  
                                //Mensaje a todos los usuarios, nuevo usuario conectado
                                for(j=0; j<(numClientes-1);j++){
                                    bzero(buffer,sizeof(buffer));
                                    sprintf(buffer, "Nuevo Cliente conectado: %d\n",new_sd);
                                    send(Clientes[j].sd,buffer,sizeof(buffer),0);
                                }
                            //Capacidad de usuarios maxima alcanzada
                            }else{
                                bzero(buffer,sizeof(buffer));
                                strcpy(buffer,"Demasiados clientes conectados\n");
                                send(new_sd,buffer,sizeof(buffer),0);
                                close(new_sd);
                            }
                        }
                    }
                    else if(i==0){
                        //Se ha introducido información de teclado
                        bzero(buffer, sizeof(buffer));
                        fgets(buffer, sizeof(buffer),stdin);
                        //Desconexion del servidor, cierra sockets y sale
                        if(strcmp(buffer,"SALIR\n") == 0){
                            for(j = 0; j<numClientes; j++){
                                bzero(buffer, sizeof(buffer));
                                strcpy(buffer,"Desconexión servidor\n"); 
                                send(Clientes[j].sd, buffer, sizeof(buffer), 0);
                                close(Clientes[j].sd);
                                FD_CLR(Clientes[j].sd,&readfds);
                            }
                            close(sd);
                            exit(-1);  
                        }
                    }
                    //Mensajes del usuario
                    else{
                        bzero(buffer, sizeof(buffer));
                        recibidos = recv(i, buffer, sizeof(buffer), 0);
                        string msg (buffer);

                        if(recibidos > 0){
                            TipoMensaje msgType = MSGparser(msg);
                            
                            switch (msgType) {
                                    case TipoMensaje::USUARIO:{
                                        if(strcmp(buffer, "USUARIO\n") == 0){
                                        bzero(buffer, sizeof(buffer));
                                        strcpy(buffer, "-Err. No ha introducido el usuario\n");
                                        send(i, buffer, sizeof(buffer), 0);
                                        }
                                    //Usuario no introducido
                                        else if(strcmp(buffer, "USUARIO \n") == 0){
                                            bzero(buffer, sizeof(buffer));
                                            strcpy(buffer, "-Err. No ha introducido el usuario\n");
                                            send(i, buffer, sizeof(buffer), 0);
                                        }
                                    //Usuario introducido
                                        else {
                                            strncpy(username, buffer + 8, 30);
                                            //Quita el salto de linea
                                            if (username[strlen(username)-1] == '\n')
                                                username[strlen(username)-1] = '\0';
                                            if(l = BuscarUsuario(username,usuarios)!=-1){
                                                bzero(buffer,sizeof(buffer));
                                                strcpy(buffer,"+Ok.Usuario correcto");
                                                send(i,buffer,sizeof(buffer),0);
                                                recv(i, buffer, sizeof(buffer), 0);

                                                if(strncmp(buffer, "PASSWORD ", 9)==0){
                                                    if(strcmp(buffer, "PASSWORD \n") == 0){
                                                        bzero(buffer, sizeof(buffer));
                                                        strcpy(buffer, "-Err. No ha introducido el password\n");
                                                        send(i, buffer, sizeof(buffer), 0);
                                                    }else{
                                                        strncpy(passw, buffer + 9, 20);
                                                        if (passw[strlen(passw)-1] == '\n')
                                                            passw[strlen(passw)-1] = '\0';
                                                        if(strcmp(passw,usuarios[l].password.c_str())==0){
                                                            bzero(buffer, sizeof(buffer));
                                                            strcpy(buffer, "+Ok.Usuario validado");
                                                            send(i, buffer, sizeof(buffer),0);
                                                            Clientes[numClientes] = {usuarios[l],i,true,false};
                                                            numClientes++;
                                                        }else{
                                                            bzero(buffer, sizeof(buffer));
                                                            strcpy(buffer, "-Err. Error en la validacion");
                                                            send(i, buffer, sizeof(buffer),0); 
                                                        } 
                                                    }
                                                }
                                            }else{ //Usuario introducido no existe
                                                bzero(buffer, sizeof(buffer));
                                                strcpy(buffer, "-Err. Usuario incorrecto");
                                                send(i, buffer, sizeof(buffer),0);
                                            }
                                        }
                                    }
                                        break;
                                    case TipoMensaje::REGISTRO:{
                                        if(j=msg.find('u') != -1){
                                            strncpy(username,msg.substr(j,30).c_str(),30);
                                            j=0;
                                            bool mismoName=false;
                                            while(j<50 && !mismoName){
                                                if(usuarios[j].username == username)
                                                    mismoName=true;
                                            }
                                            if(!mismoName){
                                                if(i=msg.find('p') != -1){
                                                    strncpy(passw,msg.substr(i,20).c_str(),20);
                                                    registrarUsuario(username,passw);
                                                    leerUsuariosDesdeArchivo(usuarios);

                                                }
                                            }else{
                                                bzero(buffer,sizeof(buffer));
                                                strcpy(buffer,"-Err.Ese username ya está ocupado");
                                                send(i,buffer,sizeof(buffer),0);
                                            }
                                        }
                                        
                                    }
                                        break;
                                    case TipoMensaje::INICIAR_PARTIDA:{
                                        for(j=0;j<numClientes;j++){
                                            if(i == Clientes[j].sd)
                                                Clientes[j].listo = true;
                                        }
                                        for(k=0;k<numClientes;k++){
                                            if( k!=j && Clientes[k].listo==true){
                                                for(int p=0;p<NumPartidas;p++){
                                                    if(PartidasLibres[p]==true){
                                                        parejas[p].sd1=Clientes[k].sd;
                                                        parejas[p].sd2=Clientes[j].sd;
                                                        Partidas[p].nuevaPartida();
                                                        Partidas[p].asociarSockets(parejas[p].sd1,parejas[p].sd2);
                                                        PartidasLibres[p]=false;
                                                        bzero(buffer,sizeof(buffer));
                                                        strcpy(buffer,"+Ok.Empieza la partida");
                                                        send(i,buffer,sizeof(buffer),0);
                                                        send(Clientes[k].sd,buffer,sizeof(buffer),0);
                                                        bzero(buffer,sizeof(buffer));
                                                        strcpy(buffer,Partidas[p].getJugador(0).getTableroPropioString().c_str());
                                                        send(parejas[p].sd1,buffer,sizeof(buffer),0);
                                                        bzero(buffer,sizeof(buffer));
                                                        strcpy(buffer,Partidas[p].getJugador(0).getTableroEnemigoString().c_str());
                                                        send(parejas[p].sd1,buffer,sizeof(buffer),0);
                                                        bzero(buffer,sizeof(buffer));
                                                        strcpy(buffer,Partidas[p].getJugador(1).getTableroPropioString().c_str());
                                                        send(parejas[p].sd2,buffer,sizeof(buffer),0);
                                                        bzero(buffer,sizeof(buffer));
                                                        strcpy(buffer,Partidas[p].getJugador(1).getTableroEnemigoString().c_str());
                                                        send(parejas[p].sd2,buffer,sizeof(buffer),0);
                                                    }
                                                    else{
                                                        bzero(buffer,sizeof(buffer));
                                                        strcpy(buffer,"+Ok.Esperando Jugadores...");
                                                    }
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                        break;
                                    case TipoMensaje::DISPARO:{
                                        if(j=msg.find(',') != -1){
                                            disparoLetra = msg.at(j-1);
                                            disparoNumero = atoi(&msg.at(j+1));
                                            string DisparoMSG;
                                            for(j=0;i<NumPartidas;j++){
                                                if(parejas[j].sd1==i || parejas[j].sd2==i){
                                                    switch(Partidas[j].DisparoRecibido(i,charToInt(disparoLetra),disparoNumero)){
                                                        case 0:{
                                                            DisparoMSG = "+Ok.Disparo en " +disparoLetra + ',' + std::to_string(disparoNumero);
                                                            bzero(buffer,sizeof(buffer));
                                                            strcpy(buffer,DisparoMSG.c_str());
                                                            if(parejas[j].sd1==i)
                                                                send(parejas[j].sd2,buffer,sizeof(buffer),0);
                                                            else
                                                                send(parejas[j].sd1,buffer,sizeof(buffer),0);
                                                            DisparoMSG = "+Ok.AGUA: " + disparoLetra + ',' + std::to_string(disparoNumero);
                                                            bzero(buffer,sizeof(buffer));
                                                            strcpy(buffer,DisparoMSG.c_str());
                                                            send(parejas[j].sd1,buffer,sizeof(buffer),0);
                                                            send(parejas[j].sd2,buffer,sizeof(buffer),0);
                                                        }
                                                            break;
                                                        case 1:{
                                                            DisparoMSG = "+Ok.Disparo en " +disparoLetra + ',' + std::to_string(disparoNumero);
                                                            bzero(buffer,sizeof(buffer));
                                                            strcpy(buffer,DisparoMSG.c_str());
                                                            if(parejas[j].sd1==i)
                                                                send(parejas[j].sd2,buffer,sizeof(buffer),0);
                                                            else
                                                                send(parejas[j].sd1,buffer,sizeof(buffer),0);
                                                            DisparoMSG = "+Ok.TOCADO: " + disparoLetra + ',' + std::to_string(disparoNumero);
                                                            bzero(buffer,sizeof(buffer));
                                                            strcpy(buffer,DisparoMSG.c_str());
                                                            send(parejas[j].sd1,buffer,sizeof(buffer),0);
                                                            send(parejas[j].sd2,buffer,sizeof(buffer),0);
                                                        }
                                                            break;
                                                        case 2:{
                                                            DisparoMSG = "+Ok.Disparo en " +disparoLetra + ',' + std::to_string(disparoNumero);
                                                            bzero(buffer,sizeof(buffer));
                                                            strcpy(buffer,DisparoMSG.c_str());
                                                            if(parejas[j].sd1==i)
                                                                send(parejas[j].sd2,buffer,sizeof(buffer),0);
                                                            else
                                                                send(parejas[j].sd1,buffer,sizeof(buffer),0);
                                                            DisparoMSG = "+Ok.HUNDIDO: " + disparoLetra + ',' + std::to_string(disparoNumero);
                                                            bzero(buffer,sizeof(buffer));
                                                            strcpy(buffer,DisparoMSG.c_str());
                                                            send(parejas[j].sd1,buffer,sizeof(buffer),0);
                                                            send(parejas[j].sd2,buffer,sizeof(buffer),0);
                                                        }
                                                            break;
                                                        case -1:{

                                                        }
                                                    }
                                                }
                                            }
                                        }

                                    }
                                        break;
                                    case TipoMensaje::SALIR:
                                        break;
                                    case TipoMensaje::DESCONOCIDO:
                                        break;
                                        }
                            
                            
                        }
                    }
                }
            }
        }
    }             
	close(sd);
	return 0;
}