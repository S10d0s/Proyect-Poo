#ifndef BOTON_H
#define BOTON_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
using namespace sf;

class Boton {
public:
	Boton();
	void definir(Vector2f pos, Vector2f dim);
	bool presiona(RenderWindow &win , View view);
	void dibujar(RenderWindow &win);
private:
	RectangleShape boton;
	Vector2f mousef;
	Vector2i mousei;
};

#endif

