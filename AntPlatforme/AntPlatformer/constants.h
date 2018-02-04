#include "SFML\Graphics.hpp"
#ifndef CONSTANTS_H
#define CONSTANTS_H
enum PersonType
{
	player = 0,
	enemy,
	typesNumber
};

enum StatePerson
{
	idle = 0,
	walk,
	shoot,
	walkShoot
};

static const sf::Vector2f originDirection = sf::Vector2f(1, 0);
static const sf::Clock CLOCK;
extern const int FPS_LOCK;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
#endif CONSTANTS_H
