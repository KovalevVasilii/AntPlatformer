#include "Player.h"

		void Player::control(float time) 
		{
		if (sf::Keyboard::isKeyPressed) 
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				state = left; 
				curSpeed = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(sf::IntRect(49 * int(CurrentFrame), 118, 48, 49));

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				state = right;
				curSpeed = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(sf::IntRect(49*int(CurrentFrame), 0, 49, 50));
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (onGround)) {
				state = jump; dy = -0.6; onGround = false;

			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				state = down;
			}
			}
		}
	void Player::checkCollisionWithMap(float Dx, float Dy,float time)
	{
		std::vector<ObjectT>* obj(lvl->GetAllObjectTs());
		for (auto it=obj->begin();it!=obj->end();)
		{
			if (getRect().intersects(it->rect))
			{	
				if (it->name == "solid")
				{
					if (Dy > 0) { size.y = it->rect.top - size.h;  dy = 0; onGround = true; }
					if (Dy < 0) { size.y = it->rect.top + it->rect.height;   dy = 0; }
					if (Dx > 0) { size.x = it->rect.left - size.w; }
					if (Dx < 0) { size.x = it->rect.left + it->rect.width; }
				}
				else if (it->name == "coin")
				{
					it = obj->erase(it--);
					coin++;
				}
				else if (it->name == "easyEnemy")
					
				{
					if (lastTime < time)
					{
						health -= 20;
						lastTime +=2;
					}
					//std::cout <<"Last Time "<< lastTime << std::endl;
					//std::cout << "Time "<< time << std::endl;
					
					
					
				}
				else if (it->name == "die")
				{
					health = 0;
					life = false;
				}
			}
			it++;
		}
	}
	void Player::update(float time)
	{
		control(time);
		switch (state)
		{
		case right:
			dx = curSpeed;
			break;
		case left:
			dx = -curSpeed;
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
		checkCollisionWithMap(dx, 0, time);
		size.y += dy * time;
		checkCollisionWithMap(0, dy,  time);
		sprite.setPosition(size.x + size.w / 2, size.y + size.h / 2);
		if (health <= 0) { life = false; }
		if (!isMove) { curSpeed = 0; }
		setPlayerCoordinateForView(size.x, size.y,*view);
		if (life) { setPlayerCoordinateForView(size.x, size.y, *view); }
		dy = dy + 0.0015*time;
	}
	void Player::setPlayerCoordinateForView(float x, float y,sf::View& view) 
	{
		float tempX = x; float tempY = y;
		view.setSize(900, 700);
		view.setCenter(tempX, tempY);
	}

	int Player::getCoin() const
	{
		return coin;
	}