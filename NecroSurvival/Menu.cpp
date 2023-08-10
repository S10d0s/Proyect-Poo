#include "Menu.h"
#include "Partida.h"
#include "Juego.h"
#include <SFML/Window/Keyboard.hpp>

Menu::Menu() {
	view.setCenter(400,300);
	view.setSize(800,600);
	
	play.definir(Vector2f (300,534),Vector2f (220,40));
	
	font.loadFromFile("Minecraft.ttf");
	fondo_t.loadFromFile("Sprites/Ladrillos.png");
	fondo_s.setTexture(fondo_t);
	fondo_s.setColor(Color(100,100,100));
	fondo_s.setPosition(0,0);

	text_ti.setFont(font);
	text_ti.setPosition(140,150);
	text_ti.setCharacterSize(60);
	text_ti.setString("NECRO SURVIVAL");
	
	text_p.setFont(font);
	text_p.setPosition(320,540);
	text_p.setCharacterSize(20);
	text_p.setString("Press here to play");
	
	text_c.setFont(font);
	text_c.setPosition(120,360);
	text_c.setCharacterSize(25);
	text_c.setString("Movimiento: -W , -A , -S , -D     Disparo: -Mouse");
}

void Menu::actualizar(Juego &j, RenderWindow &win){
	win.setView(view);
	if (play.presiona(win,view))
		j.CambiarEscena(new Partida);
}

void Menu::dibujar(RenderWindow &win){
	win.draw(fondo_s);
	play.dibujar(win);
	win.draw(text_p);
	win.draw(text_ti);
	win.draw(text_c);
}
