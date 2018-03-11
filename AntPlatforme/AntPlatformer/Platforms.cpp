#include "Platforms.h"



Platforms::Platforms()
{
	plat1 = new sf::Texture;
	plat2 = new sf::Texture;
	plat3 = new sf::Texture;
	plat1->loadFromFile("images\\plat1.png");
	plat2->loadFromFile("images\\plat2.png");
	plat3->loadFromFile("images\\plat3.png");
	plant1 = new sf::Texture;
	plant2 = new sf::Texture;
	plant3 = new sf::Texture;
	plant1->loadFromFile("images\\plant1.png");
	plant2->loadFromFile("images\\plant2.png");
	plant3->loadFromFile("images\\plant3.png");
}


Platforms::~Platforms()
{
}
