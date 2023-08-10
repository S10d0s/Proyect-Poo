#include "Pj.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>
#include "Balas.h"
#include <SFML/Window/Mouse.hpp>
using namespace sf;
using namespace std;
//Inicializacion del personaje
Pj::Pj() {
	//texturas
	Pj_ts.loadFromFile("Sprites/Pj_Stand.png");
	Pj_ta.loadFromFile("Sprites/Pj_Attack.png");
	Pjm1_t.loadFromFile("Sprites/Pj_Die1.png");
	Pjm2_t.loadFromFile("Sprites/Pj_Die2.png");
	Pjm3_t.loadFromFile("Sprites/Pj_Die3.png");
	//velocidad y aceleracion
	vel_max = 2;
	acel = 0.2;
	//sprites
	Pj_ss.setTexture(Pj_ts);
	Pj_ss.setOrigin(10.f,10.f);
	Pj_ss.setScale(2.f,2.f);
	
	Pj_sa.setTexture(Pj_ta);
	Pj_sa.setOrigin(10.f,10.f);
	Pj_sa.setScale(2.f,2.f);
	
	Pjm1_s.setTexture(Pjm1_t);
	Pjm1_s.setOrigin(10.f,10.f);
	Pjm1_s.setScale(2.f,2.f);
	
	Pjm2_s.setTexture(Pjm2_t);
	Pjm2_s.setOrigin(10.f,10.f);
	Pjm2_s.setScale(2.f,2.f);
	
	Pjm3_s.setTexture(Pjm3_t);
	Pjm3_s.setOrigin(10.f,10.f);
	Pjm3_s.setScale(2.f,2.f);
	//sombra
	Shadow.setRadius(10);
	Shadow.setScale(1.f,0.5f);
	Shadow.setFillColor(Color(0,0,0,150));
	//posicion inicial
	Posicion.x = 1200;
	Posicion.y = 800;
	Pj_ss.setPosition(Posicion);
	Pj_sa.setPosition(Posicion);
}

//Actualizar
void Pj::actualizar(float vel_max, float acel){
	//movimiento Derecha
	
	if(Keyboard::isKeyPressed(Keyboard::D)){
		Aceleracion.x = acel;
		if(Velocidad.x <= vel_max){
			Velocidad.x += Aceleracion.x;
		}
		Pj_ss.setScale(2,2);
		Pj_sa.setScale(2,2);
	}
	else{
		if(Velocidad.x > 0){
			Velocidad.x = Velocidad.x*0.9;
		}
	}

	//movimiento Izquierda
	
	if(Keyboard::isKeyPressed(Keyboard::A)){
		Aceleracion.x = -acel;
		if(Velocidad.x >= -vel_max){
			Velocidad.x += Aceleracion.x;
		}
		Pj_ss.setScale(-2,2);
		Pj_sa.setScale(-2,2);
	}
	else{
		if(Velocidad.x < 0){
			Velocidad.x = Velocidad.x*0.9;
		}
	}

	//movimiento Abajo
	
	if(Keyboard::isKeyPressed(Keyboard::S)){
		Aceleracion.y = acel;
		if(Velocidad.y <= vel_max){
			Velocidad.y += Aceleracion.y;
		}
	}else{
		if(Velocidad.y > 0){
			Velocidad.y = Velocidad.y*0.9;
		}
	}
	
	//movimiento Arriba
	
	if(Keyboard::isKeyPressed(Keyboard::W)){
		Aceleracion.y = -acel;
		if(Velocidad.y >= -vel_max){
			Velocidad.y += Aceleracion.y;
		}
	}
	else{
		if(Velocidad.y < 0){
			Velocidad.y = Velocidad.y*0.9;
		}
		
	}
	
	//limite de moviemnto
	if(Pj_ss.getPosition().x>2390){
		Velocidad.x = 0.f;
		Pj_ss.move(-1,0);
	}
	if(Pj_ss.getPosition().x<10){
		Velocidad.x = 0.f;
		Pj_ss.move(1,0);
	}
	if(Pj_ss.getPosition().y>1580){
		Velocidad.y = 0.f;
		Pj_ss.move(0,-1);
	}
	if(Pj_ss.getPosition().y<20){
		Velocidad.y = 0.f;
		Pj_ss.move(0,1);
	}
	//actualizacon del movimiento
	{
	Pj_ss.move(Velocidad);
	Shadow.setPosition(Pj_ss.getPosition() + Vector2f (-11.f,15.f));
	Pj_sa.setPosition(Pj_ss.getPosition());
	Pjm1_s.setPosition(Pj_ss.getPosition());
	Pjm2_s.setPosition(Pj_ss.getPosition());
	Pjm3_s.setPosition(Pj_ss.getPosition());
	}
}
//Renderizado
void Pj::dibujar(RenderWindow &win){
	//render sombra
	win.draw(Shadow);
	//render personaje
	if(Mouse::isButtonPressed(Mouse::Left)){
		win.draw(Pj_sa);
	}
	else{
		win.draw(Pj_ss);
	}
}
//Muerte
void Pj::muerte(RenderWindow &win){
	win.draw(Shadow);
	
	if(Mc.getElapsedTime().asMilliseconds()>1500){
		Mc.restart();
	}
	if(Mc.getElapsedTime().asMilliseconds()<500){
		win.draw(Pjm1_s);
	}
	if(Mc.getElapsedTime().asMilliseconds()<1000 and Mc.getElapsedTime().asMilliseconds() >= 500){
		win.draw(Pjm2_s);
	}
	if(Mc.getElapsedTime().asMilliseconds()<1500 and Mc.getElapsedTime().asMilliseconds() >= 1000){
		win.draw(Pjm3_s);
	}
	
}
//Generar balas
Balas Pj::GenerarBala (RenderWindow &win, View view){
	//vector de direccion de la bala
	Vector2f p = Pj_ss.getPosition();
	Vector2i mi = Mouse::getPosition(win);
	Vector2f mf = win.mapPixelToCoords(mi,view);
	Vector2f v (mf.x-p.x,mf.y-p.y);
	v = v*1.f/sqrt(v.x*v.x + v.y*v.y);
	
	return Balas (p,v);
}
//Ver posicion
Vector2f Pj::VerPosicion(){
	Vector2f PP = Pj_ss.getPosition();
	return PP;
};
