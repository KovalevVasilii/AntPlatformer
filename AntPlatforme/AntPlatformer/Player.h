#ifndef PLAYER_H
#define PLAYER_H
#include "Person.h"
#include "Level.h"
#include <list>
#include "enemy.h"
class Player :
	public Person
{
public:
	Player(sf::Image &image, std::string name, Size size, float health, sf::View& view, Level *lvl,float speed) :
		Person(image, name, size, health,lvl),view(&view),coin(0),speed(speed) 
	{
		state = idle; 
		CurrentFrame = 1;
		this->speed= speed;
		lastTime = 0;
		sprite.setTextureRect(sf::IntRect(49 * int(CurrentFrame), 0, 49, 50));
		//std::cout << this->speed << std::endl;
		
	}
	int getCoin() const;
	sf::Sprite& getSprite() { return sprite; }
	void setPlayerCoordinateForView(float x, float y, sf::View& view);
	void update(float time, std::list<Enemy*> enemyList);
	StatePerson getState() const { return state; }
	~Player() {}
private:
	void checkCollisionWithMap(float Dx, float Dy, float time);
	void control(float time);
	float CurrentFrame;
	sf::View* view;
	int coin;
	float lastTime;
	float speed;
	float healthTimer;
	float curSpeed;

};
#endif PLAYER_H