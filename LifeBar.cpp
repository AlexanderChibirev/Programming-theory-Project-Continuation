#include "LifeBar.h"



LifeBar::LifeBar()
{
	image.loadFromFile("images/life.png");
	image.createMaskFromColor(Color(50, 96, 166));
	t.loadFromImage(image);
	s.setTexture(t);
	s.setTextureRect(IntRect(0, 0, 13, 80));

	bar.setFillColor(Color(0, 0, 0));//������ ������������� ������������� ������ � ���������� ������ ���������� ��������
	max = 100;
}


//LifeBar::~LifeBar()
//{
//}

void LifeBar::update(int k)// k-������� ��������

{
	if (k>0)
		if (k<max)
			bar.setSize(Vector2f(float(8), float((max - k) * 75 / max)));//���� �� ������������ � ��� ���� ������ ���������, �� ������������� ����� �������� (����� ������) ��� ������� ��������������
}

void LifeBar::draw(RenderWindow &window)
{
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();

	s.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);//������� �� ������
	bar.setPosition(center.x - size.x / 2 + 14, center.y - size.y / 2 + 14);

	window.draw(s);//������� ������ ������� ��������
	window.draw(bar);//������ �� ��� ������ �������������, �� ��� �� ��������� �
}