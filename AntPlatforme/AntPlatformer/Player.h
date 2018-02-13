#pragma once
#include "Person.h"
#include "view.h"
class Level;
class Player :
	public Person
{
public:
	Player(sf::Sprite &sprite, std::string name, Size size, sf::Vector2f location, float health,Level& lvl):
		Person(sprite, name, size,location,health){
		state=idle; obj = lvl.GetAllObjects();
		if (name == "Player") {
			sprite.setTextureRect(sf::IntRect(4, 19, size.w, size.h));
		}
	}
	void checkCollisionWithMap(float Dx, float Dy);
	void control();
	void update(float time);
	lvl::View view;
	
	~Player();
};
