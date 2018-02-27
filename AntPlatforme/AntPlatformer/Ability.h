#pragma once
#include "Object.h"
#include <random>
#include "Level.h"
//#include <iostream>
class Ability
{
public:
	Ability(sf::Texture text, float x, float y);
	std::string to_String();
	AbilityType getTypeOfAbility() { return typeOfAbility; }
	sf::Texture getTexture() { return texture; }
	sf::Sprite getSprite() { return sprite; }
	sf::FloatRect getRect() { return sf::FloatRect(size.x, size.y, size.w, size.h); }
	void draw(sf::RenderWindow* window);
	bool flagExist;
	Ability();
	~Ability();
private:
	Size size;
	sf::Texture texture;
	sf::Sprite sprite;
	AbilityType typeOfAbility;
};

