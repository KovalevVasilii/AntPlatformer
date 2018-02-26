#ifndef VIEW_H
#define VIEW_H
#include "SFML\Graphics.hpp"
sf::View view;

		void setPlayerCoordinateForView(float x, float y) {
			float tempX = x; float tempY = y;
			//if (y > 700) tempY = 700;
			view.setSize(900, 700);
			view.setCenter(tempX, tempY);
		}
#endif VIEW_H

