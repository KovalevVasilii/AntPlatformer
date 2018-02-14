#include <iostream>
#include "Level.h"
#include "TinyXML\tinyxml.h"
#include <vector>

int ObjectT::GetPropertyInt(std::string name)
{
	return atoi(properties[name].c_str());
}

float ObjectT::GetPropertyFloat(std::string name)
{
	return strtod(properties[name].c_str(), NULL);
}

std::string ObjectT::GetPropertyString(std::string name)
{
	return properties[name];
}

bool Level::LoadFromFile(std::string filename)
{
	TiXmlDocument levelFile(filename.c_str());

	if (!levelFile.LoadFile())
	{
		std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
		return false;
	}

	// работаем с контейнером map
	TiXmlElement *map;
	map = levelFile.FirstChildElement("map");

	// пример карты: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">
	width = atoi(map->Attribute("width"));//извлекаем из нашей карты ее свойства
	height = atoi(map->Attribute("height"));//те свойства, которые задавали при работе в 
	tileWidth = atoi(map->Attribute("tilewidth"));//тайлмап редакторе
	tileHeight = atoi(map->Attribute("tileheight"));
	tileWidth = 20;
	tileHeight = 20;
	// Берем описание тайлсета и идентификатор первого тайла
	TiXmlElement *tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	// source - путь до картинки в контейнере image
	TiXmlElement *image;
	image = tilesetElement->FirstChildElement("image");
	std::string imagepath = image->Attribute("source");

	// пытаемся загрузить тайлсет
	sf::Image img;

	if (!img.loadFromFile(imagepath))
	{
		std::cout << "Failed to load tile sheet." << std::endl;
		return false;
	}


	img.createMaskFromColor(sf::Color(255, 255, 255));
	tilesetImage.loadFromImage(img);
	tilesetImage.setSmooth(false);

	int columns = tilesetImage.getSize().x / tileWidth;
	int rows = tilesetImage.getSize().y / tileHeight;

	std::vector<sf::Rect<int>> subRects;

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
		{
			sf::Rect<int> rect;

			rect.top = y * tileHeight;
			rect.height = tileHeight;
			rect.left = x * tileWidth;
			rect.width = tileWidth;

			subRects.push_back(rect);
		}

	TiXmlElement *layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		Layer layer;

		
		if (layerElement->Attribute("opacity") != NULL)
		{
			float opacity = strtod(layerElement->Attribute("opacity"), NULL);
			layer.opacity = 255 * opacity;
		}
		else
		{
			layer.opacity = 255;
		}

		TiXmlElement *layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");

		if (layerDataElement == NULL)
		{
			std::cout << "Bad map. No layer information found." << std::endl;
		}

		const char* tileElement;
		tileElement = (layerDataElement->GetText());
		std::string str(tileElement);
		int x = 0;
		int y = 0;
		std::vector<std::string> commands;
		std::string buffer = "";     
		for (int i = 0; i < str.size(); i++) {
			if (str[i] != ',') {     
				buffer += str[i];
			}
			else {
				commands.push_back(buffer);
				buffer = "";
			}
		}
		for (auto i=0;i<commands.size();i++)
		{
			
			int tileGID;
			if (commands[i].size()>5)
			{
				tileGID = 100;
			}
			else
			{
				tileGID = std::stoi(commands[i]);
			}
			int subRectToUse = tileGID - firstTileID;

			if (subRectToUse >= 0)
			{
				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(x*tileWidth, y*tileWidth);
				sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

				layer.tiles.push_back(sprite);
			}

			x++;
			if (x >= width)
			{
				x = 0;
				y++;
				if (y >= height)
					y = 0;
			}
		}

		
		layers.push_back(layer);

		layerElement = layerElement->NextSiblingElement("layer");
	}

	TiXmlElement *objectTGroupElement;


	if (map->FirstChildElement("objectgroup") != NULL)
	{
		objectTGroupElement = map->FirstChildElement("objectgroup");
		while (objectTGroupElement)
		{

			TiXmlElement *objectTElement;
			objectTElement = objectTGroupElement->FirstChildElement("object");

			while (objectTElement)
			{

				std::string objectTType;
				if (objectTElement->Attribute("type") != NULL)
				{
					objectTType = objectTElement->Attribute("type");
				}
				std::string objectTName;
				if (objectTElement->Attribute("name") != NULL)
				{
					objectTName = objectTElement->Attribute("name");
				}
				int x = atoi(objectTElement->Attribute("x"));
				int y = atoi(objectTElement->Attribute("y"));

				int width, height;

				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
				sprite.setPosition(x, y);

				if (objectTElement->Attribute("width") != NULL)
				{
					width = atoi(objectTElement->Attribute("width"));
					height = atoi(objectTElement->Attribute("height"));
				}
				else
				{
					width = subRects[atoi(objectTElement->Attribute("gid")) - firstTileID].width;
					height = subRects[atoi(objectTElement->Attribute("gid")) - firstTileID].height;
					sprite.setTextureRect(subRects[atoi(objectTElement->Attribute("gid")) - firstTileID]);
				}

				ObjectT objectT;
				objectT.name = objectTName;
				objectT.type = objectTType;
				objectT.sprite = sprite;

				sf::Rect <float> objectTRect;
				objectTRect.top = y;
				objectTRect.left = x;
				objectTRect.height = height;
				objectTRect.width = width;
				objectT.rect = objectTRect;

				TiXmlElement *properties;
				properties = objectTElement->FirstChildElement("properties");
				if (properties != NULL)
				{
					TiXmlElement *prop;
					prop = properties->FirstChildElement("property");
					if (prop != NULL)
					{
						while (prop)
						{
							std::string propertyName = prop->Attribute("name");
							std::string propertyValue = prop->Attribute("value");

							objectT.properties[propertyName] = propertyValue;

							prop = prop->NextSiblingElement("property");
						}
					}
				}


				objectTs.push_back(objectT);

				objectTElement = objectTElement->NextSiblingElement("object");
			}
			objectTGroupElement = objectTGroupElement->NextSiblingElement("objectgroup");
		}
	}
	else
	{
		std::cout << "No objectT layers found..." << std::endl;
	}

	return true;
}

ObjectT Level::GetObjectT(std::string name)
{
	for (int i = 0; i < objectTs.size(); i++)
		if (objectTs[i].name == name)
			return objectTs[i];
}

std::vector<ObjectT> Level::GetObjectTs(std::string name)
{
	std::vector<ObjectT> vec;
	for (int i = 0; i < objectTs.size(); i++)
		if (objectTs[i].name == name)
			vec.push_back(objectTs[i]);

	return vec;
}


std::vector<ObjectT> Level::GetAllObjectTs()
{
	return objectTs;
};


sf::Vector2i Level::GetTileSize()
{
	return sf::Vector2i(tileWidth, tileHeight);
}

void Level::Draw(sf::RenderWindow &window)
{
	for (int layer = 0; layer < layers.size(); layer++)
	{
		for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
		{
			window.draw(layers[layer].tiles[tile]); 
		}
	}
}
