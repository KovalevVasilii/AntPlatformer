#ifndef PERSON_H
#define PERSON_H
#include "Object.h"
#include "Weapon.h"
class Person :
	public Object
{
public:
	Person();
	~Person();
	void Move(sf::Vector2f direction);
	bool isAlive() { return life; }
	void hit(Weapon& weapon);
	virtual void update() = 0;
	virtual bool atack() = 0;
	float speed;
	float lastTime;
protected:
	double health;
	bool life;
	StatePerson state;

};
#endif PERSON_H

