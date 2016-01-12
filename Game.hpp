#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "level.hpp"
#include "Animation.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
//#include "MovingPlatform.h"
#include "levelObjects.hpp"
#include "LifeBar.h"

using namespace sf;

void GameInit(RenderWindow &window) {
	
}

void RunGame(RenderWindow &window)
{
	///////////// инициализация ///////////////////////////

	View view( FloatRect(0, 0, 750, 550) );

	int flag = 0;
	Level lvl;
	lvl.LoadFromFile("files/Level1.tmx");

	Texture moveplatform_t;
	Texture claw_t;
	Texture enemy_t;
	Texture coin_t;
	Texture level1_Objects_t;
	Texture background_t;

	background_t.loadFromFile("files/images/bg.png");
	moveplatform_t.loadFromFile("files/images/movingPlatform.png");
    claw_t.loadFromFile("files/images/hero.png");
	enemy_t.loadFromFile("files/images/Enemies-OfficerF.png");
	level1_Objects_t.loadFromFile("files/images/level1_Objects.png");
	coin_t.loadFromFile("files/images/coin.png");
	

	AnimationManager hero_anim;//загружаем героя
	hero_anim.loadFromXML("files/anim_hero.xml", claw_t);
	hero_anim.animList["jump"].loop = 0;

	AnimationManager enemy_anim;//загрузка врага
	enemy_anim.create("hit_on_hero", enemy_t, 0, 880, 137, 144, 4, 0.004, 144);
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

	AnimationManager move_platform_x_y;
	move_platform_x_y.create("move",moveplatform_t,0,0,95,32,1,0);// 1= количество кадров
	
	AnimationManager move_platform_y;
	move_platform_y.create("move", moveplatform_t, 0, 0, 95, 32, 1, 0);

	Sprite background(background_t);
	background.setOrigin(float(background_t.getSize().x / 2), float(background_t.getSize().y / 2));

	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;
	
	std::vector<Object> e = lvl.GetObjects("easyEnemy");
	for (int i=0;i < e.size();i++)
		entities.push_back(new ENEMY(enemy_anim, lvl, e[i].rect.left, e[i].rect.top) );

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

	/*e = lvl.GetObjects("movingPlatformX");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new MovingPlatform(move_platform_x_y, lvl, e[i].rect.left, e[i].rect.top, "movingPlatformX"));

	e = lvl.GetObjects("movingPlatformY");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new MovingPlatform(move_platform_x_y, lvl, e[i].rect.left, e[i].rect.top, "movingPlatformY"));
*/
	Object pl = lvl.GetObject("player");
	PLAYER Claw(hero_anim, lvl, float(pl.rect.left), float(pl.rect.top));
	Clock clock;
	double CurrentFrame = 0;
	bool dir = false;
	LifeBar lifeBarPlayer;

	/////////////////// основной цикл (код) /////////////////////
	while (window.isOpen())
	{
		lifeBarPlayer.update(int(Claw.Health));
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
			if (b->life==false)	{ it  = entities.erase(it); delete b;}
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
							Claw.y = movPlatX->y - Claw.h + 10; Claw.x += movPlatX->dx*time; Claw.dy = 0; Claw.STATE = PLAYER::stay;
						}
			}
			//3.. и т.д.
			//FloatRect(enemy.sprite.getGlobalBounds().left, .top, .width, .heigth).intersects(obj[i].rect)
			if ((*it)->Name == "easyEnemy")
			{
				//if (Claw.dir) Claw.x += 10; else Claw.x -= 10; при ударе отскок
				Entity *enemy = *it;
				//Claw.timer += time;
				//if (Claw.timer > 3000) { enemy->dx *= -1; Claw.timer = 0; enemy->anim.flip(); }//меняет направление примерно каждые 3 сек(альтернативная версия смены направления)

				if (enemy->Health <= 0) { continue;} //для прекращения вызова анимации(удар от врага)
				if (Claw.getRect().intersects(enemy->getRect())) {
					if (Claw.dx > 0 || Claw.dx < 0) { Claw.Health -= float(0.5); }
					if (Claw.dy > 0 || Claw.dy < 0) { Claw.Health -= float(0.5); }
					if (Claw.shoot) { enemy->claw_shoot = true; enemy->Health -= 0.25;}
					else if (!Claw.hit_on_enemy) {

						enemy->attack_start = true;
						if (enemy->attack_start) { Claw.hit_on_enemy = true; Claw.Health -= float(0.1); }
						//////////////////////////////////////////////////////
						if (Claw.dir == 1 && enemy->dir == 1 /*&& flag == 0*/) {
							enemy->dir = 1; //если враг смотрит влево и враг смотрит влево, то враг атакует влево
							//cout << "1";
							flag = 1;
							enemy->x = enemy->x - 3; //смещаем при атаке
							//Claw.x += 10;
						}
						else if (Claw.dir == 0 && enemy->dir == 0 /*&& flag == 0*/) {
							enemy->dir = 0; //если персонаж смотрит вправо и враг смотрит вправо, то он бьет его вправо
							//cout << "2";
							flag = 1;
							enemy->x = enemy->x + 3; //смещаем при атаке
							//Claw.x -= 10;
						}
						else if (Claw.dir == 1 && enemy->dir == 0 /*&& flag == 0*/) {
							enemy->dir = 0; //если перс смотрит влево, а враг вправо, то враг бьет вправо
							//cout << "3";
							flag = 1;
							enemy->x = enemy->x + 3; //смещаем при атаке
							//Claw.x -= 10;
						}
						else if (Claw.dir == 0 && enemy->dir == 1 /*&& flag == 0*/) {
							enemy->dir = 1; //если перс смотрит вправо, а враг влево, то бьет враг влево
							//cout << "4";
							flag = 1;
							enemy->x = enemy->x - 3; //смещаем при атаке
							//Claw.x -= 10;
						}
						///////////////////////////////////////////////
					}
				}
				else
				{
					//flag = 0;
					enemy->x += enemy->dx*time;
					enemy->anim.set("run");
					enemy->dir_attack = false;
				}
			}
		}


		/////////////////////отображаем на экран/////////////////////
		view.setCenter(float(Claw.x),float(Claw.y));

		window.setView(view);

		background.setPosition(view.getCenter());
		window.draw(background);


		lvl.Draw(window);

		for(it=entities.begin();it!=entities.end();it++)
			(*it)->draw(window);
		Claw.draw(window);
		lifeBarPlayer.draw(window);
		window.display();

	}


}
