#include <SFML/Graphics.hpp>
namespace lvl
{


	class View
	{
	public:
		void setPlayerCoordinateForView(float x, float y) {
			float tempX = x; float tempY = y;
			if (y > 624) tempY = 624;

			view.setCenter(tempX, tempY);
		}
	private:
		sf::View view;
	};
}
