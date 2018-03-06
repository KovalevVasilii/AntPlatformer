#include "Ability.h"

std::string Ability::to_String()
{
	std::string text;
	switch (typeOfAbility)
	{
	case 0:
		text = "Health Up!";
		break;
	case 1:
		text = "Speed Up!";
		break;
	case 2:
		text = "Bullets Up!";
		break;
	case 3:
		text = "Jump Up!";
		break;
	}
	return text;
}
Ability::Ability()
{
}


Ability::~Ability()
{
}
Ability::Ability(sf::Texture text, float x, float y)
{
	flagExist = true;
	//texture.loadFromFile("images/coin.png");
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, 3);
		typeOfAbility = AbilityType(dist(gen));
		sprite.setTexture(text);
		sprite.setPosition(x, y);
		size = Size(sprite.getPosition().x, sprite.getPosition().y,
			sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
		sprite.setScale(0.5, 0.5);
	
}
void Ability::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}