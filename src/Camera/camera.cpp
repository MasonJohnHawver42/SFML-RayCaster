#include "../World/world.cpp"
#include "SFML/Graphics.hpp"

class Camera : public Actor{
private:
  World * world;

  double fov;

public:
  // dir is in rads
  Camera(World * w, Vector<double> * p, double dir)
  : Actor(p, dir)
  {
    world = w;
    setGrid(world->getMap());

    fov = M_PI / 3;
  }

  void display(int rayCount, sf::RenderWindow * window);
};


void Camera::display(int rayCount, sf::RenderWindow * window) {
  double jump = fov / rayCount;

  double rad = dir->getRad() - (fov / 2);

  double disToPP = (window->getSize().x / 2.0) / tan(fov / 2);

  int sliceWidth = max(1, (int)(window->getSize().x / rayCount));

  for(int i = 0; i < rayCount; i++)
  {
    Vector<double> inter = castRay(rad);

    //inter.toString();

    double dis = pos->getDis(inter);
    dis = dis * cos((jump * i) - (fov / 2));

    double sliceHieght = disToPP / dis;

    sf::RectangleShape rect(sf::Vector2f(sliceWidth, (int)sliceHieght));
    rect.setPosition(sliceWidth * i, (window->getSize().y - sliceHieght) / 2.0);


    int colorG = (int)((min(sliceHieght, (double)window->getSize().y) / window->getSize().y) * 255);
    //if((inter.getX() - ((int)(inter.getX()))) < .2) {colorG = 200;}
    //if((inter.getY() - ((int)(inter.getY()))) < .2) {colorG = 150;}
    rect.setFillColor(*new sf::Color(colorG, colorG, colorG));

    window->draw(rect);

    rad += jump;
  }
}
