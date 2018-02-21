#include "enemy.h"
void Enemy::checkCollisionWithMap(float Dx, float Dy)
{
	std::vector<ObjectT>* obj(lvl->GetAllObjectTs());
	for (auto it = obj->begin(); it != obj->end();it++)
		if (getRect().intersects(it->rect))
		{
			if (it->name == "solid")
			{
				if (Dy>0) { size.y = it->rect.top - size.h;  dy = 0; onGround = true; }
				if (Dy<0) { size.y = it->rect.top + it->rect.height;   dy = 0; }
				if (Dx>0) { size.x = it->rect.left - size.w; }
				if (Dx<0) { size.x = it->rect.left + it->rect.width; }
			}
		}
}
void Enemy::update(float time,const Player* player)
{
	Size p = player->getSize();
	sprite.setPosition(size.x + size.w / 2, size.y + size.h / 2);
	if (way(p) <= radOfView)
	{
		if (player->getSize().x - getSize().x < 0)
		{
			sprite.setTextureRect(sf::IntRect(300+ 55 * CurrentFrame, 12, 50, 67));
		}
		else
		{
			sprite.setTextureRect(sf::IntRect(55 * CurrentFrame, 10, 50, 65));
		}
		/*state = player->getState();
		
		switch (state)
		{
		case right:
			//dx = speed;
			sprite.setTextureRect(sf::IntRect(300, 12, 50, 67));
			break;
		case left:
			//dx = -speed;
			sprite.setTextureRect(sf::IntRect(55 * CurrentFrame, 10, 50, 65));
			break;

		}*/
	}
	else
	{
		/*moveTimer += time;
		if (moveTimer > 3000)
		{
			dx *= -1; moveTimer = 0;
		}
		checkCollisionWithMap(dx, 0);
		size.x += dx * time;
		
		*/
	}
		if (health <= 0) { life = false; }
	
}
int Enemy::way(Size& hero)
{
	return sqrt((hero.x- size.x)*(hero.x - size.x) +
		(hero.y - size.y)*(hero.y - size.y));
}

Enemy::~Enemy()
{
}