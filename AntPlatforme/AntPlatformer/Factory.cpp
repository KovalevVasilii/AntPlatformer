#include "Factory.h"
#include <random>

std::string Factory::to_String()
{
	std::string text;
	switch (typeOfObject)
	{
	case 0:
		text = "Player";
		break;
	case 1:
		text = "Enemy";
		break;
	case 2:
		text = "Coin";
		break;
	case 3:
		text = "Ability";
		break;
	}
	return text;
}

Factory::Factory(sf::Texture text, float x, float y)
{
	flagExist = true;
	//texture.loadFromFile("images/coin.png");
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 3);
	typeOfObject = ObjectType(dist(gen));
	sprite.setTexture(text);
	sprite.setPosition(x, y);
	size = Size(sprite.getPosition().x, sprite.getPosition().y,
		sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	sprite.setScale(0.5, 0.5);

}
void Factory::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}
Factory::Factory()
{
}


Factory::~Factory()
{
}
