#pragma once
#include "SFML\Graphics.hpp"
void menu(sf::RenderWindow & window) {
	sf::Texture menuTexture1, menuTexture3,menuBackground;
	menuTexture1.loadFromFile("images/firstNum.png");
	menuTexture3.loadFromFile("images/thirdNum.png");
	menuBackground.loadFromFile("images/menuBG.png");
	sf::Sprite menu1(menuTexture1), menu3(menuTexture3),menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu3.setPosition(100, 90);
	menuBg.setPosition(345, 0);

	while (isMenu)
	{
		menu1.setColor(sf::Color::White);
		menu3.setColor(sf::Color::White);
		menuNum = 0;
		window.clear(sf::Color(128, 128, 128));

		if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window))) { menu1.setColor(sf::Color::Blue); menuNum = 1; }
		if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) { menu3.setColor(sf::Color::Blue); menuNum = 3; }

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu3);

		window.display();
	}
}