#pragma once
#include "Person.h"
class Player :
	public Person
{
private:
	sf::Vector2f getMoveDirection();
	void Calculate();
public:
	Player();
	~Player();
};
