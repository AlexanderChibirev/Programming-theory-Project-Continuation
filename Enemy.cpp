//#include "Enemy.hpp"
//
//ENEMY::ENEMY(AnimationManager &a, Level &lev, float x, float y) :Entity(a, x, y)
//{
//	//option("player", float(1), 100, "stay");
//	option("easyenemy", float(0.06), 10, "run");
//}
//
//void ENEMY::update(float time)
//{ //dir 1 в норм сторону 0  зеркально
//	if (dir_attack == false) {
//		timer += time;
//	}
//
//	if (timer > 4000 && (dir_attack == false))
//	{
//		x += dx*time;
//		dx *= -1;
//		dir = !dir;
//		timer = 0;
//	}
//	if (attack_start == true) {
//		anim.set("attack");
//		dx = 0;
//		attack_start = false;
//		dir_attack = true;
//	}
//	if (Health <= 0) {
//		anim.set("dead");
//		currentFrame += 0.005*time;
//		if (currentFrame > 7) { anim.pause(); life = false; }
//	}
//	anim.flip(dir);
//	anim.tick(time);
//}