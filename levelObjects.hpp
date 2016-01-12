#pragma once
class levelObjects : public Entity
{
public:
	levelObjects(AnimationManager &a, Level &lev, float x, float y, String Name) :Entity(a, x, y)
	{
		option(Name, 0.05, 10, "move");
	}

	void update(float time)
	{
		if (Name == "coin") {	
			anim.tick(time);
		}
		if (Name == "torch") {
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
