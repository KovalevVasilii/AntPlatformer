#include "Weapon.h"



Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

void Weapon::update(float time)
{
	if (typeOfWeapon)
	{
		int coef = -1;
		if (direction == Wright)
		{
			coef = 1;
		}
		sprite.setPosition(sprite.getPosition().x + coef*time*getRateOfFire(), sprite.getPosition().y);
		sprite.setRotation(sprite.getRotation() + 4);
		size = Size(sprite.getPosition().x, sprite.getPosition().y,
			sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	}
}