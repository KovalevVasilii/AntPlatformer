#pragma once
#include "Person.h"
#include "view.h"
class Level;
class Enemy :
	public Person
{
public:
	Enemy(sf::Sprite &sprite, std::string name, Size size, sf::Vector2f location, float health, Level& lvl) :
		Person(sprite, name, size, location, health) {
		state = idle; obj = lvl.GetAllObjects();
		if (name == "Enemy") {
			sprite.setTextureRect(sf::IntRect(4, 19, size.w, size.h));
		}
	}
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time);
	lvl::View view;

	~Enemy();
};
