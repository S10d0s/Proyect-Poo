#include "Juego.h"
#include "Menu.h"

int main(int argc, char *argv[]){
	Juego J(new Menu);
	J.jugar();
	return 0;
}

