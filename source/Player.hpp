#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"
#include <iostream>
using namespace std;


class PLAYER : public Entity
{
public:
	enum { stay, run, jump, climb, swim, dead_spike, ends_of_the_earth, sit_down } STATE;
	bool onLadder, shoot;
	std::map<std::string, bool> key;

	PLAYER(AnimationManager &a, Level &lev, int x, int y) :Entity(a, x, y)
	{
		option("Player", 10, 100, "stay"); //имя, = ,жизни, состояние
		STATE = stay;
		obj = lev.GetAllObjects();
	}

	void Keyboard()
	{
		if (key["L"])
		{
			dir = 1;//поворачиваем спрайт
			if (STATE != sit_down) dx = -0.1;
			if (STATE == stay) STATE = run;
		}

		if (key["R"])
		{
			dir = 0;
			if (STATE != sit_down) dx = 0.1;
			if (STATE == stay) STATE = run;

		}
		//
		if (key["L"] && key["jump"]) {
			if ((STATE == climb) && (dy == 0)) {
				STATE = run;
				anim.set("jump");
			}

		}
		if (key["R"] && key["jump"]) {
			if ((STATE == climb) && (dy == 0)) {
				STATE = run;
				anim.set("jump");
			}

		}
		if (key["climb_up"]) {
			if (onLadder) STATE = climb;
			if (STATE == climb) dy = -0.05;
		}
		if (key["jump"])
		{

			if (STATE == stay || STATE == run) { dy = -0.35; STATE = jump; anim.play("jump"); }
		}

		if (key["climb_down"])
		{
			if (STATE == stay || STATE == run) { STATE = sit_down; dx = 0; }
			if (STATE == climb) dy = 0.05;
		}


		/////////////////////если клавиша отпущена///////////////////////////
		if (!(key["R"] || key["L"]))
		{
			dx = 0;
			if (STATE == run) STATE = stay;
		}


		if (!(key["climb_up"] || key["climb_down"]))
		{
			if (STATE == climb) dy = 0;
		}

		key["R"] = key["L"] = key["jump"] = key["climb_down"] = key["climb_up"] = false;
	}

	void Animation(float time) //проход по анимационной xlm
	{
		if (STATE == stay) anim.set("stay");
		if (STATE == run) anim.set("run");
		if (STATE == jump) anim.set("jump");
		if (STATE == sit_down) anim.set("sit_down");
		if (STATE == climb) { anim.set("climb"); anim.pause(); if (dy != 0) anim.play(); }
		if (STATE == ends_of_the_earth) anim.set("ends_of_the_earth");
		if (dir) anim.flip();
		anim.tick(time);
	}

	void update(float time)
	{
		Keyboard();

		Animation(time);

		if (STATE == climb) if (!onLadder) STATE = stay;
		if (STATE != climb) dy += 0.0005*time;
		onLadder = false;

		x += dx*time;
		Collision(0);

		y += dy*time;
		Collision(1);
	}

	void Collision(int num)
	{
		for (int i = 0; i < obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "solid")
				{
					if (dy > 0 && num == 1) { y = obj[i].rect.top - h;  dy = 0;   STATE = stay; }
					if (dy < 0 && num == 1) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (dx > 0 && num == 0) { x = obj[i].rect.left - w; }
					if (dx < 0 && num == 0) { x = obj[i].rect.left + obj[i].rect.width; }
				}

				if (obj[i].name == "ladder") {
					onLadder = true;
					if (STATE == climb) x = obj[i].rect.left - 10;
				}
				/*if ((int(x) == 1920)||(int(x) == 1919)||(int(x) == 1918) || (int(x) == 1917)|| (int(x) == 1916)|| (int(x) == 1915)|| (int(x) == 1914)|| (int(x) == 1913)) {
				cout<<int(x);
				STATE = ends_of_the_earth;
				}*/
				if (obj[i].name == "ends_of_the_earth_r" && (dx == 0) && (dy == 0) && (dir != 1)) {

					STATE = ends_of_the_earth;
				}
				if (obj[i].name == "ends_of_the_earth_l" && (dx == 0) && (dy == 0)) {
					STATE = ends_of_the_earth;
					dir = 1;
					//x = obj[i].rect.left - 10;
				}

			}
	}

};


#endif PLAYER_H
