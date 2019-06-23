#include "../World/world.cpp"

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

    fov = M_PI/3;
  }

  void display(int rayCount, sf::RenderWindow * window);
};


void Camera::display(int rayCount, sf::RenderWindow * window) {
  double jump = fov / rayCount;

  double rad = dir->getRad() - (fov / 2);

  double disToPP = (window->getSize().x / 2.0) / tan(fov / 2);

  int sliceWidth = max(1, (int)(window->getSize().x / rayCount));

  double xScale = sliceWidth / 1;

  for(int i = 0; i < rayCount; i++)
  {
    Intersection * inter = castRay(rad);

    if(!inter->getHit()->equals(*new Vector<double>()))
    {
      double dis = pos->getDis(*inter->getHit());
      dis = dis * cos((jump * i) - (fov / 2));

      double sliceHieght = disToPP / dis;

      sf::Sprite wall;
      sf::Texture wallTexture = world->getMap()->get(*(inter->getWall()))->getTexture();

      wall.setTexture(wallTexture);

      double scale = sliceHieght / wall.getTexture()->getSize().y;

      wall.setTextureRect(sf::IntRect((int)(wall.getTexture()->getSize().y * inter->getSlice()), 0, 1, wall.getTexture()->getSize().y));
      wall.setScale(xScale, scale);

      wall.setPosition(sliceWidth * i, (window->getSize().y - sliceHieght) / 2.0);

      int colorG = 255 * (min((double) window->getSize().y, sliceHieght + (window->getSize().y / 2)) / window->getSize().y);

      wall.setColor(*new sf::Color(colorG, colorG, colorG));

      window->draw(wall);
    }


    rad += jump;
  }
}
