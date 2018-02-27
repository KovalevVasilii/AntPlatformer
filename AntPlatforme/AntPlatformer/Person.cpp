#include "Person.h"



Person::Person() {}


Person::~Person() {}

void Person::hit(Weapon& weapon)
{
	health -= weapon.getDamage();
	shock=80;
}

