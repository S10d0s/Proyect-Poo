#ifndef PARTIDA_H
#define PARTIDA_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Pj.h"
#include "Juego.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include "Enemigos.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
using namespace sf;
using namespace std;

class Partida : public Escena{
public:
	Partida();
	void actualizar(Juego &j, RenderWindow &win) override;
	void dibujar(RenderWindow &win) override;
	void CentrarCamara(RenderWindow &win);
	void GenerarEnemigos();
	void GenerarBalas(RenderWindow &win);
	void ColiByE();
	bool ColiPyE();
	void Cronometro();
private:
	Clock DisC, C1, Spawn_enemigo, cronometro, muerte;
	Texture Fondo_t, H1_t, H2_t, H3_t, Ecto_t, Reloj_t;
	Sprite Fondo_s, H1_s, H2_s, H3_s, Ecto_s, Reloj_s;
	Pj Player;
	vector<Balas> balas;
	View view;
	Vector2f mapSize, viewCenter;
	vector<unique_ptr<Enemigos>> enemigos;
	Font font;
	Text tiempo, Killc;
	int ite, Kc, Li;
	Time newTime;
	vector<Time> bestTimes;
};

#endif

