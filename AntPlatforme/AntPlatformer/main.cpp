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
#include "startGameh.h"
#include "menu.h"
#include <SFML/Audio.hpp>
#include "Generator.h"

void gameRun(sf::RenderWindow& window)
{
	if (startGame(window))
	{
		window.clear();
		gameRun(window);
	}
}
int main()
{
	sf::Music life;
	life.openFromFile("life.wav");
	life.setLoop(true);
	//life.play();
	life.setVolume(30);
	sf::RenderWindow window(sf::VideoMode(1600, 720), "Antplatformer");
	Generator hh(1600, 720);
	hh.generate()->Draw(window);
	window.display();
	menu(window);
	if (window.isOpen())
	{
		gameRun(window);
	}
	//life.stop();
	std::cin.get();
}