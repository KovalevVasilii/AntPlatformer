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
void Enemy::update(float time)
{
	if (name == "easyEnemy") {
		moveTimer += time; if (moveTimer>3000) { dx *= -1; moveTimer = 0; }
		checkCollisionWithMap(dx, 0);
		size.x += dx * time;
		sprite.setPosition(size.x + size.w / 2, size.y + size.h / 2);
		if (health <= 0) { life = false; }
	}
}



Enemy::~Enemy()
{
}