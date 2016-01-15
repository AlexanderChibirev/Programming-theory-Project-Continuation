#pragma once


class MovingPlatform : public Entity
{
public:
	MovingPlatform(AnimationManager &a, Level &lev, float x, float y, String Name) :Entity(a, x, y)
	{
		Level lvl;
		lvl.LoadFromFile("files/Level1.tmx");
		objR = lvl.GetObjects("solidR");
		objL = lvl.GetObjects("solidL");
		objU = lvl.GetObjects("solidU");
		objD = lvl.GetObjects("solidD");
		option(Name, 0.07, 0, "move");
	}

	void update(float time)
	{
		if (Name == "movingPlatformX") {
			x += dx * time;
			for (int i = 0; i<objR.size(); i++)//проходимс€ по объектам
				if (getRect().intersects(objR[i].rect))//провер€ем пересечение игрока с объектом
				{
					if (objR[i].name == "solidR")//если встретили преп€тствие
					{
						dx *= -1;
						x = x - 5;
					}
				}
			for (int i = 0; i<objL.size(); i++)//проходимс€ по объектам
				if (getRect().intersects(objL[i].rect))//провер€ем пересечение игрока с объектом
				{
					if (objL[i].name == "solidL")//если встретили преп€тствие
					{
						dx *= -1;
						x = x + 5;
					}
				}
			anim.tick(time);
		}
		else
		{
			cout << "zashlo" << endl;
			y += dx * time;
			for (int i = 0; i<objU.size(); i++)//проходимс€ по объектам
				if (getRect().intersects(objU[i].rect))//провер€ем пересечение игрока с объектом
				{
					if (objU[i].name == "solidU")//если встретили преп€тствие //если верхн€€ граница
					{
						y = y + 5;
						dx *= -1;				
					}
				}
			for (int i = 0; i<objD.size(); i++)//проходимс€ по объектам
				if (getRect().intersects(objD[i].rect))//провер€ем пересечение игрока с объектом
				{
					if (objD[i].name == "solidD")//если встретили преп€тствие //если нижн€€ граница
					{
						y = y - 5;
						dx *= -1;	
					}
				}
			anim.tick(time);
		}
	}

};
