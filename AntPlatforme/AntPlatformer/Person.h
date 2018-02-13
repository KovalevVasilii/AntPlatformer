#ifndef PERSON_H
#define PERSON_H
#include "Object.h"
#include "Weapon.h"
class ObjectT;
class Person :
	public Object
{
public:
	Person();
	Person(sf::Sprite &sprite, std::string name, Size size, sf::Vector2f location,float health) :name(name),health(health),
		Object(sprite, location, size)
	{
		dx = 0; dy = 0; moveTimer = 0; 
		life = true; onGround = false; isMove = false;
	}
	~Person();
	void Move(sf::Vector2f direction);
	bool isAlive() { return life; }
	void hit(Weapon& weapon);
	virtual void update() = 0;
	virtual bool atack() = 0;
	float speed;
	float lastTime;
protected:
	std::string name;
	std::vector<ObjectT> obj;
	double health;
	bool life;
	bool isMove;
	bool onGround;
	float dx;
	float dy;
	float moveTimer;
	StatePerson state;

};
#endif PERSON_H

