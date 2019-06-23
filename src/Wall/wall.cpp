#include "../grid/grid.cpp"
#include <SFML/Graphics.hpp>

//check

class Wall
{
private:
  Vector<int> * location;
  sf::Texture texture;

public:
  Wall() { location = new Vector<int>(0, 0); }
  Wall(Vector<int> * loc)
  {
    location = loc;
  }
  Wall(Vector<int> * loc, sf::Texture t)
  {
    location = loc;
    texture = t;
  }
  Vector<int> * getLocation();

  void setTexture(sf::Texture t);
  sf::Texture getTexture();

};

Vector<int> * Wall::getLocation() { return location; }

void Wall::setTexture(sf::Texture t) {
  texture = t;
}
sf::Texture Wall::getTexture() {
  return texture;
}
