#include "Enemigos.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Pj.h"
#include <cmath>
using namespace std;
//Constructor
Enemigos::Enemigos(Vector2f Spawn): Posicion(Spawn) {
	//cargar textura
	E_t.loadFromFile("Sprites/E_move.png");
	//establecer sprite
	E_s.setTexture(E_t);
	E_s.setOrigin(10.f,10.f);
	E_s.setColor(Color(255,255,255,200));
	//establecer sombra
	Shadow.setRadius(10);
	Shadow.setScale(1.f,0.5f);
	Shadow.setFillColor(Color(0,0,0,100));
	//definir posicion inicial
	E_s.setPosition(Posicion);
}
//Actualizacion
void Enemigos::actualizar(Vector2f Pj){
	// movimiento hacia el jugador
	Vector2f e = E_s.getPosition();
	Vector2f vel (Pj.x-e.x,Pj.y-e.y);
	vel = vel*1.f/sqrt(vel.x*vel.x + vel.y*vel.y);
	//giro
	if(vel.x >= 0){
		E_s.setScale(-1.5,1.5);
	}
	else{
		E_s.setScale(1.5,1.5);
	}
	//actualizacon del movimiento
	E_s.move(vel*1.6f);
	Shadow.setPosition(E_s.getPosition() + Vector2f (-11.f,15.f));
}
//Renderizado
void Enemigos::dibujar(RenderWindow &win){
	//dibujar sombra
	win.draw(Shadow);
	//dibujar enemigo
	win.draw(E_s);
}
//Ver Posicion
Vector2f Enemigos::VerPosicion(){
	return E_s.getPosition();
}
