#include "Juego.h"
#include <SFML/Window/Event.hpp>
using namespace sf;

//Crear la pantalla
Juego::Juego(Escena *e) : win(VideoMode(800,600),"Necro Survival") {
	win.setFramerateLimit(60);
	act = e;
}
//Bucle de eventos
void Juego::jugar(){
	while(win.isOpen()){
		//evento de cerrar pestaña
		Event e;
		while(win.pollEvent(e)){
			if(e.type == Event::Closed)
				win.close();
		}
		//actualizar escena
		act->actualizar(*this,win);
		//renbderizar escena
		act->dibujar(win);
		win.display();
		//cambiar escena
		if (prox){
			delete act;
			act = prox;
			prox = nullptr;
		}
	}
}
//Destructor
Juego::~Juego(){
	delete act;
}
//Cambio de escena
void Juego::CambiarEscena(Escena *nueva_escena) {
	prox = nueva_escena;
}
