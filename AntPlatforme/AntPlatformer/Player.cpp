#include "Player.h"

		void Player::control() 
		{
		if (sf::Keyboard::isKeyPressed) 
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				state = left; speed = 0.5;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				state = right; speed = 0.5;
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
		std::vector<ObjectT>* obj(lvl->GetAllObjectTs());
		for (auto it=obj->begin();it!=obj->end();)
		{
			if (getRect().intersects(it->rect))
			{
				if (it->name == "solid")
				{
					if (Dy>0) { size.y = it->rect.top - size.h;  dy = 0; onGround = true; }
					if (Dy<0) { size.y = it->rect.top + it->rect.height;   dy = 0; }
					if (Dx>0) { size.x = it->rect.left - size.w; }
					if (Dx<0) { size.x = it->rect.left + it->rect.width; }
				}
				else
					if (it->name == "coin")
					{
						it=obj->erase(it--);
						coin++;
					}
					else
						if (it->name == "die")
						{
							//смерть
						}
			}
			it++;
		}
	}
	void Player::update(float time)
	{
		control();
		switch (state)
		{
		case right:
			dx = speed;
			break;
		case left:
			dx = -speed;
			break;
		case up: 
			break;
		case down:
			dx = 0; 
			break;
		case idle:
			break;
		}
		size.x += dx * time;
		checkCollisionWithMap(dx, 0);
		size.y += dy * time;
		checkCollisionWithMap(0, dy);
		sprite.setPosition(size.x + size.w / 2, size.y + size.h / 2);
		if (health <= 0) { life = false; }
		if (!isMove) { speed = 0; }
		setPlayerCoordinateForView(size.x, size.y,view);
		if (life) { setPlayerCoordinateForView(size.x, size.y, view); }
		dy = dy + 0.0015*time;
	}
	void Player::setPlayerCoordinateForView(float x, float y,sf::View view) 
	{
		float tempX = x; float tempY = y;
		if (y > 624) tempY = 624;

		view.setCenter(tempX, tempY);
	}

	int Player::getCoin() const
	{
		return coin;
	}