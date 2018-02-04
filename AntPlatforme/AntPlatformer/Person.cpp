#include "Person.h"



Person::Person(){}


Person::~Person(){}

void Person::hit(Weapon& weapon)
{
	health -= weapon.getDamage();
}
void Person::Move(sf::Vector2f direction)
{
	if (direction == sf::Vector2f(0, 0))
		return;
	direction = VectorOperations::ReductToLength(direction, speed);
	float deltaTime = CLOCK.getElapsedTime().asSeconds() - lastTime;

	if (state == shoot)
		state = walkShoot;
	if (state == idle)
		state = walk;
	//calculating bias
	sf::Vector2f bias = direction * deltaTime;
	//modifying position
	location += bias;

}
