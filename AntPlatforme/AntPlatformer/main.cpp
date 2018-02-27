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


void gameRun(sf::RenderWindow& window)
{
	if (startGame(window))
	{
		gameRun(window);
	}
}
int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 700), "Antplatformer");
	menu(window);
	if (window.isOpen())
	{
		gameRun(window);
	}
}