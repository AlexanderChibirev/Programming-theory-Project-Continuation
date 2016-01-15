//#include "Bullet.h"
//
//
//Bullet::Bullet(AnimationManager a, int X, int Y, bool dir) :Entity(a, x, y)
//{
//	anim = a;
//	anim.set("move");
//	x = X;
//	y = Y;
//	dx = 0.3;
//	if (dir == 1) dx = -0.3;
//	w = h = 18;
//	life = true;
//}
//
//void Bullet::update(float time)
//{
//	x += dx*time;
//	
//	anim.tick(time);
//}
//void Bullet::draw(RenderWindow &window)
//{
//	anim.draw(window, x, y);
//}
////Bullet::~Bullet()
////{
////}
