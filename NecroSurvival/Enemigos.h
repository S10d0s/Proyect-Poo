#ifndef ENEMIGOS_H
#define ENEMIGOS_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Pj.h"

class Enemigos {
public:
	Enemigos(Vector2f Spawn);
	void actualizar(Vector2f Pj);
	void dibujar(RenderWindow &win);
	Vector2f VerPosicion();
private:
	float vel;
	Texture E_t;
	Sprite E_s;
	CircleShape Shadow;
	Vector2f Velocidad , Posicion;
};

#endif

