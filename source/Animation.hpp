#pragma once
#include "TinyXML/tinyxml.h"
#include <SFML/Graphics.hpp>


using namespace sf;

class Animation
{
public:
	std::vector<IntRect> frames, frames_flip;
	float currentFrame;
	float speed;
	bool loop;
	bool flip;
	bool isPlaying;   // loop показвает зациклена ли анимация. Например анимация взрыва должна проиграться один раз и остановиться, loop=false
	Sprite sprite;

	Animation()
	{
		currentFrame = 0;
		isPlaying=true;
		flip=false;
		loop=true;
	}

	void tick(float time)
	{
		if (!isPlaying) return;

		currentFrame += speed * time;

		if (currentFrame > frames.size()) { currentFrame -= frames.size();
		                                    if (!loop) {isPlaying=false; return;}
		                                  }

		int i = int(currentFrame);
		sprite.setTextureRect( frames[i] );
		if (flip) sprite.setTextureRect( frames_flip[i] );
	}

};



class AnimationManager
{

public:
    std::string currentAnim;
	std::map<std::string, Animation> animList;

	AnimationManager()
	{}

	~AnimationManager()
	{ animList.clear();
	}

   //создание анимаций вручную
	void create(std::string name, Texture &texture, int x, int y, int w, float h, int count, double speed, int step=0, bool Loop=true)//имя,
	{
		Animation a;
		a.speed = float(speed);
		a.loop = Loop;
		a.sprite.setTexture(texture);
		a.sprite.setOrigin(20,h);

		for (int i=0;i<count;i++)
		{
			a.frames.push_back( IntRect(x+i*step, y, w, int(h))  );//х *количество спрайтов, у, ширина, высота
			a.frames_flip.push_back( IntRect(x+i*step+w, y, -w, int(h))  );//обратное отображение
		}
		animList[name] = a;
		currentAnim = name;
	}

	//загрузка из файла XML
	void loadFromXML(std::string fileName,Texture &t)
	{
		TiXmlDocument animFile(fileName.c_str());

		animFile.LoadFile();

		TiXmlElement *head;
		head = animFile.FirstChildElement("sprites");

		TiXmlElement *animElement;
		animElement = head->FirstChildElement("animation");
		while(animElement)
		{
			Animation anim;
			currentAnim = animElement->Attribute("title");
			int delay = atoi(animElement->Attribute("delay"));
			anim.speed = float(1.0/delay); anim.sprite.setTexture(t);

			TiXmlElement *cut;
			cut = animElement->FirstChildElement("cut");
			while (cut)
			{
				int x = atoi(cut->Attribute("x"));
				int y = atoi(cut->Attribute("y"));
				int w = atoi(cut->Attribute("w"));
				int h = atoi(cut->Attribute("h"));

				anim.frames.push_back( IntRect(x,y,w,h) );
				anim.frames_flip.push_back( IntRect(x+w,y,-w,h)  );
				cut = cut->NextSiblingElement("cut");
			}
			//если изображение "сидеть" зеркальное, то мы ставим на х = *anim.frames[0].width*, для нормального
			//если просто, то х = *0*
			anim.sprite.setOrigin(0,float(anim.frames[0].height));

			animList[currentAnim] = anim;
			animElement = animElement->NextSiblingElement("animation");
		}
	}
	
	void set(std::string name)
	{
		currentAnim = name;
		animList[currentAnim].flip=0;
	}

	void draw(RenderWindow &window, float x=0, float y=0)// смещаем координаты
	{
		animList[currentAnim].sprite.setPosition(x,y);
		window.draw( animList[currentAnim].sprite );
	}

	void flip(bool b=1) {animList[currentAnim].flip = b;}

	void tick(float time)	 {animList[currentAnim].tick(time);}

	void pause() {animList[currentAnim].isPlaying=false;}

	void play()  {animList[currentAnim].isPlaying=true;}

	void play(std::string name)  {animList[name].isPlaying=true;}

	bool isPlaying()  {return animList[currentAnim].isPlaying;}

	int getH()  {return animList[currentAnim].frames[0].height;}

	int getW() {return animList[currentAnim].frames[0].width;}
	//////////////////////////////////////
};

#pragma once
