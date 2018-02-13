#include "Player.h"



void Player::control() {
	if (sf::Keyboard::isKeyPressed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			state = left; speed = 0.1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			state = right; speed = 0.1;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (onGround)) {
			state = jump; dy = -0.6; onGround = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			state = down;
		}
	}
}
void Player::checkCollisionWithMap(float Dx, float Dy)
{
	for (int i = 0; i<obj.size(); i++)
		if (getRect().intersects(obj[i].rect))
		{
			if (obj[i].name == "solid")
			{
				if (Dy>0) { size.y = obj[i].rect.top - size.h;  dy = 0; onGround = true; }
				if (Dy<0) { size.y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx>0) { size.x = obj[i].rect.left - size.w; }
				if (Dx<0) { size.x = obj[i].rect.left + obj[i].rect.width; }
			}
		}
}
void Player::update(float time)
{
	control();
	switch (state)
	{
	case right:dx = speed; break;
	case left:dx = -speed; break;
	case up: break;
	case down: dx = 0; break;
	case idle: break;
	}
	size.x += dx * time;
	checkCollisionWithMap(dx, 0);
	size.y += dy * time;
	checkCollisionWithMap(0, dy);
	sprite->setPosition(size.x + size.w / 2, size.y + size.h / 2);
	if (health <= 0) { life = false; }
	if (!isMove) { speed = 0; }
	view.setPlayerCoordinateForView(size.x, size.y);
	if (life) { view.setPlayerCoordinateForView(size.x, size.y); }
	dy = dy + 0.0015*time;
}

Player::~Player()
{
}