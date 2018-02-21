#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>
#include "constants.h"

#include "size.h"
class Object
{
public:
	Object();
	~Object();
	Object(sf::Image image, Size size)
		: size(size), image(&image) 
	{
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(size.w / 2, size.h / 2);
	}
	Size getSize() const { return size; }
	sf::FloatRect getRect() { return sf::FloatRect(size.x, size.y, size.w, size.h); }
	sf::Image getImage() { return *image; }
	sf::Image *image;
	sf::Texture texture;
	sf::Sprite sprite;
	Size size;

};
#endif OBJECT_H

