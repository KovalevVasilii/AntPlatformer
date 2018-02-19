#pragma once
#include "Person.h"

#include "Level.h"
class Enemy :
	public Person
{
public:
	Enemy(sf::Image &image, std::string name, Size size,float health, Level* lvl) :
		Person(image, name, size,health,lvl) {
		state = idle; 
		if (name == "Enemy") {
			sprite.setTextureRect(sf::IntRect(4, 19, size.w, size.h));
		}
	}
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time);
	~Enemy();
};