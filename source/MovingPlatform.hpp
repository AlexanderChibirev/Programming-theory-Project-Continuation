#pragma once
class MovingPlatform: public Entity
{
public:
	MovingPlatform(AnimationManager &a, Level &lev,float x,float y,String Name):Entity(a,x,y)
	{
		option(Name, 0.05, 0, "move");
	}

	void update(float time)
	{
		
		
		if(Name == "movingPlatformX"){
			
		x += dx * time;
		time_x += time;
		if (time_x >16000) {dx *= -1; time_x = 0;}
		anim.tick(time);
		}
		else
		{
			y+= dx * time;
			time_y += time;	
			if (time_y  > 1000) { dx *= -1; time_y = 0; }
			anim.tick(time);
		}
	}

};
