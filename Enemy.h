#pragma once
#include "Entity.h"
//#include "level.hpp"
using namespace std;
//#include "Player.hpp"

class ENEMY: public Entity
{
public:

	ENEMY(AnimationManager &a,Level &lev,float x,float y):Entity(a,x,y)
	{
		Level lvl;
		lvl.LoadFromFile("files/Level1.tmx");
		objR = lvl.GetObjects("solid_for_enemy_R");
		objL = lvl.GetObjects("solid_for_enemy_L");
		option("easyEnemy", float(0.09), 100, "run");
	}

	void update(float time)
	{ //dir 1 в норм сторону 0  зеркально
		for (int i = 0; i<objR.size(); i++)//проходимся по объектам
			if (getRect().intersects(objR[i].rect))//проверяем пересечение игрока с объектом
			{
				if (objR[i].name == "solid_for_enemy_R")//если встретили препятствие
				{
					if (dx > 0) { x = objR[i].rect.left - w; dx *= -1; dir = !dir; }
				}
			}
		for (int i = 0; i<objL.size(); i++)//проходимся по объектам
			if (getRect().intersects(objL[i].rect))//проверяем пересечение игрока с объектом
			{
				if (objL[i].name == "solid_for_enemy_L")//если встретили препятствие
				{
					if (dx < 0) { x = objL[i].rect.left + objL[i].rect.width; dx *= -1; dir = !dir; }
				}
			}
		timer += time;
		if (attack_start && claw_shoot == false) {
			anim.set("attack");
			attack_start = false;
			dir_attack = true;
		}
		else if (Health > 0 && claw_shoot == true) {
			anim.set("hit_on_hero");
			timer += time; 
			if (timer > 1000) {
				claw_shoot = false;
			}
		}
		else if (Health <= 0) {
			anim.set("dead");
			currentFrame += 0.005*time;
			x = x + 0.5;
			y = y + 0.7;
			if (currentFrame > 7) { anim.pause(); life = false; }
		}
		anim.flip(dir);
		anim.tick(time);
	}
};
