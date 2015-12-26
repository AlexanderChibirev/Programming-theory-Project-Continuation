#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "level.hpp"
#include "Animation.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "MovingPlatform.hpp"
using namespace sf;


void RunGame()
{
	///////////// инициализаци€ ///////////////////////////
	RenderWindow window(VideoMode(950, 780), "Claw");

	View view( FloatRect(0, 0, 500, 400) );

	Level lvl;
	lvl.LoadFromFile("files/Level1.tmx");

	Texture moveplatform_t, claw_t;
	moveplatform_t.loadFromFile("files/images/movingPlatform.png");
    claw_t.loadFromFile("files/images/hero.png");


	AnimationManager hero_anim;
	hero_anim.loadFromXML("files/anim_hero.xml",claw_t);
	hero_anim.animList["jump"].loop = 0;

	//AnimationManager enemy_anim;//создаем объект, с ним производим монипул€ции, т.е. создаем анимацию
	//enemy_anim.create("move",enemy_t,0,0,16,16,2,0.002,18);
	//enemy_anim.create("dead",enemy_t,58,0,16,16,1,0);

	AnimationManager move_platform_x_y;
	move_platform_x_y.create("move",moveplatform_t,0,0,95,32,1,0);
	AnimationManager move_platform_y;
	move_platform_y.create("move", moveplatform_t, 0, 0, 95, 32, 1, 0);
	//pullUpLadder

	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;
	std::vector<Object> e = lvl.GetObjects("easyEnemy");
	/*for (int i=0;i < e.size();i++)
		entities.push_back(new ENEMY(enemy_anim, lvl, e[i].rect.left, e[i].rect.top) );
*/
	e = lvl.GetObjects("movingPlatformX");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new MovingPlatform(move_platform_x_y, lvl, e[i].rect.left, e[i].rect.top, "movingPlatformX"));
	e = lvl.GetObjects("movingPlatformY");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new MovingPlatform(move_platform_x_y, lvl, e[i].rect.left, e[i].rect.top, "movingPlatformY"));



	Object pl = lvl.GetObject("player");
	PLAYER Claw(hero_anim, lvl, pl.rect.left, pl.rect.top);
	Clock clock;

	/////////////////// основной цикл  /////////////////////
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time/500;  // здесь регулируем скорость игры

		if (time > 40) time = 40;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		//передвижение
		if (Keyboard::isKeyPressed(Keyboard::Left)) Claw.key["L"]=true;
		if (Keyboard::isKeyPressed(Keyboard::Right)) Claw.key["R"]=true;
		if (Keyboard::isKeyPressed(Keyboard::Down)) Claw.key["climb_down"]=true;
		//прыжок
		if (Keyboard::isKeyPressed(Keyboard::Space)) Claw.key["jump"] = true;
		//по лестнице
		if (Keyboard::isKeyPressed(Keyboard::Up)) Claw.key["climb_up"] = true;
		//атака
		if (Keyboard::isKeyPressed(Keyboard::X)) Claw.key["LControl"] = true;
		//вызываем обновление дл€ всех объектов
		for(it=entities.begin();it!=entities.end();)
		{
			Entity *b = *it;
			b->update(time);
			if (b->life==false)	{ it  = entities.erase(it); delete b;}
			else it++;
		}


		Claw.update(time);


		for(it=entities.begin();it!=entities.end();it++)
		{
			//2. движущиес€ платформа вверх вниз
			if ((*it)->Name == "movingPlatformY")
			{
				Entity *movPlatY = *it;
				if (Claw.getRect().intersects(movPlatY->getRect()))
					if (Claw.dy>0)
						if (Claw.y + Claw.h<movPlatY->y + movPlatY->h)
						{
							Claw.y = movPlatY->y - Claw.h + 10;/* Claw.x += movPlatY->dx*time;*/ Claw.dy = 0; Claw.STATE = PLAYER::stay;
						}
			}
			//3движущиес€ платформа вправо влево
			if ((*it)->Name == "movingPlatformX")
			{
				Entity *movPlatX = *it;
				if (Claw.getRect().intersects(movPlatX->getRect()))
					if (Claw.dy>0)
						if (Claw.y + Claw.h<movPlatX->y + movPlatX->h)
						{
							Claw.y = movPlatX->y - Claw.h + 10; Claw.x += movPlatX->dx*time; Claw.dy = 0; Claw.STATE = PLAYER::stay;
						}
			}
			//3.. и т.д.
		}


		/////////////////////отображаем на экран/////////////////////
		view.setCenter( Claw.x,Claw.y);
		window.setView(view);


		lvl.Draw(window);

		for(it=entities.begin();it!=entities.end();it++)
			(*it)->draw(window);

		Claw.draw(window);

		window.display();
	}


}

#endif GAME_H

