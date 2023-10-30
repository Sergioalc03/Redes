all: servidor cliente

servidor:
	g++ -Wall ../cliente-servidor/ServidorJuego.cpp ../cliente-servidor/Partida.hpp ../cliente-servidor/Partida.cpp ../cliente-servidor/Jugador.hpp ../cliente-servidor/Jugador.cpp ../Game/tablero.h ../Game/tablero.cc ../Game/barco.h ../Game/barco.cc -o Server

cliente:
	g++ -Wall ../cliente-servidor/mainClient.cpp ../cliente-servidor/cliente.h ../cliente-servidor/Cliente.cpp ../Game/tablero.h ../Game/tablero.cc ../Game/barco.h ../Game/barco.cc -o Cliente
