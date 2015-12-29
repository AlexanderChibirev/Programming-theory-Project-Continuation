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
#include "levelObjects.hpp"
using namespace sf;


void RunGame()
{
	///////////// инициализация ///////////////////////////
	RenderWindow window(VideoMode(950, 780), "Claw");

	View view( FloatRect(0, 0, 500, 400) );

	Level lvl;
	lvl.LoadFromFile("files/Level1.tmx");

	Texture moveplatform_t, claw_t, enemy_t, coin_t, level1_Objects_t;
	moveplatform_t.loadFromFile("files/images/movingPlatform.png");
    claw_t.loadFromFile("files/images/hero.png");
	enemy_t.loadFromFile("files/images/Enemies-OfficerF.png");
	level1_Objects_t.loadFromFile("files/images/level1_Objects.png");
	coin_t.loadFromFile("files/images/coin.png");

	AnimationManager hero_anim;
	hero_anim.loadFromXML("files/anim_hero.xml", claw_t);
	hero_anim.animList["jump"].loop = 0;

	//AnimationManager enemy_anim;
	//enemy_anim.loadFromXML("files/anim_hero.xml", enemy_t);
	//enemy_anim.animList["stay"].loop = 0;

	AnimationManager level1_Objects;
	level1_Objects.create("move", level1_Objects_t, 0, 728, 56, 128, 4, 0.005, 56);
	level1_Objects.create("move_window", level1_Objects_t, 215, 495, 16, 40, 4, 0.005, 16);
	level1_Objects.create("move_chain", level1_Objects_t, 0, 479, 24, 72, 7, 0.004, 24);
	level1_Objects.create("move_dungeon", level1_Objects_t, 0, 407, 113, 72, 4, 0.001, 113);
	
	AnimationManager coin;
	coin.create("move", coin_t, 0, 0, 32, 32, 9, 0.005, 32);

	AnimationManager move_platform_x_y;
	move_platform_x_y.create("move",moveplatform_t,0,0,95,32,1,0);// 1= количество кадров
	
	AnimationManager move_platform_y;
	move_platform_y.create("move", moveplatform_t, 0, 0, 95, 32, 1, 0);
	//pullUpLadder

	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;
	std::vector<Object> e = lvl.GetObjects("easyEnemy");
	/*for (int i=0;i < e.size();i++)
		entities.push_back(new ENEMY(enemy_anim, lvl, e[i].rect.left, e[i].rect.top) );
*/
	e = lvl.GetObjects("dungeon");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new levelObjects(level1_Objects, lvl, e[i].rect.left, e[i].rect.top, "dungeon")); //level1_Objects анимейшен, уровень, координата х, координата у

	e = lvl.GetObjects("chain");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new levelObjects(level1_Objects, lvl, e[i].rect.left, e[i].rect.top, "chain")); //level1_Objects анимейшен, уровень, координата х, координата у

	e = lvl.GetObjects("torch_window");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new levelObjects(level1_Objects, lvl, e[i].rect.left, e[i].rect.top, "torch_window"));

	e = lvl.GetObjects("torch");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new levelObjects(level1_Objects, lvl, e[i].rect.left, e[i].rect.top, "torch"));

	e = lvl.GetObjects("coin");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new levelObjects(coin, lvl, e[i].rect.left, e[i].rect.top, "coin"));

	e = lvl.GetObjects("movingPlatformX");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new MovingPlatform(move_platform_x_y, lvl, e[i].rect.left, e[i].rect.top, "movingPlatformX"));

	e = lvl.GetObjects("movingPlatformY");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new MovingPlatform(move_platform_x_y, lvl, e[i].rect.left, e[i].rect.top, "movingPlatformY"));

	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setColor(Color::White);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	Object pl = lvl.GetObject("player");
	PLAYER Claw(hero_anim, lvl, float(pl.rect.left), float(pl.rect.top));
	Clock clock;
	//Clock cloker;

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
		//float timeer = cloker.getElapsedTime().asSeconds();
		if (Keyboard::isKeyPressed(Keyboard::LControl)) { 
			Claw.key["l_control"] = true; }
		//if (timeer > 3) Claw.key["l_control"] = false;
		//вызываем обновление для всех объектов
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
			//2. движущиеся платформа вверх вниз
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
			//3движущиеся платформа вправо влево
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
		text.setString("ЗОЛОТО:");//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(1412,2120);//задаем позицию текста, отступая от центра камеры
		window.draw(text);//рисую этот текст
		view.setCenter(float(Claw.x),float(Claw.y));
		window.draw(text);
		window.setView(view);

		lvl.Draw(window);

		for(it=entities.begin();it!=entities.end();it++)
			(*it)->draw(window);

		Claw.draw(window);

		window.display();
	}


}

#endif GAME_H

