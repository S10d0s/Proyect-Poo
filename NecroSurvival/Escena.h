#ifndef ESCENA_H
#define ESCENA_H
using namespace sf;
//es una clase con los metodos virtual para que otras clases lo usen
class Juego;

class Escena{
public:
	virtual void actualizar(Juego &j, RenderWindow &win) = 0;
	virtual void dibujar(RenderWindow &) = 0;
};
#endif
