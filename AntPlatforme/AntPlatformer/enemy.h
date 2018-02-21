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
		if (name == "easyEnemy") {
			CurrentFrame = 1;
			sprite.setTextureRect(sf::IntRect(0, 0, 50,65));
			dx = 0.5;
		}
	}
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time);
	float CurrentFrame;
	~Enemy();
};