#include "Fin.h"
#include <SFML/Window/Keyboard.hpp>
#include "Juego.h"
#include "Menu.h"
#include <fstream>
using namespace std;

Fin::Fin() {
	view.setCenter(400,300);
	view.setSize(800,600);
	
	menu.definir(Vector2f (320,434),Vector2f (175,40));
	
	font.loadFromFile("Minecraft.ttf");
	fondo_t.loadFromFile("Sprites/Ladrillos.png");
	fondo_s.setTexture(fondo_t);
	fondo_s.setColor(Color(100,100,100));
	fondo_s.setPosition(0,0);
	
	text_ti.setFont(font);
	text_ti.setPosition(230,150);
	text_ti.setCharacterSize(60);
	text_ti.setString("GAME OVER");
	
	text_p.setFont(font);
	text_p.setPosition(340,440);
	text_p.setCharacterSize(20);
	text_p.setString("Back To Menu");
	
	text_c.setFont(font);
	text_c.setPosition(305,260);
	text_c.setCharacterSize(25);
	text_c.setString("Te moriste capo");
	
	ifstream i_tiempos("best_times.txt");
	if(i_tiempos.is_open()){
		int tiempo;
		while (i_tiempos>>tiempo){
			bestTimes.push_back(tiempo);
		}
	}
	i_tiempos.close();
	
	string bt = "Mejores Puntajes \n";
	for(int i=0;i<5;i++) {
		bt += to_string(bestTimes[i]) + "\n";
		
	}
	bt += "Tu Puntaje \n" + to_string(bestTimes[6]);
	
	text_tiempo.setFont(font);
	text_tiempo.setPosition(50,260);
	text_tiempo.setCharacterSize(25);
	text_tiempo.setString(bt);
}

void Fin::actualizar(Juego &j, RenderWindow &win){
	win.setView(view);
	if (menu.presiona(win,view))
		j.CambiarEscena(new Menu);
}

void Fin::dibujar(RenderWindow &win){
	win.draw(fondo_s);
	menu.dibujar(win);
	win.draw(text_p);
	win.draw(text_ti);
	win.draw(text_c);
	win.draw(text_tiempo);
}

