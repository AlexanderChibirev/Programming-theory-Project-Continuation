#pragma once
class MovingPlatform: public Entity
{
public:
	MovingPlatform(AnimationManager &a, Level &lev,float x,float y,String Name):Entity(a,x,y)
	{
	//	Level lvl;
	//	lvl.LoadFromFile("files/Level1.tmx");
	//	objR = lvl.GetObjects("solidR");
	//	objL = lvl.GetObjects("solidL");
		option(Name, 0.05, 0, "move");
	}

	void update(float time)
	{	
		if(Name == "movingPlatformX"){
			x += dx * time;
			//for (int i = 0; i<objR.size(); i++)//���������� �� ��������
			//	if (getRect().intersects(objR[i].rect))//��������� ����������� ������ � ��������
			//	{
			//		if (objR[i].name == "solidR")//���� ��������� �����������
			//		{
			//			cout << dx << "solidR";
			//			x += dx * time; dx *= -1;
			//		}
			//	}
			//x += dx * time;
			//for (int i = 0; i<objL.size(); i++)//���������� �� ��������
			//	if (getRect().intersects(objL[i].rect))//��������� ����������� ������ � ��������
			//	{
			//		if (objL[i].name == "solidL")//���� ��������� �����������
			//		{
			//			cout << dx ;
			//			x += dx * time; dx *= -1;
			//		}
			//	}
		x += dx * time;
		time_x += time;
		if (time_x >6000) {dx *= -1; time_x = 0;}
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
