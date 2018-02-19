#pragma once
#include "Person.h"
#include "Level.h"
class Player :
	public Person
{
public:
	Player(sf::Image &image, std::string name, Size size, float health, sf::View view, Level *lvl) :
		Person(image, name, size, health,lvl),view(view),coin(0){
		state = idle; 
		if (name == "Player") {
			sprite.setTextureRect(sf::IntRect(4, 19, size.w, size.h));
		}
		
	}
	int getCoin() const;
	void setPlayerCoordinateForView(float x, float y, sf::View view);
	void checkCollisionWithMap(float Dx, float Dy);
	void control();
	void update(float time);
	sf::View view;
	int coin;
	~Player(){}
};