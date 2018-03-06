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
	life.openFromFile("music/life.wav");
	life.setLoop(true);
	//life.play();
	
	sf::RenderWindow window(sf::VideoMode(1600, 700), "Antplatformer");
	menu(window);
	if (window.isOpen())
	{
		gameRun(window);
	}
	life.stop();
}