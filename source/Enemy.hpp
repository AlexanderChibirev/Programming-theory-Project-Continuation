#pragma once
#include "Entity.hpp"


class ENEMY: public Entity
{
public:

	ENEMY(AnimationManager &a,Level &lev,float x,float y):Entity(a,x,y)
	{
		//option("Player", float(1), 100, "stay");
		option("easyEnemy", float(0.08), 10, "run");
	}

	void update(float time)
	{ //dir 1 в норм сторону 0  зеркально
		timer += time;
		if (timer > 4000 && (dir_attack == false))
		{
			x += dx*time;
			dx *= -1;
			dir = !dir;
			timer = 0;
		}
		if (attack_start == true) {
			anim.set("attack");
			attack_start = false;
			dir_attack = true;
		}
		if (Health > 0 && claw_shoot == true) { 
			anim.set("hit_on_hero");
			timer += time; 
			if (timer > 1000) {
				//anim.set("attack");
				claw_shoot = false;
			}
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
