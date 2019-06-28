#include "intersection.cpp"

class Actor {
protected:
  Vector<double> * pos;
  Vector<double> * dir;

  double size; // radius

  sf::Texture texture;

  World * world;
public:
  //dir is in rads
  Actor(Vector<double> * p, double dir)
  {
    pos = p;
    setDir(dir);

    texture = *new sf::Texture();
    sf::Image blank;
    blank.create(1, 1, *new sf::Color(255, 255, 255));
    texture.loadFromImage(blank);

    size = 1;
  }

  void setWorld(World * w);
  void removeSelfFromWorld();

  World * getWorld();

  Vector<double> * getPos();
  Vector<double> * getDir();

  double getSize();

  sf::Texture getTexture();

  void setTexture(sf::Texture t);

  void moveTo(Vector<double> newPos);
  void move(Vector<double> offset);

  void moveForward(double mag);
  void moveBackward(double mag);

  void strafe(double mag);

  void setDir(double rad);

  void turn(double rad);

  virtual void act() {}

  Intersection * castRay(double rad);
};

void Actor::setWorld(World * w) { world = w; }
void Actor::removeSelfFromWorld() {
  if(world != nullptr)
  {
    world->removeActor(this);
    world = nullptr;
  }
}

World * Actor::getWorld() { return world; }


Vector<double> * Actor::getPos() { return pos; }
Vector<double> * Actor::getDir() { return dir; }

double Actor::getSize() { return size; }

sf::Texture Actor::getTexture() { return texture; }

void Actor::setTexture(sf::Texture t) { texture = t; }

void Actor::moveTo(Vector<double> newPos) {
  double x, y;
  x = newPos.getX();
  y = newPos.getY();
  if(1)//!world->getMap()->isOcupied(*new Vector<int>((int)x, (int)y)))
  {
    pos = new Vector<double>(x, y);
  }
}

void Actor::move(Vector<double> offset) {
  Vector<double> p = *pos;
  p.add(offset);
  moveTo(p);
}

void Actor::moveForward(double mag) {
  Vector<double> d = *dir;
  d.mult(mag);
  move(d);
}

void Actor::moveBackward(double mag) {
  Vector<double> d = *dir;
  d.mult(mag * -1);
  move(d);
}

void Actor::strafe(double mag) {
  Vector<double> d = *dir;
  d.perp();
  d.mult(mag);
  move(d);
}

void Actor::setDir(double rad) {
  dir = Vector<double>::radianToVector(rad);
}

void Actor::turn(double rad) {
  dir->turn(rad);
}

Intersection * Actor::castRay(double rad)
{
  Vector<double> * rayDir = Vector<double>::radianToVector(rad);

  Vector<int> * gridPos;

  double x;
  double y;

  int yFlip;
  Vector<double> * rayYPos;
  Vector<double> * rayYInc;


  if (rayDir->getX() != 0)
  {
    yFlip = (int) (rayDir->getX() / abs(rayDir->getX()));

    x = ((int) pos->getX()) + ((yFlip + 1) / 2.0);
    y = pos->getY() + ((x - pos->getX()) * tan(rad));

    rayYPos = new Vector<double>(x, y);

    rayYInc = new Vector<double>(yFlip, yFlip * tan(rad));
  }

  int xFlip;
  Vector<double> * rayXPos;
  Vector<double> * rayXInc;

  if (rayDir->getY() != 0)
  {
    xFlip = (int) (rayDir->getY() / abs(rayDir->getY()));

    y = ((int) pos->getY()) + ((xFlip + 1) / 2.0);
    x = pos->getX() + ((y - pos->getY()) / tan(rad));

    rayXPos = new Vector<double>(x, y);

    rayXInc = new Vector<double>(xFlip / tan(rad), xFlip);
  }

  int i = 0;

  while (i < 100)
  {

    if (rayDir->getX() != 0 && rayXPos->getDis(*pos) > rayYPos->getDis(*pos))
    {
      gridPos = new Vector<int>((int)(rayYPos->getX()) - ((yFlip - 1) / -2), (int)(rayYPos->getY()));

      //if(!world->getMap()->isValid(*gridPos)) { break; }
      if(world->getMap()->isOcupied(*gridPos)) { return new Intersection(rayYPos, gridPos, abs((rayYPos->getX() - gridPos->getX()) - (rayYPos->getY() - floor(rayYPos->getY())))); }

      rayYPos->add(*rayYInc);
    }

    else
    {
      gridPos = new Vector<int>((int) rayXPos->getX(), ((int) rayXPos->getY()) - ((xFlip - 1) / -2));
      //if(!world->getMap()->isValid(*gridPos)) { break; }
      Intersection * inter = new Intersection(rayXPos, gridPos, abs((1 - (rayXPos->getY() - gridPos->getY())) - (rayXPos->getX() - floor(rayXPos->getX()))));

      if(world->getMap()->isOcupied(*gridPos)) {
        return inter;
      }
      rayXPos->add(*rayXInc);
    }

    i++;
  }

  return new Intersection();
}
