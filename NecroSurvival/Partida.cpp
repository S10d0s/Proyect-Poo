#include "Partida.h"
#include "Pj.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Juego.h"
#include <SFML/Window/Keyboard.hpp>
#include "Balas.h"
#include <SFML/Window/Mouse.hpp>
#include <algorithm>
#include "Enemigos.h"
#include <cmath>
#include "Menu.h"
#include "Fin.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;


//Cargar fondo
Partida::Partida() {
	//establecer camara
	view.setSize(800,600);
	Vector2f mapSize(2400,1600);
	
	//cargar fondo
	Fondo_t.loadFromFile("Sprites/Ladrillos.png");
	Fondo_s.setTexture(Fondo_t);
	Fondo_s.setPosition(0,0);
	
	//cargar sprites y texturas varias
	H1_t.loadFromFile("Sprites/HeartShield.png");
	H1_s.setTexture(H1_t);
	H1_s.setScale(2,2);
	
	H2_t.loadFromFile("Sprites/HeartHalfShield.png");
	H2_s.setTexture(H2_t);
	H2_s.setScale(2,2);
	
	H3_t.loadFromFile("Sprites/Heart.png");
	H3_s.setTexture(H3_t);
	H3_s.setScale(2,2);
	
	Ecto_t.loadFromFile("Sprites/Ectoplasm.png");
	Ecto_s.setTexture(Ecto_t);
	Ecto_s.setScale(2,2);
	Ecto_s.setColor(Color(255,255,255,150));
	
	Reloj_t.loadFromFile("Sprites/Reloj.png");
	Reloj_s.setTexture(Reloj_t);
	Reloj_s.setScale(1.5,1.5);
	
	//cronometro
	font.loadFromFile("minecraft.ttf");
	tiempo.setFont(font);
	tiempo.setCharacterSize(20);
	
	//Kills
	Kc = 0;
	Killc.setFont(font);
	Killc.setCharacterSize(20);
	
	//Vidas
	Li = 3;
	
	//lectura del txt
	for(int i=0;i<5;i++) { bestTimes.push_back(seconds(0)); }
	
	ifstream i_tiempos("best_times.txt");
	if(i_tiempos.is_open()){
		int tiempo_ms;
		int aux = 0;
		while (i_tiempos>>tiempo_ms){
			Time tiempo = milliseconds(tiempo_ms);
			bestTimes[aux] = tiempo;
			if(aux > 4) break;
			aux++;
		}
	}
	i_tiempos.close();
}
//Comparar tiempos
bool compareBestTimes(Time & a, Time & b) {
	return (a > b);
}

//Detectar balas fuera de la pantalla
bool fuera_de_la_pantalla(Balas &d) {
	//detectar balas
	Vector2f p = d.VerPosicion();
	if (p.x<0 or p.x>2400) return true;
	if (p.y<0 or p.y>1600) return true;
	return false;
}

//Centrar camara
void Partida::CentrarCamara(RenderWindow &win){
	float centerX = Player.VerPosicion().x;
	if (Player.VerPosicion().x < 400) {
		centerX = 400;
	} else if (Player.VerPosicion().x > 2000) {
		centerX = 2000;
	}
	
	float centerY = Player.VerPosicion().y;
	if (Player.VerPosicion().y < 300) {
		centerY = 300;
	} else if (Player.VerPosicion().y > 1300) {
		centerY = 1300;
	}
	
	Vector2f viewCenter(centerX, centerY);
	view.setCenter(viewCenter);
	win.setView(view);
}

//Generar Enemigos
void Partida::GenerarEnemigos(){
	if (Spawn_enemigo.getElapsedTime() > milliseconds(1000-cronometro.getElapsedTime().asSeconds()*10)) {
		//vector a angulo random fuera de la pantalla
		float aux = rand() % 360;
		Vector2f ang(cos(aux)*500,sin(aux)*500);
		//crear enemigo
		enemigos.push_back(make_unique<Enemigos>(Player.VerPosicion() + ang));
		Spawn_enemigo.restart();
	}
}
//Generar Balas
void Partida::GenerarBalas(RenderWindow &win){
	if(DisC.getElapsedTime() > milliseconds(500-Kc*2)){
		if(Mouse::isButtonPressed(Mouse::Left)){
			balas.push_back(Player.GenerarBala(win, view));
			DisC.restart();
		}
	}
}
//Colision Balas Y Enemigos
void Partida::ColiByE(){
	
	bool colisionDetectada = false;
	
	for (auto it = balas.begin(); it != balas.end(); ) {
		bool balaEliminada = false;
		
		for (auto enemigoIt = enemigos.begin(); enemigoIt != enemigos.end(); ) {
			// Calcular la distancia entre los centros de los objetos
			Vector2f distance = it->VerPosicion() - (*enemigoIt)->VerPosicion();
			float length = sqrt(distance.x * distance.x + distance.y * distance.y);
			
			// Comprobar si hay colisión
			if (length <= 20) {
				enemigoIt = enemigos.erase(enemigoIt);
				colisionDetectada = true;
				balaEliminada = true;
				Kc += 1;
				break;  // Salir del bucle de enemigos
			} else {
				++enemigoIt;
			}
		}
		
		if (!balaEliminada) {
			++it;
		} else {
			it = balas.erase(it);
		}
	}
}
//Colision Player y Enemigo
bool Partida::ColiPyE(){
	for (auto enemigoIt = enemigos.begin(); enemigoIt != enemigos.end(); ) {
		// Calcular la distancia entre los centros de los objetos
		Vector2f distance = Player.VerPosicion() - (*enemigoIt)->VerPosicion();
		float length = sqrt(distance.x * distance.x + distance.y * distance.y);
		
		// Comprobar si hay colisión
		if (length <= 25) {
			enemigoIt = enemigos.erase(enemigoIt);
			return true;
		} else {
			++enemigoIt;
		}
	}
	return false;
}

