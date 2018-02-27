#ifndef ENEMY_H
#define ENEMY_H
class Player;
#include "Person.h"
//#include "Player.h"
#include "Level.h"
#include <SFML/Audio.hpp>
class Enemy :
	public Person
{
public:
	Enemy(sf::Image*image, std::string name, Size size,float health, Level* lvl, float radOfView,float speed, ObjectT* obj) 
		:radOfView(radOfView),speed(speed),
		Person(image, name, size,health,lvl, obj) {
		state = idle; 
		CurrentFrame = 0;
		sprite.setTextureRect(sf::IntRect(55*CurrentFrame, 10, 50,65));
		hitM = new sf::Music;
		hitM->openFromFile("hitM.wav");
		
	}
	
	float getlDX() { return lDX; }
	void update(float time, Player& player);
	~Enemy();
	void draw(sf::RenderWindow* window);
private:
	void checkCollisionWithMap(float Dx, float Dy);
	int way(Size& hero);
	float radOfView;
	float speed;
	float CurrentFrame;
	float lDX;
	sf::Music* hitM;
};
#endif ENEMY_H