#pragma once

#include "Entity.hpp"
#include <iostream>
#include "Game.hpp"
using namespace std;


class PLAYER : public Entity
{
public:
	enum { stay, run, jump, climb, dead_spike, ends_of_the_earth, sit_down,hit_sword, hit_sword_sit, fall} STATE;
	bool onLadder;
	bool shoot;
	bool hit_on_enemy;
	std::map<std::string, bool> key;

	PLAYER(AnimationManager &a, Level &lev, float x, float y) :Entity(a, x, y)
	{
		option("Player", float(1), 100, "stay"); //имя, = ,жизни, состояние
		STATE = stay; 
		hit_on_enemy = false;
		obj = lev.GetAllObjects();
	}

	void Keyboard()
	{
		if (key["L"] && STATE != dead_spike)
		{
			dir = 1;//поворачиваем спрайт
			if ((STATE != sit_down)) dx = -0.1;
			if (STATE == stay) STATE = run;
		}

		if (key["R"] && STATE != dead_spike)
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
		if (key["jump"] && (dy == 0))
		{

			if (STATE == stay || STATE == run) { dy = -0.35; STATE = jump; anim.play("jump"); }
		}

		if (key["climb_down"])
		{
			if (STATE == stay || STATE == run) { STATE = sit_down; dx = 0; }
			if (STATE == climb) dy = 0.05;
		}
		if (key["l_control"]) {
			shoot = true;
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

		key["R"] = key["L"] = key["jump"] = key["climb_down"] = key["climb_up"] = key["l_control"] = false;
	}
	void Animation(float time) //проход по анимационной xlm
	{
		//Clock cloker;
		//cout << x << "=====" << y;
		if (STATE == stay ) anim.set("stay");
		if (STATE == run) anim.set("run");
		if (STATE == jump) { anim.set("jump"); }
		if (STATE == sit_down) anim.set("sit_down");
		if (STATE == climb) { anim.set("climb"); anim.pause(); if (dy != 0) anim.play(); }
		if (STATE == dead_spike) { 
			timer += time;
			if (timer < 1000) anim.play();
			else anim.pause();
			anim.set("dead_spike"); 
			dy = 0; dx = 0;
			Health = 0; }
		if (STATE == ends_of_the_earth) {
			timer += time;
			if (dir){
			x = x - 0,9999;
			}
			if (timer > 5000) { if (dir) { dx = -2;  timer = 0; STATE = fall; } else { dx = 2;  timer = 0; STATE = fall; } }
			anim.set("ends_of_the_earth");  }
		if (shoot && STATE != dead_spike) {
			dx = 0;
			anim.set("fist_fight");
			timer += time;
			if (timer > 600) { shoot = false; timer = 0; }
			cout << timer << "\n";
			if (STATE == sit_down) {
				if (dir == 1) {  }
				anim.set("hit_sword_down");

			}
			}
		if (hit_on_enemy && STATE!= dead_spike && shoot == false) {
			timer += time;
			if (timer > 1000) { 
				hit_on_enemy = false;
				timer = 0;}
			anim.set("hit_on_enemy");
		}
		if (dy > 0 && STATE != climb && (STATE != dead_spike)) { anim.set("fall");}

		if (dir) anim.flip();//переворачиваем если что)

		anim.tick(time);
	}

	void update(float time)
	{
		Keyboard();

		Animation(time);

		if (STATE == climb) if (!onLadder) STATE = stay;
		if (STATE != climb && STATE != dead_spike) dy += 0.0005*time;
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
				или лучше так 1913 < int(x) < 1920.....
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
				if (obj[i].name == "spikes") {
					STATE = dead_spike;
				}
				if (obj[i].name == "esayEnemy") {
					cout << "hello";
				}

			}
	}

};
