#ifndef VECTOR_OPERATORS_H
#define VECTOR_OPERATORS_H
#include "constants.h"

static class VectorOperations
{
public:
	static sf::Vector2f ReductComponentsToOne(sf::Vector2f);
	static sf::Vector2f ReductToLength(sf::Vector2f, float);
	static float VectorToRotation(sf::Vector2f);
	static float GetLength(sf::Vector2f);
	static float AngleBetweenVectors(sf::Vector2f, sf::Vector2f);
	static float Distance(sf::Vector2f, sf::Vector2f);
};
#endif VECTOR_OPERATORS_H
