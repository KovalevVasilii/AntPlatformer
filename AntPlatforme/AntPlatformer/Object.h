#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "VectorOperations.h"
#include "size.h"
class Object
{
public:
	Object();
	~Object();
	Object(sf::Sprite sprite, sf::Vector2f location, Size size)
			:location(location), size(size),sprite(&sprite) {}
	sf::Vector2f getLocation() { return location; }
	Size getSize() { return size; }
	sf::FloatRect getRect() { return sf::FloatRect(size.x, size.y, size.w, size.h); }
	void setLocation(sf::Vector2f location) { this->location = location; }
	sf::Sprite getSprite() { return *sprite; }
protected:
	sf::Sprite *sprite;
	Size size; 
	sf::Vector2f location;

};
#endif OBJECT_H

