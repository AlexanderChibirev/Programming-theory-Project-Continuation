//#include "MovingPlatform.h"
//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <list>
//#include "level.hpp"
//#include "Animation.hpp"
//#include "Entity.hpp"
//#include "Player.hpp"
//#include "Enemy.hpp"
//#include "MovingPlatform.h"
//#include "levelObjects.hpp"
//
//
//MovingPlatform::MovingPlatform(AnimationManager &a, Level &lev, float x, float y, String Name):Entity(a, x, y)
//{
//	option(Name, 0.05, 0, "move");
//}
//void  MovingPlatform::update(float time)
//{
//	if (Name == "movingPlatformX") {
//		x += dx * time;
//		x += dx * time;
//		time_x += time;
//		if (time_x >6000) { dx *= -1; time_x = 0; }
//		anim.tick(time);
//	}
//	else
//	{
//		y += dx * time;
//		time_y += time;
//		if (time_y  > 1000) { dx *= -1; time_y = 0; }
//		anim.tick(time);
//	}
//}
//
////MovingPlatform::~MovingPlatform()
////{
////}
