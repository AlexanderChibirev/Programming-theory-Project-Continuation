#pragma once

#include "Entity.hpp"


class ENEMY: public Entity
{
public:

	ENEMY(AnimationManager &a,Level &lev,float x,float y):Entity(a,x,y)
	{
		//option("Player", float(1), 100, "stay");
		option("easyEnemy", float(0.06), 10, "run");
	}

	void update(float time)
	{ //dir 1 � ���� ������� 0  ���������
		if (dir_attack == false){
			timer += time;
		}
		
		if (timer > 4000 && (dir_attack == false))
		{
			x += dx*time;
			dx *= -1;
			dir = !dir;
			timer = 0;
		}
		if (attack_straight == true) { anim.set("attack");
		dx = 0; 
		attack_straight = false;
		dir_attack = true;
		}
		if (Health <= 0) {
			anim.set("dead");
			currentFrame += 0.005*time;
			if (currentFrame > 7) { anim.pause(); life = false; }
		}
		anim.flip(dir);
		anim.tick(time);
	}
};
