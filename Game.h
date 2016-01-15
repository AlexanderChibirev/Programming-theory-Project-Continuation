#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "level.h"
#include "Player.h"
#include "MovingPlatform.h"
#include "levelObjects.h"
#include "LifeBar.h"
#include "Enemy.h"
//#include "Bullet.h"
#include "EnemyMouse.h"
#include "MovingPlatform.hpp"
#include "Entity.h"
#include "Game.h"
#include <sstream>
#include <iostream>

using namespace sf;


void RunGame(RenderWindow &window)
{
	///////////// инициализация //////////////////////////
	View view( FloatRect(0, 0, 750, 550) );

	int flag = 0;
	Level lvl;
	lvl.LoadFromFile("files/Level1.tmx");

	Texture moveplatform_t;
	Texture dead_t;
	Texture claw_t;
	Texture enemy_t;
	Texture enemy_mouse_t;
	Texture coin_t;
	Texture level1_Objects_t;
	Texture background_t;

	Font font;//шрифт 
	font.loadFromFile("files/CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setColor(Color::Yellow);//покрасили текст в желтый. если убрать эту строку, то по умолчанию он белый
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	enemy_mouse_t.loadFromFile("images/mouse.png");
	dead_t.loadFromFile("files/images/dead.png");
	background_t.loadFromFile("files/images/bg.png");
	moveplatform_t.loadFromFile("files/images/movingPlatform.png");
    claw_t.loadFromFile("files/images/hero.png");
	enemy_t.loadFromFile("files/images/Enemies-OfficerF.png");
	level1_Objects_t.loadFromFile("files/images/level1_Objects.png");
	coin_t.loadFromFile("files/images/coin.png");
	Sprite dead_s(dead_t);

	AnimationManager hero_anim;//загружаем героя
	hero_anim.loadFromXML("files/anim_hero.xml", claw_t);
	hero_anim.animList["jump"].loop = 0;

	AnimationManager enemy_mouse_anim;
	enemy_mouse_anim.create("stay", enemy_mouse_t, 0, 63, 48, 40, 4, 0.004, 48);
	enemy_mouse_anim.create("dead", enemy_mouse_t, 0, 111, 56, 72, 4, 0.004, 56);
	enemy_mouse_anim.create("attack", enemy_mouse_t, 264, 8, 56, 48, 4, 0.004, 56);

	AnimationManager enemy_anim;//загрузка врага
	enemy_anim.create("hit_on_hero", enemy_t, 0, 880, 176, 144, 4, 0.004, 176);
	enemy_anim.create("run", enemy_t, 0, 0, 120, 129, 8, 0.005, 120);
	enemy_anim.create("dead", enemy_t, 0, 720, 112, 112, 7, 0.005, 112);
	enemy_anim.create("attack", enemy_t, 0, 264, 168, 128, 5, 0.005, 168);

	AnimationManager level1_Objects;//загрузка фоновых движущихся объектов
	level1_Objects.create("move", level1_Objects_t, 0, 728, 56, 128, 4, 0.005, 56);
	level1_Objects.create("move_window", level1_Objects_t, 215, 495, 16, 40, 4, 0.005, 16);
	level1_Objects.create("move_chain", level1_Objects_t, 0, 479, 24, 72, 7, 0.001, 24);
	level1_Objects.create("move_dungeon", level1_Objects_t, 0, 407, 113, 72, 4, 0.001, 113);
	
	AnimationManager coin;//загрузка взаимодействующих объектов
	coin.create("move", coin_t, 0, 0, 32, 32, 9, 0.005, 32);

	AnimationManager coin1;//загрузка взаимодействующих объектов
	coin1.create("move", coin_t, 0, 115, 40, 29, 4, 0.005, 40);
	
	AnimationManager coin2;//загрузка взаимодействующих объектов
	coin2.create("move", coin_t, 0, 250, 38, 39, 4, 0.005, 38);

	AnimationManager coin3;//загрузка взаимодействующих объектов
	coin3.create("move", coin_t, 0, 186, 36, 38, 4, 0.005, 36);

	AnimationManager move_platform_x;
	move_platform_x.create("move",moveplatform_t,0,0,95,32,1,0);// 1= количество кадров
	
	AnimationManager move_platform_y;
	move_platform_y.create("move", moveplatform_t, 0, 0, 95, 32, 1, 0);

	AnimationManager move_platform_up;
	move_platform_up.create("move", moveplatform_t, 0, 0, 95, 32, 1, 0);

	Sprite background(background_t);
	background.setOrigin(float(background_t.getSize().x / 2), float(background_t.getSize().y / 2));

	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;

	std::vector<Object> e_m = lvl.GetObjects("mouse");
	for (int i = 0; i < e_m.size(); i++)
		entities.push_back(new EnemyMouse(enemy_mouse_anim, lvl, e_m[i].rect.left, e_m[i].rect.top));

	
	std::vector<Object> e = lvl.GetObjects("dungeon");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new levelObjects(level1_Objects, lvl, e[i].rect.left, e[i].rect.top, "dungeon")); //level1_Objects анимейшен, уровень, координата х, координата у

	e = lvl.GetObjects("easyEnemy");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new ENEMY(enemy_anim, lvl, e[i].rect.left, e[i].rect.top));

	e = lvl.GetObjects("chain");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new levelObjects(level1_Objects, lvl, e[i].rect.left, e[i].rect.top, "chain")); //level1_Objects анимейшен, уровень, координата х, координата у

	e = lvl.GetObjects("torch_window");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new levelObjects(level1_Objects, lvl, e[i].rect.left, e[i].rect.top, "torch_window"));

	e = lvl.GetObjects("torch");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new levelObjects(level1_Objects, lvl, e[i].rect.left, e[i].rect.top, "torch"));
