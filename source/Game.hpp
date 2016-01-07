#pragma once
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

void GameInit(RenderWindow &window) {
	
}

void RunGame()
{
	///////////// ������������� ///////////////////////////
	RenderWindow window(VideoMode(750, 550), "Claw");

	View view( FloatRect(0, 0, 750, 550) );

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
	

	AnimationManager hero_anim;//��������� �����
	hero_anim.loadFromXML("files/anim_hero.xml", claw_t);
	hero_anim.animList["jump"].loop = 0;

	AnimationManager enemy_anim;//�������� �����
	enemy_anim.create("run", enemy_t, 0, 0, 96, 129, 8, 0.005, 96);
	enemy_anim.create("dead", enemy_t, 0, 720, 112, 112, 7, 0.005, 112);
	enemy_anim.create("attack", enemy_t, 0, 264, 168, 128, 5, 0.005, 168);

	AnimationManager level1_Objects;//�������� ������� ���������� ��������
	level1_Objects.create("move", level1_Objects_t, 0, 728, 56, 128, 4, 0.005, 56);
	level1_Objects.create("move_window", level1_Objects_t, 215, 495, 16, 40, 4, 0.005, 16);
	level1_Objects.create("move_chain", level1_Objects_t, 0, 479, 24, 72, 7, 0.001, 24);
	level1_Objects.create("move_dungeon", level1_Objects_t, 0, 407, 113, 72, 4, 0.001, 113);
	
	AnimationManager coin;//�������� ����������������� ��������
	coin.create("move", coin_t, 0, 0, 32, 32, 9, 0.005, 32);

	AnimationManager move_platform_x_y;
	move_platform_x_y.create("move",moveplatform_t,0,0,95,32,1,0);// 1= ���������� ������
	
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
		entities.push_back(new levelObjects(level1_Objects, lvl, e[i].rect.left, e[i].rect.top, "dungeon")); //level1_Objects ���������, �������, ���������� �, ���������� �

	e = lvl.GetObjects("chain");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new levelObjects(level1_Objects, lvl, e[i].rect.left, e[i].rect.top, "chain")); //level1_Objects ���������, �������, ���������� �, ���������� �

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

	Object pl = lvl.GetObject("player");
	PLAYER Claw(hero_anim, lvl, float(pl.rect.left), float(pl.rect.top));
	Clock clock;
	double CurrentFrame = 0;
	bool dir = false;
	/////////////////// �������� ���� (���) /////////////////////
	while (window.isOpen())
	{
		sf::Int64 time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time/500;  // ����� ���������� �������� ����
		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		//������������
		if (Keyboard::isKeyPressed(Keyboard::Left)) { Claw.key["L"] = true; }
		if (Keyboard::isKeyPressed(Keyboard::Right)) { Claw.key["R"] = true; }
		if (Keyboard::isKeyPressed(Keyboard::Down)) { Claw.key["climb_down"] = true;}
		//������
		if (Keyboard::isKeyPressed(Keyboard::Space)) { Claw.key["jump"] = true;}
		//�� ��������
		if (Keyboard::isKeyPressed(Keyboard::Up)) { Claw.key["climb_up"] = true;}
		//�����
		if ((Keyboard::isKeyPressed(Keyboard::LControl))) {
			Claw.key["l_control"] = true;
		}
		
		//�������� ���������� ��� ���� ��������
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
			//2. ���������� ��������� ����� ����
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
			//3���������� ��������� ������ �����
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
			//3.. � �.�.
			if ((*it)->Name == "easyEnemy")
			{
				//if (Claw.dir) Claw.x += 10; else Claw.x -= 10; ��� ����� ������
				Entity *enemy = *it;
				//Claw.timer += time;
				//if (Claw.timer > 3000) { enemy->dx *= -1; Claw.timer = 0; enemy->anim.flip(); }//������ ����������� �������� ������ 3 ���(�������������� ������ ����� �����������)

				if (enemy->Health <= 0) { continue;} //��� ����������� ������ ��������(���� �� �����)
				if (Claw.getRect().intersects(enemy->getRect())) {
					if (Claw.shoot) {/* enemy->dx = 0;*/ enemy->Health -= 0.25; }
					else if (!Claw.hit_on_enemy) {
						Claw.Health -= 5;
						enemy->attack_straight = true;
						if (enemy->attack_straight) { Claw.hit_on_enemy = true; cout <<"HERO_HP = " << Claw.Health << "\n"; }
						if (Claw.dir) {
							enemy->dir = 1;
							enemy->x = enemy->x + 10; //������� ��� �����
							//Claw.x += 10;
						}
						else {
							enemy->dir = 0;
							enemy->x = enemy->x - 10; //������� ��� �����
							//Claw.x -= 10;
						}

					}
				}
				else
				{

					enemy->x += enemy->dx*time;
					enemy->anim.set("run");
					enemy->dir_attack = false;
				}
			}
		}


		/////////////////////���������� �� �����/////////////////////
		view.setCenter(float(Claw.x),float(Claw.y));

		window.setView(view);

		background.setPosition(view.getCenter());
		window.draw(background);


		lvl.Draw(window);

		for(it=entities.begin();it!=entities.end();it++)
			(*it)->draw(window);

		Claw.draw(window);
		window.display();

	}


}
