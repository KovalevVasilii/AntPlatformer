#ifndef VIEW_H
#define VIEW_H
#include "SFML\Graphics.hpp"
		sf::View view;
		void setPlayerCoordinateForView(float x, float y) {
			float tempX = x; float tempY = y;
			if (y > 1600) tempY = 700;

			view.setCenter(tempX, tempY);
		}
#endif VIEW_H

