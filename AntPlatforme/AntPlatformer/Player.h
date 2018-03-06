#ifndef PLAYER_H
#define PLAYER_H
#include "Person.h"
#include "Level.h"
#include <list>
#include "enemy.h"
#include "Ability.h"
class Player :
	public Person
{
public:
	Player(sf::Image* image, std::string name, Size size, float health, sf::View& view, 
		int countWeapons, Level *lvl,float speed, ObjectT* obj, sf::Image* weaponIm) :
		Person(image, name, size, health,lvl,obj),view(&view),coin(0),speed(speed) 
	{

		abilitiesCoef = 0;
		direction = Wright;
		state = idle; 
		CurrentFrame = 1;
		this->speed= speed;
		lastTime = 0;
		sprite.setTextureRect(sf::IntRect(49 * int(CurrentFrame), 0, 49, 50));
		//std::cout << this->speed << std::endl;
		weaponIm->loadFromFile("images/weapon.png");
		this->weaponIm = weaponIm;
		for (int i = 0; i <=countWeapons; i++)
		{
			weapons.push_back(new Weapon(weaponIm, Size(0, 0, weaponIm->getSize().x, weaponIm->getSize().y), 0.1, 10, false));
		}
		pause = 5;
		
	}
	int getCoin() const;
	sf::Sprite& getSprite() { return sprite; }
	void setPlayerCoordinateForView(float x, float y, sf::View& view);
	void update(float time, std::vector<std::shared_ptr<Enemy>>& enemyList, std::vector<std::shared_ptr<Ability>>&abilitiesList);
	StatePerson getState() const { return state; }
	void draw(sf::RenderWindow* window);
	void addBullet(){ weapons.push_back(new Weapon(weaponIm, Size(0, 0, weaponIm->getSize().x, weaponIm->getSize().y), 0.1, 10, false)); }
	~Player() {}
	std::string getInformation() { return information; }
	void setHealth() { health = 100; }
private:
	std::string information;
	float abilitiesCoef;
	void updateWeapon(float time, std::vector<std::shared_ptr<Enemy>>& enemyList);
	void checkCollisionWithMap(float Dx, float Dy, float time);
	void control(float time);
	float CurrentFrame;
	sf::View* view;
	int pause;
	int coin;
	float lastTime;
	float speed;
	float healthTimer;
	float curSpeed;
	WeaponDirection direction;
	std::vector<Weapon*> weapons;
	sf::Image*weaponIm;
};
#endif PLAYER_H