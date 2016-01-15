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
			for (int i = 0; i<objR.size(); i++)//���������� �� ��������
				if (getRect().intersects(objR[i].rect))//��������� ����������� ������ � ��������
				{
					if (objR[i].name == "solidR")//���� ��������� �����������
					{
						dx *= -1;
						x = x - 5;
					}
				}
			for (int i = 0; i<objL.size(); i++)//���������� �� ��������
				if (getRect().intersects(objL[i].rect))//��������� ����������� ������ � ��������
				{
					if (objL[i].name == "solidL")//���� ��������� �����������
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
			for (int i = 0; i<objU.size(); i++)//���������� �� ��������
				if (getRect().intersects(objU[i].rect))//��������� ����������� ������ � ��������
				{
					if (objU[i].name == "solidU")//���� ��������� ����������� //���� ������� �������
					{
						y = y + 5;
						dx *= -1;				
					}
				}
			for (int i = 0; i<objD.size(); i++)//���������� �� ��������
				if (getRect().intersects(objD[i].rect))//��������� ����������� ������ � ��������
				{
					if (objD[i].name == "solidD")//���� ��������� ����������� //���� ������ �������
					{
						y = y - 5;
						dx *= -1;	
					}
				}
			anim.tick(time);
		}
	}

};
