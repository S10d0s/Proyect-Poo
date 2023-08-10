#include "Balas.h"

Balas::Balas(Vector2f pos, Vector2f direc) {
	bala.setPosition(pos+direc*6.f);
	bala.setRadius(7);
	bala.setOrigin(7,7);
	bala.setFillColor(Color(240,10,10,150));
	bala.setOutlineColor(Color(100,20,20,100));
	bala.setOutlineThickness(4);
	vel = direc*10.f;
}

void Balas::actualizar () {
	bala.move(vel);
}

void Balas:: dibujar(RenderWindow &win) {
	win.draw(bala);
}

Vector2f Balas::VerPosicion(){
	return bala.getPosition();
}
