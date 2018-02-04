#include "VectorOperations.h"

sf::Vector2f VectorOperations::ReductComponentsToOne(sf::Vector2f vector)
{
	sf::Vector2f direction = vector;
	if (direction.x == 0 && direction.y == 0)
		return (sf::Vector2f(0, 0));
	else
	{
		float maxComp = std::max<float>(abs(direction.x), abs(direction.y));
		direction.x = direction.x / maxComp;
		direction.y = direction.y / maxComp;
		return direction;
	}
}

sf::Vector2f VectorOperations::ReductToLength(sf::Vector2f vector, float length)
{
	sf::Vector2f direction = vector;
	float divSum = GetLength(direction);
	divSum = length / divSum;
	direction.x = direction.x * divSum;
	direction.y = direction.y * divSum;
	return direction;
}

float VectorOperations::VectorToRotation(sf::Vector2f direction)
{
	float scalar = direction.x*originDirection.x + direction.y*originDirection.y;
	float lengths = GetLength(originDirection)*GetLength(direction);
	float angle = acos(scalar / lengths) * 180 / (3.14);
	if (direction.y < 0)
		angle += (180 - angle) * 2;
	return angle;
}

float VectorOperations::GetLength(sf::Vector2f vector)
{
	float length = sqrt(abs(vector.x)*abs(vector.x) + abs(vector.y)*abs(vector.y));
	return length;
}

float VectorOperations::AngleBetweenVectors(sf::Vector2f f, sf::Vector2f s)
{
	float x1 = f.x;
	float y1 = f.y;
	float x2 = s.x;
	float y2 = s.y;
	float t = (x1*x2 + y1 * y2) / (sqrt((double)x1*x1 + y1 * y1)*sqrt((double)x2*x2 + y2 * y2));
	if (t<-1) t = -1;
	else if (t > 1) t = 1;
	return acos(t) * 180 / (3.14);
}

float VectorOperations::Distance(sf::Vector2f f, sf::Vector2f s)
{
	float dist = sqrt((f.x - s.x)*(f.x - s.x) + (f.y - s.y)*(f.y - s.y));
	return dist;
}
