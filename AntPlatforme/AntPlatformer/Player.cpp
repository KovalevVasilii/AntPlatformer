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
				direction = Wleft;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				state = right;
				curSpeed = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(sf::IntRect(49*int(CurrentFrame), 0, 49, 50));
				direction = Wright;
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (onGround)) {
				state = jump; dy = -0.8+abilitiesCoef; onGround = false;

			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				state = down;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				for (auto weapon : weapons)
				{
					if (!weapon->getTypeOfWeapon() && pause <= 0)
					{
						weapon->setTypeOfWeapon(true);
						weapon->setDirection(direction);
						weapon->sprite.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width - 30,
							this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height / 2);
						pause = 5;
						break;
					}
				}
			}
			else
			{
				pause--;
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
				else if (it->name == "die")
				{
					health = 0;
					life = false;
				}
			}
			it++;
		}
	}
	void Player::update(float time, std::vector<std::shared_ptr<Enemy>>& enemyList,std::vector<std::shared_ptr<Ability>>&abilitiesList, std::vector<sf::Sprite>& coins)
	{
		//std::cout << getRect().left << getRect().top << std::endl;
		updateWeapon(time, enemyList);
		for (auto it = enemyList.begin(); it != enemyList.end(); it++)
		{
			if ((*it)->getRect().intersects(getRect()))
			{
				health-=0.05;
				//std::cout << it->getDx() << std::endl;
					if ((*it)->getlDX() > 0)
					{
						(*it)->setSizeX(size.x - (*it)->getSize().w);
						(*it)->setDx(0);
						//std::cout << "KEK" << std::endl;
					}
					if ((*it)->getlDX() < 0)
					{
						(*it)->setSizeX(size.x + (*it)->getSize().w);
						(*it)->setDx(0);
					}
				}
				//if (dx < 0) { size.x = size.x; }
				//if (dx > 0) { size.x = getSize().x - size.w;}
		}
		for (auto it : abilitiesList)
		{
			if (it->getRect().intersects(getRect())&&it->flagExist==true)
			{
				std::cout << it->to_String() << std::endl;
				information = it->to_String();
				switch (it->getTypeOfAbility())
				{
				case 0:
					health += 25;
					break;
				case 1:
					speed += 0.05;
					
					break;
				case 2:
					for (int i = 0; i < 10; i++)
					{
						addBullet();
					}
					break;
				case 3:
					abilitiesCoef -= 0.05;
					break;
				}
				it->flagExist = false;
			}
		}
		for (int i=0;i<coins.size();i++)
		{
			if (coins[i].getGlobalBounds().intersects(getRect())) {
				coin++;
				std::swap(coins[i], coins[coins.size() - 1]);
				coins.pop_back();
			}
		}
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
			checkCollisionWithMap(0, dy, time);
			sprite.setPosition(size.x + size.w / 2, size.y + size.h / 2);
			if (health <= 0) { life = false; }
			if (!isMove) { curSpeed = 0; }
			setPlayerCoordinateForView(size.x, size.y, *view);
			if (life) { setPlayerCoordinateForView(size.x, size.y, *view); }
			dy = dy + 0.0015*time;
		
		shock--;
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

	void Player::updateWeapon(float time, std::vector<std::shared_ptr<Enemy>>& enemyList)
	{
		if (weapons.size() > 0)
		{
			for (auto it = enemyList.begin(); it != enemyList.end(); it++)
			{
				for (int i = 0; i < weapons.size(); i++)
				{
					if (weapons[i]->getTypeOfWeapon() && weapons[i]->getRect().intersects((*it)->getRect()))
						{
							(*it)->hit(*weapons[i]);
							std::swap(weapons[i], weapons[weapons.size() - 1]);
							weapons.pop_back();
					}
				}
			}
			for (int i = 0; i < weapons.size(); i++)
			{
				weapons[i]->update(time);
			}
		}

	}

	void Player::draw(sf::RenderWindow* window)
	{
		window->draw(sprite);
		for (auto weapon : weapons)
		{
			if (weapon->getTypeOfWeapon())
			{
				window->draw(weapon->sprite);
			}
		}
	}