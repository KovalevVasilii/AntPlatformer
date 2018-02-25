#ifndef ENEMY_H
#define ENEMY_H
class Player;
#include "Person.h"
//#include "Player.h"
#include "Level.h"
class Enemy :
	public Person
{
public:
	Enemy(sf::Image &image, std::string name, Size size,float health, Level* lvl, float radOfView,float speed) :radOfView(radOfView),speed(speed),
		Person(image, name, size,health,lvl) {
		state = idle; 
		CurrentFrame = 0;
		sprite.setTextureRect(sf::IntRect(55*CurrentFrame, 10, 50,65));

	}
	float getlDX() { return lDX; }
	void update(float time, Player& player);
	~Enemy();
private:
	void checkCollisionWithMap(float Dx, float Dy);
	int way(Size& hero);
	float radOfView;
	float speed;
	float CurrentFrame;
	float lDX;

};
#endif ENEMY_H