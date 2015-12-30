#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.hpp"


class ENEMY: public Entity
{
public:

	ENEMY(AnimationManager &a,Level &lev,float x,float y):Entity(a,x,y)
	{
		//option("Player", float(1), 100, "stay");
		option("easyEnemy", float(0.02), 10, "run");
	}

	void update(float time)
	{ //dir 1 в норм сторону 0 нет
		x+=dx*time;
		timer+=time;
		anim.flip(dir);
		if (timer > 7000)
		{
			cout << "h";
			dx *= -1;
			dir = !dir;
			timer = 0;
		}
		//if (Health <= 0) { CurrentFrame += 0.005*time; anim.set("dead"); }
		anim.tick(time);
	}
};

#endif ENEMY_H
