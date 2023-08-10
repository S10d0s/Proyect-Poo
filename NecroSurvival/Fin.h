#ifndef FIN_H
#define FIN_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Escena.h"
#include "Boton.h"
#include <vector>
using namespace std;
using namespace sf;

class Fin : public Escena {
public:
	Fin();
	void actualizar(Juego &j,RenderWindow &win) override;
	void dibujar(RenderWindow &w) override;
private:
	vector<int> bestTimes;
	View view;
	Boton menu;	
	Texture fondo_t;
	Sprite fondo_s;
	Font font;
	Text text_ti , text_p , text_c, text_tiempo;
};

#endif

