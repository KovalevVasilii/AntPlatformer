#pragma once
#include "Object.h"

class Factory 
{
public:
	Factory(sf::Texture text, float x, float y);
	std::string to_String();
	ObjectType getTypeOfObject() { return typeOfObject; }
	sf::Texture getTexture() { return texture; }
	sf::Sprite getSprite() { return sprite; }
	sf::FloatRect getRect() { return sf::FloatRect(size.x, size.y, size.w, size.h); }
	void draw(sf::RenderWindow* window);
	bool flagExist;
	Factory();
	~Factory();
private:
	Size size;
	sf::Texture texture;
	sf::Sprite sprite;
	ObjectType typeOfObject;
};

