#include "enemy.h"
void Enemy::checkCollisionWithMap(float Dx, float Dy)
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
void Enemy::update(float time)
{
	if (name == "easyEnemy") {
		moveTimer += time; if (moveTimer>3000) 
		{ 
			dx *= -1; moveTimer = 0; 
		}
		checkCollisionWithMap(dx, 0);
		size.x += dx * time;
		sprite.setPosition(size.x + size.w / 2, size.y + size.h / 2);
		if (health <= 0) { life = false; }
	}
}



Enemy::~Enemy()
{
}