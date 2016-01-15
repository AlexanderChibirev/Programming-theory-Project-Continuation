#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "level.h"


using namespace sf;

class Entity
{
public:
    double x;
	double y;
    double dx;
	double dy; 
	double w;
	double h;
	double currentFrame;	
	AnimationManager anim;
	std::vector<Object> obj;
	std::vector<Object> objL;
	std::vector<Object> objR;
	std::vector<Object> objU;
	std::vector<Object> objD;
	bool coinss;
	bool life;
	bool  dir;
	bool clash;
	bool dir_attack;
	bool claw_shoot;
	bool attack_start;
	float timer;
	float timer_end;
	float time_x;
	float time_y;
	std::string Name;
	float Health;

	Entity(AnimationManager &A,float X, float Y)
	{
		anim = A;
		x = X;
		y = Y;
		dir = 0;
		coinss = false;
		attack_start = false;
		claw_shoot = false;
		dir_attack = false;
		clash = false;
		life=true;
		timer=0;
		timer_end=0;
		dx=dy=0;
		
	}

	virtual void update(float time) = 0;

	void draw(RenderWindow &window)
	{
		anim.draw(window,float(x),float(y+h));
	}

	FloatRect getRect()
	{
		return FloatRect(float(x), float(y), float(w), float(h));
	}

	void option(std::string NAME, double SPEED=0, float HEALTH=10, std::string FIRST_ANIM="")
	{
		Name = NAME;
		if (FIRST_ANIM!="") anim.set(FIRST_ANIM);
		w = anim.getW();
		h = anim.getH();
		dx = SPEED;
		Health = HEALTH;
	}

};


