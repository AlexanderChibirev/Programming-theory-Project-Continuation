#pragma once
#include "Entity.hpp"
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
		option("easyEnemy", float(0.08), 20, "run");
	}

	void update(float time)
	{ //dir 1 � ���� ������� 0  ���������
		for (int i = 0; i<objR.size(); i++)//���������� �� ��������
			if (getRect().intersects(objR[i].rect))//��������� ����������� ������ � ��������
			{
				if (objR[i].name == "solid_for_enemy_R")//���� ��������� �����������
				{
					if (dx > 0) { x = objR[i].rect.left - w; dx *= -1; dir = !dir; }
				}
			}
		for (int i = 0; i<objL.size(); i++)//���������� �� ��������
			if (getRect().intersects(objL[i].rect))//��������� ����������� ������ � ��������
			{
				if (objL[i].name == "solid_for_enemy_L")//���� ��������� �����������
				{
					if (dx < 0) { x = objL[i].rect.left + objL[i].rect.width; dx *= -1; dir = !dir; }
				}
			}
		timer += time;
		/*if (timer > 4000 && (dir_attack == false))
		{
			x += dx*time;
			dx *= -1;
			dir = !dir;
			timer = 0;
		}*/
		if (attack_start) {
			anim.set("attack");
			attack_start = false;
			dir_attack = true;
		}
		if (Health > 0 && claw_shoot == true) { 
			anim.set("hit_on_hero");
			timer += time; 
			if (timer > 1000) {
				claw_shoot = false;
			}
		}
		if (Health <= 0) {
			anim.set("dead");
			currentFrame += 0.005*time;
			x = x + 1;
			y = y + 2;
			if (currentFrame > 7) { anim.pause(); life = false; }
		}
		anim.flip(dir);
		anim.tick(time);
	}
};
