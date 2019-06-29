#include "../Actor/actor.cpp"
#include <unistd.h>

double dosPi = 2 * M_PI;


class Camera : public Actor{
public:
  Camera(World * w, Vector<double> * p, double dir)
  : Actor(p, dir)
  {
    world = w;
  }

  virtual void display(sf::RenderWindow * window) {}
};
