#pragma once
#include "Person.h"

#include "Level.h"
class Enemy :
	public Person
{
public:
	Enemy(sf::Image &image, std::string name, Size size,float health, Level& lvl) :
		Person(image, name, size,health) {
		state = idle; obj = lvl.GetAllObjectTs();
		if (name == "easyEnemy") {
			sprite.setTextureRect(sf::IntRect(100, 100, size.w, size.h));
		}
	}
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time);
	~Enemy();
};