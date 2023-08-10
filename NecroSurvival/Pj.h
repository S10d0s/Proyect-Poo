#ifndef PJ_H
#define PJ_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Balas.h"
using namespace sf;

class Pj {
public:
	Pj();
	void actualizar(float vel_max,float acel);
	void dibujar(RenderWindow &win);
	void muerte(RenderWindow &win);
	Vector2f VerPosicion();
	Balas GenerarBala(RenderWindow &win,View view);
private:
	float vel_max,acel;
	Texture Pj_ts, Pj_ta, Pjm1_t, Pjm2_t, Pjm3_t;
	Sprite Pj_ss, Pj_sa, Pjm1_s, Pjm2_s, Pjm3_s;
	Clock Mc;
	CircleShape Shadow;
	Vector2f Aceleracion , Velocidad , Posicion;
};

#endif

