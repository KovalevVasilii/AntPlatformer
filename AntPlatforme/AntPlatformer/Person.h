#ifndef PERSON_H
#define PERSON_H
#include "Object.h"
#include "Level.h"
#include "Weapon.h"

class Person :
	public Object
{
public:
	Person();
	Person(sf::Image* image, std::string name, Size size,float health, Level *lvl, ObjectT* obj)
		:name(name), health(health), lvl(lvl), object(obj), Object(image,size)
	{
		dx = 0; dy = 0; moveTimer = 0; shock=0;
		life = true; onGround = false; isMove = false;
	}
	~Person();
	bool isAlive() { return life; }
	int getHealth() { return health; }
	void hit(Weapon& weapon);
	std::string getName() { return name; }
	int getDx() { return dx; }
	void setDx(int Dx) { dx = Dx; }
	void setSizeX(float x) { size.x = x; }
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
	ObjectT* object;
	int shock;
};
#endif PERSON_H

