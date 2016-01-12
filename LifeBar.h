#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

using namespace sf;

class PLAYER;

class LifeBar
{
public:
	Image image;
	Texture t;
	Sprite s;
	int max;
	RectangleShape bar;
	LifeBar();
	//~LifeBar();
	void update(int);
	void draw(RenderWindow &window);
};

