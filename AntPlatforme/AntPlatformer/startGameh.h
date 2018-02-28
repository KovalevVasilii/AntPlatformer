#pragma once
#include <iostream>
#include "Level.h"
#include <sstream>
#include <vector>
#include <list>
#include "Player.h"
#include "enemy.h"
#include "view.h"
#include <memory>
#include "Ability.h"
#include "menu.h"
bool startGame(sf::RenderWindow& window)
{
	sf::SoundBuffer buffer;
	buffer.loadFromFile("music/weapon.wav");
	sf::Sound sound;
	sound.setBuffer(buffer);

	static int numberOfLevel = 1;
	bool flag = true;
	Level level;
	if (numberOfLevel == 1)
	{
		level.LoadFromFile("map.tmx");
	}
	else
	{
		level.LoadFromFile("map2.tmx");
		//bool flag = true;
	}



	sf::Image heroImage;
	heroImage.loadFromFile("images/hero_aprite.gif");
	heroImage.createMaskFromColor(sf::Color(0, 128, 0));

	sf::Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/enemy_sprite.png");
	easyEnemyImage.createMaskFromColor(sf::Color(255, 255, 255));

	sf::Image weaponIm;

	ObjectT* player = level.GetObjectT("player");
	std::vector<ObjectT*> easyEnemyObject = level.GetObjectTs("easyEnemy");
	std::vector<Enemy> enemyList;

	

	ObjectT* ob = level.GetObjectT("easyEnemy");
	Size enemySize(ob->rect.left, ob->rect.top, 50, 45);
	Enemy obb(&easyEnemyImage, "easyEnemy", enemySize, 100, &level, 150, 0.3, ob,&sound);;

	Size playerSize(player->rect.left, player->rect.top, 49, 50);
	for (auto it : easyEnemyObject)
	{
		enemyList.push_back(obb);
	}

	int i = 0;
	for (auto it : easyEnemyObject)
	{
		Size enemySize(it->rect.left, it->rect.top, 50, 45);
		enemyList[i].size = enemySize;
		i++;
	}

	Player player1(&heroImage, "Player", playerSize, 100, view, 30,  &level, 0.5, player, &weaponIm);

	sf::Texture coinT;
	coinT.loadFromFile("images/coin.png");
	



	sf::Font textF;
	textF.loadFromFile("lobster.ttf");
	sf::Text coinText;
	coinText.setFont(textF);
	coinText.setCharacterSize(20);
	coinText.setFillColor(sf::Color::Blue);

	sf::Text information;
	information.setFont(textF);
	information.setCharacterSize(20);
	information.setFillColor(sf::Color::Blue);

	//coinText.setPosition(window.getSize().x - 150,40);
	sf::Text diedText("You died", textF, 90);
	diedText.setFillColor(sf::Color::Red);
	sf::Text exitText("(press Escape to exit or Tab to restart)", textF, 30);
	exitText.setFillColor(sf::Color::Red);
	sf::Text healthText;
	healthText.setFont(textF);
	healthText.setCharacterSize(20);
	healthText.setFillColor(sf::Color::Blue);
	sf::Clock clock;


	sf::Texture abilityT;
	abilityT.loadFromFile("ability.png");
	std::vector<Ability*> abilities;
	std::vector<ObjectT*> abilitiesObj = level.GetObjectTs("ability");

	for (auto it : abilitiesObj)
	{


		abilities.push_back(new Ability(abilityT, it->rect.left, it->rect.top));
		//std::cout << it->getRect().left <<" : "<< it->getRect().top << std::endl;
		//std::cout << it->to_String() << std::endl;
	}

	float CurrentFrame = 0;
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
					return false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) { return true; }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { return false; }
			if (player1.isAlive())
			{
				player1.update(time, enemyList, abilities);
				for (auto easyEnemy = enemyList.begin(); easyEnemy != enemyList.end(); easyEnemy++)
				{
					easyEnemy->update(time, player1);
				}
				window.setView(view);
				window.clear(sf::Color(65, 170, 255));
				std::vector<sf::Sprite> coins;
				std::vector<ObjectT*> coinsObj = level.GetObjectTs("coin");
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 10) CurrentFrame -= 10;
				for (auto it = coinsObj.begin(); it != coinsObj.end(); it++)
				{
					sf::Sprite coin;
					coin.setTexture(coinT);
					coin.setTextureRect(sf::IntRect(100 * int(CurrentFrame), 0, 100, 100));
					coin.setScale(0.3, 0.3);
					coin.setPosition((*it)->rect.left, (*it)->rect.top);
					coins.push_back(coin);
					window.draw(coin);
				}
				//std::cout << abilities.size() << std::endl;
				for (int i = 0; i<abilities.size(); i++)
				{
					if (abilities[i]->flagExist)
					{
						//abilities[i]->draw(&window);
						//easyEnemy.~Enemy();
						sf::Sprite AB;
						AB.setTexture(abilityT);
						AB.setPosition(abilities[i]->getRect().left, abilities[i]->getRect().top);
						AB.setScale(0.5, 0.5);
						window.draw(AB);
						//std::cout << abilities[i]->getRect().left << " : " << abilities[i]->getRect().top << std::endl;
						//window.draw(abilities[i]->getSprite());

					}
					else
					{
						std::swap(abilities[i], abilities[abilities.size() - 1]);
						abilities.pop_back();
						i--;
					}
				}
				information.setString(player1.getInformation());
				

				coinText.setString("Coins: " + std::to_string(player1.getCoin()));
				coinText.setPosition(view.getCenter().x + 300, view.getCenter().y - 350);
				healthText.setString("Health: " + std::to_string(player1.getHealth()));
				healthText.setPosition(view.getCenter().x + 300, view.getCenter().y - 325);
				information.setPosition(view.getCenter().x + 300, view.getCenter().y - 300);
				
				level.Draw(window);
				for (int i = 0; i<enemyList.size(); i++)
				{
					if (enemyList[i].isAlive())
					{
						enemyList[i].draw(&window);
						//easyEnemy.~Enemy();
					}
					else
					{
						std::swap(enemyList[i], enemyList[enemyList.size() - 1]);
						enemyList.pop_back();
						i--;
					}
				}
				//window.draw(player1.sprite);
				player1.draw(&window);
				window.draw(coinText);
				window.draw(healthText);
				window.draw(information);
				if (coins.empty())
				{
					//std::cout << "You win" << std::endl;
					diedText.setString("You win!");
					diedText.setFillColor(sf::Color::Green);
					diedText.setPosition(view.getCenter().x - 75, view.getCenter().y + 20);
					exitText.setString("(press Escape to exit or Tab to continue)");
					exitText.setFillColor(sf::Color::Green);
					exitText.setPosition(view.getCenter().x - 50, view.getCenter().y + 120);
					numberOfLevel = 2;
					window.draw(diedText);
					window.draw(exitText);
					if (flag == true)
					{
						flag = false;
						window.display();
						player1.setHealth();
					}
					
				}
				else
				{
					window.display();
				}

			}
			else
			{
				diedText.setPosition(view.getCenter().x - 75, view.getCenter().y + 20);
				exitText.setPosition(view.getCenter().x - 50, view.getCenter().y + 120);
				window.draw(diedText);
				window.draw(exitText);
				if (flag == true)
				{
					flag = false;
					window.display();
				}
			}


		}
	}
	catch (...)
	{
		std::cout << "WARNING" << std::endl;
	}

}