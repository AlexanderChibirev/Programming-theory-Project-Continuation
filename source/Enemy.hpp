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
	{ //dir 1 в норм сторону 0 нет
		x += dx*time;
		timer += time;
		if (dir_attack == false){
		anim.flip(dir);
		}
		if (timer > 4000 && (dir_attack == false))
		{
			dx *= -1;
			dir = !dir;
			timer = 0;
		}
		if (attack_straight == true) { anim.set("attack");
		cout << dir << "\n";
		dx = 0; 
		attack_straight = false;
		dir_attack = true;
		if (dir == 1) {	dir = 0; anim.flip(dir);}
		else { dir = 1; anim.flip(dir); }
		}
		if (Health <= 0) {
			anim.set("dead");
			currentFrame += 0.005*time;
			if (currentFrame > 7) { anim.pause(); life = false; }
		}
		anim.tick(time);
	}
};
