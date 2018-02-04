#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "VectorOperations.h"
class Object
{
public:
	Object();
	~Object();
	Object(sf::Vector2f location, sf::Vector2f size, double weigth)
			:location(location), weigth(weigth),size(size) {}
	sf::Vector2f getLocation() { return location; }
	sf::Vector2f getSize() { return size; }
	double getWeight() { return weigth; }
	void setLocation(sf::Vector2f location) { this->location = location; }
	void setWeigth(double weigth) { this->weigth = weigth; }
	sf::Sprite getSprite() { return *sprite; }
protected:
	sf::Sprite *sprite;
	double weigth;
	sf::Vector2f size; 
	sf::Vector2f location;

};
#endif OBJECT_H

