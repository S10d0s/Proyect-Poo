#ifndef BALAS_H
#define BALAS_H
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
using namespace sf;

class Balas {
public:
	Balas(Vector2f pos, Vector2f direc);
	void actualizar();
	void dibujar(RenderWindow &win);
	Vector2f VerPosicion();
private:
	CircleShape bala;
	Vector2f vel;
};

#endif