//////////////////////////////////////////////////////////////////
	e = lvl.GetObjects("coin");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new levelObjects(coin, lvl, e[i].rect.left, e[i].rect.top, "coin"));
	e = lvl.GetObjects("coin1");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new levelObjects(coin1, lvl, e[i].rect.left, e[i].rect.top, "coin1"));
	e = lvl.GetObjects("coin2");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new levelObjects(coin2, lvl, e[i].rect.left, e[i].rect.top, "coin2"));
	e = lvl.GetObjects("coin3");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new levelObjects(coin3, lvl, e[i].rect.left, e[i].rect.top, "coin3"));
/////////////////////////////////////////////////////////////////

	e = lvl.GetObjects("movingPlatformUp");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new levelObjects(move_platform_up, lvl, e[i].rect.left, e[i].rect.top, "movingPlatformUp"));

	e = lvl.GetObjects("movingPlatformX");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new MovingPlatform(move_platform_x, lvl, e[i].rect.left, e[i].rect.top, "movingPlatformX"));

	e = lvl.GetObjects("movingPlatformY");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new MovingPlatform(move_platform_x, lvl, e[i].rect.left, e[i].rect.top, "movingPlatformY"));

	Object pl = lvl.GetObject("player");
	PLAYER Claw(hero_anim, lvl, float(pl.rect.left), float(pl.rect.top));
	Clock clock;
	double CurrentFrame = 0;
	double CurrentFrame2 = 0;
	bool dir = false;
	LifeBar lifeBarPlayer;

	/////////////////// основной цикл (код) /////////////////////
	while (window.isOpen())
	{
		lifeBarPlayer.update(Claw.Health);
		sf::Int64 time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time/500;  // здесь регулируем скорость игры
		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		//передвижение
		if (Keyboard::isKeyPressed(Keyboard::Left)) { Claw.key["L"] = true; }
		if (Keyboard::isKeyPressed(Keyboard::Right)) { Claw.key["R"] = true; }
		if (Keyboard::isKeyPressed(Keyboard::Down)) { Claw.key["climb_down"] = true; Claw.hit_on_enemy = false;}
		//прыжок
		if (Keyboard::isKeyPressed(Keyboard::Space)) { Claw.key["jump"] = true;}
		//по лестнице
		if (Keyboard::isKeyPressed(Keyboard::Up)) { Claw.key["climb_up"] = true;}
		//атака
		if ((Keyboard::isKeyPressed(Keyboard::LControl))) {
			Claw.key["l_control"] = true;
		}
		
		//вызываем обновление для всех объектов
		for(it=entities.begin();it!=entities.end();)
		{
			Entity *b = *it;
			b->update(float(time));
			if (b->life == false && (b->Name != "coin" && b->Name != "coin1"&& b->Name != "coin2"&& b->Name != "coin3" ))	{ it  = entities.erase(it); delete b;}
			else it++;
		}


		Claw.update(float(time));


		for (it = entities.begin(); it != entities.end(); it++)
		{
			//2. движущиеся платформа вверх вниз
			if ((*it)->Name == "movingPlatformY")
			{
				Entity *movPlatY = *it;
				if (Claw.getRect().intersects(movPlatY->getRect()))
					if (Claw.dy > 0)
						if (Claw.y + Claw.h < movPlatY->y + movPlatY->h)
						{
							Claw.y = movPlatY->y - Claw.h + 10; Claw.dy = 0; Claw.STATE = PLAYER::stay;
						}
			}
			//3движущиеся платформа вправо влево
			if ((*it)->Name == "movingPlatformX")
			{
				Entity *movPlatX = *it;
				if (Claw.getRect().intersects(movPlatX->getRect()))
					if (Claw.dy>0)
						if (Claw.y + Claw.h < movPlatX->y + movPlatX->h)
						{
							Claw.y = movPlatX->y - Claw.h + 10; Claw.x += movPlatX->dx * time; Claw.dy = 0; Claw.STATE = PLAYER::stay;
						}
			}
			//3.. и т.д.
			if ((*it)->Name == "easyEnemy")
			{
				Entity *enemy = *it;
				if (enemy->Health <= 0) { continue;} //для прекращения вызова анимации(удар от врага)
				if (Claw.getRect().intersects(enemy->getRect())) {
					if (Claw.shoot && Claw.STATE != Claw.sit_down) { enemy->claw_shoot = true; enemy->Health -= 0.25; } //если враг атакует и не сидит, то враг не может атаковать
					else if (!Claw.hit_on_enemy) {
						enemy->attack_start = true;
						if (enemy->attack_start) { Claw.hit_on_enemy = true; Claw.dy = 0; Claw.Health -= float(0.07); }
						//////////////////////////////////////////////////////
						if (Claw.dir == 1 && enemy->dir == 1 /*&& flag == 0*/) {
							enemy->dir = 1; //если враг смотрит влево и враг смотрит влево, то враг атакует влево
							flag = 1;
							enemy->x = enemy->x - 1; //смещаем при атаке
						}
						else if (Claw.dir == 0 && enemy->dir == 0 /*&& flag == 0*/) {
							enemy->dir = 0; //если персонаж смотрит вправо и враг смотрит вправо, то он бьет его вправо
							flag = 1;
							enemy->x = enemy->x + 1; //смещаем при атаке
						}
						else if (Claw.dir == 1 && enemy->dir == 0 /*&& flag == 0*/) {
							enemy->dir = 0; //если перс смотрит влево, а враг вправо, то враг бьет вправо
							flag = 1;
							enemy->x = enemy->x + 1; //смещаем при атаке
						}
						else if (Claw.dir == 0 && enemy->dir == 1 /*&& flag == 0*/) {
							enemy->dir = 1; //если перс смотрит вправо, а враг влево, то бьет враг влево
							flag = 1;
							enemy->x = enemy->x - 1; //смещаем при атаке
						}
						///////////////////////////////////////////////
					}
				}
				else
				{
					enemy->x += enemy->dx*time;
					enemy->anim.set("run");
					enemy->dir_attack = false;
				}
			}

			if ((*it)->Name == "coin")
			{
				Entity *coin = *it;
				if (Claw.getRect().intersects(coin->getRect()))
				{
					coin->life = false;
					Claw.points_coins += 10;
				}
			}
			
			if ((*it)->Name == "coin1")
			{
				Entity *coin = *it;
				if (Claw.getRect().intersects(coin->getRect()))
				{
					coin->life = false;
					Claw.points_coins += 5000;
				}
			}
			if ((*it)->Name == "coin2")
			{
				Entity *coin = *it;
				if (Claw.getRect().intersects(coin->getRect()))
				{
					coin->life = false;
					Claw.points_coins += 1000;
				}
			}
			if ((*it)->Name == "coin3")
			{
				Entity *coin = *it;
				if (Claw.getRect().intersects(coin->getRect()))
				{
					coin->life = false;
					Claw.points_coins += 10000;
				}
			}
			if ((*it)->Name == "movingPlatformUp")
			{
				Entity *movPlatUp = *it;
				if (Claw.getRect().intersects(movPlatUp->getRect()))
					if (Claw.dy>0)
						if (Claw.y + Claw.h < movPlatUp->y + movPlatUp->h)
						{
							Claw.y = movPlatUp->y - Claw.h + 10;
							Claw.x += movPlatUp->dx * time; 
							movPlatUp->x += movPlatUp->dx * time;
							Claw.dy = 0;
							Claw.STATE = PLAYER::stay;
						}
			}
		}


		/////////////////////отображаем на экран/////////////////////
		view.setCenter(float(Claw.x),float(Claw.y));

		window.setView(view);

		background.setPosition(view.getCenter());
		window.draw(background);
		std::ostringstream  playerScoreString;
		playerScoreString << Claw.points_coins;//	playerHealthString << p.health; gameTimeString << gameTime;//занесли в нее число очков, то есть формируем строку

		text.setString("ЗОЛОТО:" + playerScoreString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(view.getCenter().x-340, view.getCenter().y-270);//задаем позицию текста, отступая от центра камеры

		lvl.Draw(window);
		window.draw(dead_s);
		for(it=entities.begin();it!=entities.end();it++)
			(*it)->draw(window);
		Claw.draw(window);
		lifeBarPlayer.draw(window);
		window.draw(text);//рисую этот текст
		window.display();
		while (Claw.life == false) {
			if (CurrentFrame < 100) { window.clear(); }
			CurrentFrame += time;
			dead_s.setOrigin(float(background_t.getSize().x / 2), float(background_t.getSize().y / 2));
			dead_s.setPosition(view.getCenter());
			window.draw(dead_s);
			cout << CurrentFrame<<endl;
			window.display();
			if (CurrentFrame > 4000) RunGame(window);
		}

	}


}