//Cronometro
void Partida::Cronometro(){
	int min = static_cast<int>(cronometro.getElapsedTime().asSeconds())/60;
	int sec = static_cast<int>(cronometro.getElapsedTime().asSeconds())%60;
	int mili = static_cast<int>(cronometro.getElapsedTime().asMilliseconds())%1000;
	
	ostringstream cronometroStream;
	cronometroStream << setfill('0') << setw(2) << min << ":"
		<< setfill('0') << setw(2) << sec << ":"
		<< setfill('0') << setw(2) << mili / 10; // Mostrar solo 2 dígitos para milisegundos
	
	tiempo.setString(cronometroStream.str());
	
}
//Actualizaciones
void Partida::actualizar(Juego &j, RenderWindow &win){
	//centrar camara 
	CentrarCamara(win);
	//generar Enemigos
	GenerarEnemigos();
	//generar balas
	if(Li > 0){
		GenerarBalas(win);
	}
	//jugador
	if(Li > 0){
		Player.actualizar(2.f + Kc*0.02f,0.2f + Kc*0.002f);
	}
	//balas
	for(auto &b : balas){
		b.actualizar();
	}
	//enemigo
	if(Li > 0){
		for (auto &enemigo : enemigos) {
			enemigo->actualizar(Player.VerPosicion());
		}
	}
	//escritura txt
	if(muerte.getElapsedTime().asMilliseconds() > 1500){
		newTime = cronometro.getElapsedTime();
		
		bestTimes.push_back(newTime+ Kc*100);
		sort(bestTimes.begin(),bestTimes.end(),compareBestTimes);
		bestTimes.push_back(newTime+ Kc*100);
		
		ofstream o_tiempos("best_times.txt");
		if(o_tiempos.is_open()){
			int tiempo_ms;
			int aux=0;
			for(const auto&tiempo:bestTimes){
				
				tiempo_ms = tiempo.asMilliseconds();
				o_tiempos<<tiempo_ms<<"\n";
				if(aux >4) break;
				aux++;
			}
			int mejort = bestTimes[6].asMilliseconds();
			o_tiempos<<mejort;
		}
		o_tiempos.close();
	}
	//eliminar balas fuera de pantalla
	auto it = remove_if(balas.begin(),balas.end(),fuera_de_la_pantalla);
	balas.erase(it,balas.end());
	//Colisiones
	ColiByE();
	if (ColiPyE()){
		Li -= 1;
	}
	if(Li > 0){
		muerte.restart();
	}
	if(muerte.getElapsedTime().asMilliseconds() > 1500){
		j.CambiarEscena(new Fin);
	}
	//cronometro
	Cronometro();
	tiempo.setPosition(Vector2f (-35,-279)+view.getCenter());
	Reloj_s.setPosition(Vector2f (-70,-280)+view.getCenter());
	//Kill count
	Ecto_s.setPosition(Vector2f (310,-280)+view.getCenter());
	Killc.setString(to_string(Kc));
	Killc.setPosition(Vector2f (350,-270)+view.getCenter());
	//Vidas
	H1_s.setPosition(Vector2f (-380,-280)+view.getCenter());
	H2_s.setPosition(Vector2f (-380,-280)+view.getCenter());
	H3_s.setPosition(Vector2f (-380,-280)+view.getCenter());
	
}


//Renderizado
void Partida::dibujar(RenderWindow &win){
	
	//dibujar fondo
	win.draw(Fondo_s);
	//dibujar bala
	for(Balas &b : balas)
		b.dibujar(win);
	//dibujar enemigos
	for(const auto &e : enemigos)
		e->dibujar(win);
	//dibujar jugador
	if(Li > 0){
		Player.dibujar(win);
	}
	else{
		Player.muerte(win);
	}
	//cronometro
	win.draw(tiempo);
	win.draw(Reloj_s);
	//Kill count
	win.draw(Killc);
	win.draw(Ecto_s);
	//Life
	win.draw(H3_s);
	if(Li>1){
		win.draw(H2_s);
	}
	if(Li>2){
		win.draw(H1_s);
	}
	
}
