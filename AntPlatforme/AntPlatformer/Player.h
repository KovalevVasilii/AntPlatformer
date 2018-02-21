#pragma once
#include "Person.h"
#include "Level.h"
class Player :
	public Person
{
public:
	Player(sf::Image &image, std::string name, Size size, float health, sf::View& view, Level *lvl) :
		Person(image, name, size, health,lvl),view(&view),coin(0){
		state = idle; 
		if (name == "Player") {
			CurrentFrame = 1;
			sprite.setTextureRect(sf::IntRect(49 * int(CurrentFrame), 0, 49, 50));
		}
		
	}
	int getCoin() const;
	void setPlayerCoordinateForView(float x, float y, sf::View& view);
	void checkCollisionWithMap(float Dx, float Dy);
	void control(float time);
	void update(float time);
	float CurrentFrame;
	sf::View* view;
	int coin;
	~Player(){}
};