 #include <iostream>
#include "Level.h"
#include <sstream>
#include <vector>
#include <list>
#include "Player.h"
#include "enemy.h"
#include "view.h"
#include <memory>

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
	easyEnemyImage.createMaskFromColor(sf::Color(255, 255, 255));

	ObjectT player = level.GetObjectT("player");
	ObjectT easyEnemyObject = level.GetObjectT("easyEnemy");

	
	Size playerSize(player.rect.left, player.rect.top, 49, 50);
	Size enemySize(easyEnemyObject.rect.left, easyEnemyObject.rect.top, 50, 45);
	//std::shared_ptr<Player> player1 = std::make_shared<Player>(heroImage, "Player", playerSize, 100, view, &level, 0.5);
	Player player1(heroImage, "Player", playerSize, 100, view, &level, 0.5);
	Enemy easyEnemy(easyEnemyImage, "easyEnemy",enemySize,100, &level,150,0.3);
	std::list<Enemy*> enemyList;
	enemyList.push_back(&easyEnemy);
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
	sf::Text healthText;
	healthText.setFont(textF);
	healthText.setCharacterSize(20);
	healthText.setFillColor(sf::Color::Blue);
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
				player1.update(time,enemyList);
				easyEnemy.update(time,player1);
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
				healthText.setString("Health: " + std::to_string(player1.getHealth()));
				healthText.setPosition(view.getCenter().x + 300, view.getCenter().y - 300);
				level.Draw(window);
				if (easyEnemy.isAlive())
				{
					window.draw(easyEnemy.sprite);
					//easyEnemy.~Enemy();
				}
				window.draw(player1.sprite);
				window.draw(coinText);
				window.draw(healthText);
				if (coins.empty())
				{
					//std::cout << "You win" << std::endl;
					diedText.setString("You win!");
					diedText.setFillColor(sf::Color::Green);
					diedText.setPosition(view.getCenter().x - 75, view.getCenter().y + 20);
					exitText.setFillColor(sf::Color::Green);
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
				else
				{
					window.display();
				}
				
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