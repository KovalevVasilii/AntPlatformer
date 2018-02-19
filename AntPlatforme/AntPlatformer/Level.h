#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TinyXML/tinyxml.h"

struct ObjectT
{
	int GetPropertyInt(std::string name);
	float GetPropertyFloat(std::string name);
	std::string GetPropertyString(std::string name);

	std::string name;
	std::string type;
	sf::Rect<float> rect;
	std::map<std::string, std::string> properties;

	sf::Sprite sprite;
};

struct Layer
{
	int opacity;
	std::vector<sf::Sprite> tiles;
};

class Level
{
public:
	bool LoadFromFile(std::string filename);
	ObjectT GetObjectT(std::string name);
	std::vector<ObjectT> GetObjectTs(std::string name);
	std::vector<ObjectT>* GetAllObjectTs();
	void Draw(sf::RenderWindow &window);
	sf::Vector2i GetTileSize();

private:
	int width, height, tileWidth, tileHeight;
	int firstTileID;// айди первого тайла
	sf::Rect<float> drawingBounds;//размер части карты которую рисуем
	sf::Texture tilesetImage;//текстура карты
	std::vector<ObjectT> objectTs;
	std::vector<Layer> layers;
};




#endif
