#pragma once
#include "Entity.h"


class EnemyMouse : public Entity
{
public:

	EnemyMouse(AnimationManager &a, Level &lev, float x, float y) :Entity(a, x, y)
	{
		option("mouse", 0.01, 15, "stay");
	}

	void update(float time)
	{
		//x += dx*time;
		timer += time;
		/*cout << Entity::place << ".h MOUSE"<< endl;*/
		//if (*place == true) { anim.set("attack");  timer = 0;}
		//if (timer < 3200) { anim.set("stay"); }

		/*if (Health <= 0) {
			anim.set("dead"); dx = 0;
			timer_end += time;
			if (timer_end>4000) life = false;
		}*/

		anim.tick(time);
	}
};
