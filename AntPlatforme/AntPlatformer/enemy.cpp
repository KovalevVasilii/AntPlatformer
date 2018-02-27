#include "enemy.h"
#include "Player.h"
void Enemy::checkCollisionWithMap(float Dx, float Dy)
{
	std::vector<ObjectT>* obj(lvl->GetAllObjectTs());
	for (auto it = obj->begin(); it != obj->end();it++)
		if (getRect().intersects(it->rect))
		{
			if (it->name == "solid")
			{
				if (Dy>0) { size.y = it->rect.top - size.h;  dy = 0; onGround = true; }
				if (Dy<0) {  size.y = it->rect.top + it->rect.height;   dy = 0; }
				if (Dx>0) { size.x = it->rect.left - size.w; }
				if (Dx<0) { size.x = it->rect.left + it->rect.width; }
			}
			else if (it->name == "die")
			{
				life = false;
			}
		}

}
void Enemy::update(float time,Player& player)
{
	if (health <= 0)
	{
		life = false;
	}
	object=lvl->GetObjectT("easyEnemy");
	Size p = player.getSize();
	sprite.setPosition(size.x + size.w / 2, size.y + size.h / 2);
	if (way(p) <= radOfView)
	{
		if (player.getSize().x - getSize().x < 0)
		{
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(sf::IntRect(59 * int(CurrentFrame), 62, 59, 62));
			dx = -speed;
			lDX = dx;
		}
		else if(player.getSize().x - getSize().x >0)
		{
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(sf::IntRect(59 * int(CurrentFrame), 0, 59, 58));
			dx = speed;
			lDX = dx;
		}
		}
	else
	{
		dx = 0;
	}
	size.x += dx * time;
	checkCollisionWithMap(dx, 0);
	
	size.y += dy * time;
	shock--;
	checkCollisionWithMap(0, dy);
	dy = dy + 0.0015*time;
	if (shock >= 0)
	{
		hitM->play();
		if (player.getSize().x - getSize().x > 0)
		{
			sprite.setTextureRect(sf::IntRect(663, 467, 45, 83));
		}
		else
		{
			sprite.setTextureRect(sf::IntRect(708, 467, 45, 83));
		}
	}
		
}
int Enemy::way(Size& hero)
{
	return sqrt((hero.x- size.x)*(hero.x - size.x) +
		(hero.y - size.y)*(hero.y - size.y));
}

Enemy::~Enemy()
{
}

void Enemy::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	//window->display();
}