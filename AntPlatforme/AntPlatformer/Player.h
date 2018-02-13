#pragma once
#include "Person.h"
#include "Level.h"
class Player :
	public Person
{
public:
	Player(sf::Image &image, std::string name, Size size, float health, Level& lvl,sf::View view) :
		Person(image, name, size, health),view(view) {
		state = idle; obj = lvl.GetAllObjectTs();
		if (name == "Player") {
			sprite.setTextureRect(sf::IntRect(4, 19, size.w, size.h));
		}
		
	}
	void setPlayerCoordinateForView(float x, float y, sf::View view);
	void checkCollisionWithMap(float Dx, float Dy);
	void control();
	void update(float time);
	sf::View view;
	~Player(){}
};