#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Escena.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Boton.h"
using namespace sf;

class Menu : public Escena{
public:
	Menu();
	void actualizar(Juego &j,RenderWindow &win) override;
	void dibujar(RenderWindow &w) override;
private:
	View view;
	Boton play;
	Texture fondo_t;
	Sprite fondo_s;
	Font font;
	Text text_ti , text_p , text_c;
};

#endif

