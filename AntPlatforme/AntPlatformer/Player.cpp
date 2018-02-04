#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}
sf::Vector2f Player::getMoveDirection()
{
	sf::Vector2f direction = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		direction.x -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		direction.x += 1;
	return direction;
}
void Player::Calculate()
{
	state = idle;
	sf::Vector2f moveDirection = getMoveDirection();
	if (moveDirection != sf::Vector2f(0, 0))
		Move(moveDirection);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		atack();
	//Person::Calculate();
}