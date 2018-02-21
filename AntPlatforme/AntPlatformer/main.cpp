#include <iostream>
#include "Level.h"
#include <sstream>
#include <vector>
#include <list>
#include "Player.h"
#include "enemy.h"
#include "view.h"

int main()
{
	Level level;
	level.LoadFromFile("map.tmx");

	sf::RenderWindow window;
	window.create(sf::VideoMode(1600, 700), "Antplatformer");

	sf::Image heroImage;
	heroImage.loadFromFile("images/hero_aprite.gif");
	heroImage.createMaskFromColor(sf::Color(0, 128, 0));

	sf::Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/enemy_sprite.png");

	ObjectT player = level.GetObjectT("player");
	ObjectT easyEnemyObject = level.GetObjectT("easyEnemy");

	Size playerSize(player.rect.left, player.rect.top, 49, 50);
	Size enemySize(easyEnemyObject.rect.left, easyEnemyObject.rect.top, 50, 65);
	Player player1(heroImage, "Player", playerSize,100,view, &level);
	Enemy easyEnemy(easyEnemyImage, "easyEnemy",enemySize,100, &level);

	sf::Texture coinT;
	coinT.loadFromFile("coin.png");
	
	sf::Font textF;
	textF.loadFromFile("lobster.ttf");
	sf::Text coinText;
	coinText.setFont(textF);
	coinText.setCharacterSize(20);
	coinText.setFillColor(sf::Color::Blue);
	//coinText.setPosition(window.getSize().x - 150,40);
	sf::Text diedText("You died", textF, 90);
	diedText.setFillColor(sf::Color::Red);
	sf::Text exitText("(press space to exit)", textF, 30);
	exitText.setFillColor(sf::Color::Red);
	sf::Clock clock;
	try {
		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asMicroseconds();

			clock.restart();
			time = time / 800;
			sf::Event event;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					//window.close();
					exit(0);
			}
			if (player1.isAlive())
			{
				player1.update(time);
				easyEnemy.update(time);
				window.setView(view);
				window.clear(sf::Color::White);
				std::vector<sf::Sprite> coins;
				std::vector<ObjectT> coinsObj = level.GetObjectTs("coin");
				for (auto it = coinsObj.begin(); it != coinsObj.end(); it++)
				{
					sf::Sprite coin;
					coin.setTexture(coinT);
					coin.setPosition(it->rect.left, it->rect.top);
					coins.push_back(coin);
					window.draw(coin);
				}
				coinText.setString("Coins: " + std::to_string(player1.getCoin()));
				coinText.setPosition(view.getCenter().x+300, view.getCenter().y-350);
				level.Draw(window);
				window.draw(easyEnemy.sprite);
				window.draw(player1.sprite);
				window.draw(coinText);
				window.display();
			}
			else
			{
				diedText.setPosition(view.getCenter().x-75, view.getCenter().y+20);
				exitText.setPosition(view.getCenter().x - 50, view.getCenter().y + 120);
				window.draw(diedText);
				window.draw(exitText);
				bool static flag = true;
				if (flag == true)
				{
					flag = false;
					window.display();
				}
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					exit(0);
				}
			}
			

		}
	}
	catch (...)
	{
		std::cout << "WARNING" << std::endl;
	}

	return 0;
}