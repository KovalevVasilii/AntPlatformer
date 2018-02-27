#ifndef WEAPON_H
#define WEAPON_H

#include "Object.h"

class Weapon:public Object
{
public:
	Weapon();
	~Weapon();
	Weapon(sf::Image* image, Size size, double rateOfFire,double damage,bool typeOfWeapon)
			:rateOfFire(rateOfFire),damage(damage),typeOfWeapon(typeOfWeapon), Object(image,size){}
	double getDamage() { return damage; }
	double getRateOfFire() { return rateOfFire; }
	bool getTypeOfWeapon() { return typeOfWeapon; }
	void setTypeOfWeapon(bool type) {  typeOfWeapon=type; }
	void update(float time);
	void setDirection(WeaponDirection direction)
	{
		this->direction = direction;
	};
private:
	WeaponDirection direction;
	double rateOfFire;
	double damage;
	bool typeOfWeapon;
};
#endif WEAPON_H
