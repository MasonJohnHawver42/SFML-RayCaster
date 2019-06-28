#include "../vector.cpp"
#include <SFML/Graphics.hpp>

class Wall
{
private:
  Vector<int> * location;
  sf::Texture texture;

public:
  Wall(Vector<int> * loc)
  {
    location = loc;
    texture = *new sf::Texture();
    sf::Image blank;
    blank.create(1, 1, *new sf::Color(255, 255, 255));
    texture.loadFromImage(blank);

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
