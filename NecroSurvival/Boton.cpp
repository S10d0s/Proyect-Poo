#include "Boton.h"
#include <SFML/Window/Mouse.hpp>

Boton::Boton() {
	boton.setFillColor(Color(50,50,150,100));
	boton.setOutlineColor(Color(50,50,100,100));
	boton.setOutlineThickness(2);
}

void Boton::definir(Vector2f pos, Vector2f dim){
	boton.setPosition(pos);
	boton.setSize(dim);
}

void Boton::dibujar(RenderWindow &win){
	win.draw(boton);
}

bool Boton::presiona(RenderWindow &win, View view){
	mousei = Mouse::getPosition(win);
	mousef = win.mapPixelToCoords(mousei,view);
	if (boton.getGlobalBounds().contains(mousef)){
		boton.setFillColor(Color(100,100,250,100));
		if(Mouse::isButtonPressed(Mouse::Left)){
			return true;
		}
	}
	else{
		boton.setFillColor(Color(50,50,150,100));
	}
	return false;
};
