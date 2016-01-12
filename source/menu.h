#pragma once
void menu(RenderWindow & window) {
	Texture menuTexture1;
	Texture menuTexture2;
	Texture menuTexture3;
	Texture aboutTexture;
	Texture menuBackground;
	menuTexture1.loadFromFile("images/newGame.png");
	menuTexture2.loadFromFile("images/aboutProgram.png");
	menuTexture3.loadFromFile("images/exit.png");
	aboutTexture.loadFromFile("images/history.png");
	menuBackground.loadFromFile("images/bg23.png");
	Sprite menu1(menuTexture1);
	Sprite menu2(menuTexture2);
	Sprite menu3(menuTexture3);
	Sprite about(aboutTexture);
	Sprite menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(0, 0);
	menu2.setPosition(0, 100);
	menu3.setPosition(0, 170);
	menuBg.setPosition(0, 0);

	//////////////////////////////����///////////////////
	double CurrentFrame = 0;
	double CurrentFrame2 = 0;
	while (isMenu)
	{
		Clock clock;
		sf::Int64 time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		CurrentFrame += 0.0006*time; //���� 21 �� 0.0008, ���� 6, �� 0.0001
		if (CurrentFrame > 6) CurrentFrame -= 6; // ���� 21 ���� 6
		menuBg.setTextureRect(IntRect(750* int(CurrentFrame), 0, 750,750)); //
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(0, 0, 350, 95).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Yellow); menuNum = 1; }//������ ����
		if (IntRect(0, 100, 285, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Yellow); menuNum = 2; }//� ���������
		if (IntRect(0, 170, 144, 40).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Yellow); menuNum = 3; }//����� �� ����

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//���� ������ ������ ������, �� ������� �� ���� 
			if (menuNum == 2) { 
				window.draw(about);
				window.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	////////////////////////////////////////////////////
}