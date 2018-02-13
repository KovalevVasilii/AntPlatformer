#ifndef WEAPON_H
#define WEAPON_H

#include "Object.h"

class Weapon:public Object
{
public:
	Weapon();
	~Weapon();
	Weapon(double rateOfFire,double damage,bool typeOfWeapon)
			:rateOfFire(rateOfFire),damage(damage),typeOfWeapon(typeOfWeapon){}
	double getDamage() { return damage; }
	double getRateOfFire;
	bool getTypeOfWeapon() { return typeOfWeapon; }
private:
	double rateOfFire;
	double damage;
	bool typeOfWeapon;
};
#endif WEAPON_H
