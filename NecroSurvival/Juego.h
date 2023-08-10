#ifndef JUEGO_H
#define JUEGO_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Escena.h"
using namespace sf;

class Juego {
public:
	Juego(Escena *e);
	void jugar();
	void CambiarEscena(Escena *Nueva_escena);
	~Juego();
private:
	RenderWindow win;
	Escena *act,*prox = nullptr;
};

#endif

