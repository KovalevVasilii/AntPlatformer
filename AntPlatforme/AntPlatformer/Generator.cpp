#include "Generator.h"
#include <random>


Generator::Generator(int width, int height)
	:width(width), height(height), levels(height / 120), heightLevel(height / levels)
{
	heightLevel=height / levels;
	widthLevel = (5 * 20 * 5);
}


Generator::~Generator()
{
}

Level* Generator::generate()
{

	std::random_device gen;
	std::uniform_int_distribution<> genLevel(0, levels);
	//std::uniform_int_distribution<> genBool(0, 2);
	std::uniform_int_distribution<> genWidth(2, levels-2);
	std::uniform_int_distribution<> genPlat(1, 4);
	std::uniform_int_distribution<> genPlant(0, 3);
	std::uniform_int_distribution<> offsetX(0, 2 * 5 * 20);
	std::uniform_int_distribution<> offsetXEnemy(0, 5 * 20);
	std::uniform_int_distribution<> offsetXAbility(0, 4 * 20);
	std::uniform_int_distribution<> offsetYAbility(0, 40);
	std::uniform_int_distribution<> offsetY(0, 3 * 20);
	std::vector<ObjectT> platforms;
	std::uniform_int_distribution<> genAbility(0, 3);

	ObjectT enemyObj;
	sf::Rect <float> enemyRect;
	enemyRect.height = 40;
	enemyRect.width = 20;
	enemyObj.name = "easyEnemy";
	int enemyCount = genWidth(gen);

	ObjectT abilityObj;
	abilityObj.name = "ability";
	sf::Rect <float> abilityRect;
	abilityRect.height = 20;
	abilityRect.width = 20;

	ObjectT plantObj;
	plantObj.name = "plant";
	sf::Rect <float> plantRect;
	plantObj.rect = plantRect;
	sf::Sprite plantSprite;

	int levelNum = genLevel(gen);
	for (int i = 0; i < width / widthLevel; i++)
	{
		for (int j = 0; j < levels-1; j++)
		{
			if ((i + j) % 2 == 0)
			{
				int count = genWidth(gen);
				sf::Vector2f pos(i*widthLevel + offsetX(gen), j*heightLevel + offsetY(gen));
				ObjectT platformObj;
				sf::Rect <float> objectTRect;
				sf::Sprite platformSprite;
				bool enemy=false;
				switch (genPlat(gen))
				{
				case 1:
					for (int ñ = 0; ñ < count; ñ++)
					{

						objectTRect.top = pos.y;
						objectTRect.left = pos.x;
						platformObj.name = "solid";
						platformSprite.setPosition(pos);
						platformSprite.setTexture(*platTexture.plat1);
						platformObj.sprite = platformSprite;
						objectTRect.height = platformObj.sprite.getGlobalBounds().height;
						objectTRect.width = platformObj.sprite.getGlobalBounds().width;
						platformObj.rect = objectTRect;
						platforms.push_back(platformObj);

						int abilities = genAbility(gen);
						for (int ab = 0; ab < abilities; ab++)
						{
							abilityRect.left = pos.x+ offsetXAbility(gen);
							abilityRect.top = pos.y-20- offsetYAbility(gen);
							abilityObj.rect = abilityRect;
							level.addObjectT(abilityObj);
						}

						int plants = genPlant(gen);
						switch (genPlat(gen))
						{
						case 1:
							for (int pl = 0; pl < plants; pl++)
							{
								plantSprite.setTexture(*platTexture.plant1);
								plantSprite.setPosition(pos.x + offsetXAbility(gen), pos.y - platTexture.plant1->getSize().y+5);
								plantObj.sprite = plantSprite;
								level.addObjectT(plantObj);
							}
							break;
						case 2:
							for (int pl = 0; pl < plants; pl++)
							{
								plantSprite.setTexture(*platTexture.plant2);
								plantSprite.setPosition(pos.x + offsetXAbility(gen), pos.y - platTexture.plant2->getSize().y + 5);
								plantObj.sprite = plantSprite;
								level.addObjectT(plantObj);
							}
							break;
						case 3:
							for (int pl = 0; pl < plants; pl++)
							{
								plantSprite.setTexture(*platTexture.plant3);
								plantSprite.setPosition(pos.x + offsetXAbility(gen), pos.y - platTexture.plant3->getSize().y + 5);
								plantObj.sprite = plantSprite;
								level.addObjectT(plantObj);
							}
							break;
						default:
							break;
						}

						if (enemyCount > 0 && !enemy)
						{
							if (genLevel(gen) != 0)
							{
								enemy = true;
								enemyRect.top = pos.y - 50;;
								enemyRect.left = pos.x + offsetXEnemy(gen);
								enemyObj.rect = enemyRect;
								level.addObjectT(enemyObj);
								enemyCount--;
							}
						}

						pos = sf::Vector2f(pos.x + platTexture.plat1->getSize().x, pos.y);
					}
					break;
				case 2:
					for (int ñ = 0; ñ < count; ñ++)
					{
						objectTRect.top = pos.y;
						objectTRect.left = pos.x;
						platformObj.name = "solid";
						platformSprite.setPosition(pos);
						platformSprite.setTexture(*platTexture.plat2);
						platformObj.sprite = platformSprite;
						objectTRect.height = platformObj.sprite.getGlobalBounds().height;
						objectTRect.width = platformObj.sprite.getGlobalBounds().width;
						platformObj.rect = objectTRect;
						platforms.push_back(platformObj);
						ObjectT border;
						objectTRect.height = height;
						objectTRect.width = 1;
						objectTRect.top = 0;
						objectTRect.left = 0;
						border.rect = objectTRect;
						border.name = "solid";
						level.addObjectT(border);
						objectTRect.top = 0;
						objectTRect.left = width - 1;
						border.rect = objectTRect;
						level.addObjectT(border);
						int abilities = genAbility(gen);
						for (int ab = 0; ab < abilities; ab++)
						{
							abilityRect.left = pos.x + offsetXAbility(gen);
							abilityRect.top = pos.y - 20 - offsetYAbility(gen);
							abilityObj.rect = abilityRect;
							level.addObjectT(abilityObj);
						}

						int plants = genPlant(gen);
						switch (genPlat(gen))
						{
						case 1:
							for (int pl = 0; pl < plants; pl++)
							{
								plantSprite.setTexture(*platTexture.plant1);
								plantSprite.setPosition(pos.x + offsetXAbility(gen), pos.y - platTexture.plant1->getSize().y + 5);
								plantObj.sprite = plantSprite;
								level.addObjectT(plantObj);
							}
							break;
						case 2:
							for (int pl = 0; pl < plants; pl++)
							{
								plantSprite.setTexture(*platTexture.plant2);
								plantSprite.setPosition(pos.x + offsetXAbility(gen), pos.y - platTexture.plant2->getSize().y + 5);
								plantObj.sprite = plantSprite;
								level.addObjectT(plantObj);
							}
							break;
						case 3:
							for (int pl = 0; pl < plants; pl++)
							{
								plantSprite.setTexture(*platTexture.plant3);
								plantSprite.setPosition(pos.x + offsetXAbility(gen), pos.y - platTexture.plant3->getSize().y + 5);
								plantObj.sprite = plantSprite;
								level.addObjectT(plantObj);
							}
							break;
						default:
							break;
						}

						if (enemyCount > 0 && !enemy)
						{
							if (genLevel(gen) != 0)
							{
								enemy = true;
								enemyRect.top = pos.y - 50;;
								enemyRect.left = pos.x + offsetXEnemy(gen);
								enemyObj.rect = enemyRect;
								level.addObjectT(enemyObj);
								enemyCount--;
							}
						}

						pos = sf::Vector2f(pos.x + platTexture.plat2->getSize().x, pos.y);
					}
					break;
				case 3:
					for (int ñ = 0; ñ < count; ñ++)
					{
						objectTRect.top = pos.y;
						objectTRect.left = pos.x;

						platformObj.name = "solid";
						platformSprite.setPosition(pos);
						platformSprite.setTexture(*platTexture.plat3);
						platformObj.sprite = platformSprite;
						objectTRect.height = platformObj.sprite.getGlobalBounds().height;
						objectTRect.width = platformObj.sprite.getGlobalBounds().width;
						platformObj.rect = objectTRect;
						platforms.push_back(platformObj);

						int abilities = genAbility(gen);
						for (int ab = 0; ab < abilities; ab++)
						{
							abilityRect.left = pos.x + offsetXAbility(gen);
							abilityRect.top = pos.y - 20 - offsetYAbility(gen);
							abilityObj.rect = abilityRect;
							level.addObjectT(abilityObj);
						}

						int plants = genPlant(gen);
						

						if (enemyCount > 0 && !enemy)
						{
							if (genLevel(gen) != 0)
							{
								enemy = true;
								enemyRect.top = pos.y - 50;;
								enemyRect.left = pos.x + offsetXEnemy(gen);
								enemyObj.rect = enemyRect;
								level.addObjectT(enemyObj);
								enemyCount--;
							}
						}

						pos = sf::Vector2f(pos.x + platTexture.plat3->getSize().x, pos.y);
					}

					break;
				default:
					break;
				}
				for (auto it : platforms)
				{
					level.addObjectT(it);
				}

			}
		}
	}
	ObjectT playerObj;
	sf::Rect <float> objectTRect;
	objectTRect.top = level.GetObjectT("solid")->rect.top - 50;
	objectTRect.left = level.GetObjectT("solid")->rect.left+60;
	objectTRect.height = 40;
	objectTRect.width = 20;
	playerObj.name = "player";
	playerObj.rect = objectTRect;
	level.addObjectT(playerObj);

	ObjectT dieObj;
	objectTRect.top =height-2;
	objectTRect.left = 0;
	objectTRect.height = 2;
	objectTRect.width = width;
	dieObj.name = "die";
	dieObj.rect = objectTRect;
	level.addObjectT(dieObj);

	ObjectT border;
	objectTRect.height = height;
	objectTRect.width = 1;
	objectTRect.top = 0;
	objectTRect.left = 0;
	border.rect = objectTRect;
	border.name = "solid";
	level.addObjectT(border);
	objectTRect.top = 0;
	objectTRect.left = width - 1;
	border.rect = objectTRect;
	level.addObjectT(border);
	return &level;
}

