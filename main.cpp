#include "Game.hpp"
#include "menu.h"

int main()
{
	RenderWindow window(VideoMode(750, 550), "Claw");
	//menu(window);
	RunGame(window);
	return 0;
}
