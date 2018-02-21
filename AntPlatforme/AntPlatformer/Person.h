#ifndef PERSON_H
#define PERSON_H
#include "Object.h"
#include "Weapon.h"
#include "Level.h"
class Person :
	public Object
{
public:
	Person();
	Person(sf::Image &image, std::string name, Size size,float health, Level *lvl) 
		:name(name), health(health), lvl(lvl), Object(image,size)
	{
		dx = 0; dy = 0; moveTimer = 0;
		life = true; onGround = false; isMove = false;
	}
	~Person();
	bool isAlive() { return life; }
	int getHealth() { return health; }
	void hit(Weapon& weapon);
	//virtual void update() = 0;
	//virtual bool atack() = 0;
	float speed;
	float lastTime;
protected:
	std::string name;
	Level *lvl;
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

