#pragma once
#include "Game.h"
class levelObjects : public Entity
{
public:
	levelObjects(AnimationManager &a, Level &lev, float x, float y, String Name) :Entity(a, x, y)
	{
		option(Name, 0.05, 10, "move");
	}

	void update(float time)
	{
		if (Name == "coin"|| Name == "coin1" || Name == "coin2"||Name == "coin3") {
			anim.tick(time);
			if (life == false){
				x = x - 5;
				y = y - 5;
			}
		}
		if (Name == "movingPlatformUp" || Name == "torch") {
			anim.tick(time);
		}
		if (Name == "torch_window") {
			anim.set("move_window");
			anim.tick(time);
		}
		if (Name == "chain") {
			anim.set("move_chain");
			anim.tick(time);
		}
		if (Name == "dungeon") {
			anim.set("move_dungeon");
			anim.tick(time);
		}
	}

};
