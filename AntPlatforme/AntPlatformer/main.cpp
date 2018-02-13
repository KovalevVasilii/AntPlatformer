#include <iostream>
#include "Level.h"
#include <sstream>
#include <vector>
#include <list>
#include "Player.h"
#include "enemy.h"

sf::View view;

int main()
{
	Level level;
	level.LoadFromFile("mapN.tmx");

	sf::RenderWindow window;
	window.create(sf::VideoMode(1600, 700), "Antplatformer");

	sf::Image heroImage;
	heroImage.loadFromFile("images/hero_sprite.png");

	sf::Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/enemy_sprite.png");
	easyEnemyImage.createMaskFromColor(sf::Color(255, 0, 0));

	ObjectT player = level.GetObjectT("player");
	ObjectT easyEnemyObject = level.GetObjectT("easyEnemy");

	Size playerSize(player.rect.left, player.rect.top, 150, 210);
	Size enemySize(easyEnemyObject.rect.left, easyEnemyObject.rect.top, 200, 97);
	Player player1(heroImage, "Player", playerSize,100,level,view);
	Enemy easyEnemy(easyEnemyImage, "Enemy",enemySize,100, level);

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
					window.close();
			}
			player1.update(time);
			easyEnemy.update(time);
			window.setView(view);
			window.clear(sf::Color::White);
			level.Draw(window);
			//window.draw(easyEnemy.sprite);
			window.draw(player1.sprite);
			window.display();
		}
	}
	catch (...)
	{
		std::cout << "WARNING" << std::endl;
	}

	return 0;
}