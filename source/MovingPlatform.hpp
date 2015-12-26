class MovingPlatform: public Entity
{
public:
	MovingPlatform(AnimationManager &a, Level &lev,int x,int y,String Name):Entity(a,x,y)
	{
		option(Name, 0.05, 0, "move");
	}

	void update(float time)
	{
		if(Name == "movingPlatformX"){
		x += dx * time;
		timer+=time;
		if (timer>6000) {dx*=-1;timer=0;}
		anim.tick(time);
		}
		else
			y += dx * time;
			timer += time;
			if (timer>6000) { dx *= -1; timer = 0; }
			anim.tick(time);
	}

};
