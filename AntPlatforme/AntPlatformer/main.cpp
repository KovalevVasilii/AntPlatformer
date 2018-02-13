#include <iostream>
#include "Object.h"
#include "Level.h"
#include <iostream>
#include <sstream>
#include "iostream"
#include "level.h"
#include <vector>
#include <list>


int main()
{
	Level level;
	level.LoadFromFile("mapN.tmx");

	sf::RenderWindow window;
	window.create(sf::VideoMode(1600, 700), "Antplatformer");

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		level.Draw(window);
		window.display();
	}

	return 0;
}