#include "intersection.cpp"

class Actor {
protected:
  Vector<double> * pos;
  Vector<double> * dir;

  Grid<Wall> * grid;
public:
  //dir is in rads
  Actor(Vector<double> * p, double dir)
  {
    pos = p;
    setDir(dir);
  }

  void setGrid(Grid<Wall> * g);
  Grid<Wall> * getGrid();

  Vector<double> * getLocation();
  Vector<double> * getDirection();

  void moveTo(Vector<double> * newPos);
  void move(Vector<double> offset);

  void moveForward(double mag);
  void moveBackward(double mag);
  void setDir(double rad);

  void turn(double rad);

  void act();

  Intersection * castRay(double rad);
};

void Actor::setGrid(Grid<Wall> * g) { grid = g;}
Grid<Wall> * Actor::getGrid() { return grid; }


Vector<double> * Actor::getLocation() { return pos; }
Vector<double> * Actor::getDirection() { return dir; }

void Actor::moveTo(Vector<double> * newPos) {
  pos = newPos;
}

void Actor::move(Vector<double> offset) {
  pos->add(offset);
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

void Actor::setDir(double rad) {
  dir = Vector<double>::radianToVector(rad);
}

void Actor::turn(double rad) {
  dir->turn(rad);
}

void Actor::act() {}

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

  while (i < 10000)
  {

    if (rayDir->getX() != 0 && rayXPos->getDis(*pos) > rayYPos->getDis(*pos))
    {
      gridPos = new Vector<int>((int)(rayYPos->getX()) - ((yFlip - 1) / -2), (int)(rayYPos->getY()));

      if(!grid->isValid(*gridPos)) { break; }
      if(grid->isOcupied(*gridPos)) { return new Intersection(rayYPos, gridPos, rayYPos->getY() - floor(rayYPos->getY())); }

      rayYPos->add(*rayYInc);
    }

    else
    {
      gridPos = new Vector<int>((int) rayXPos->getX(), ((int) rayXPos->getY()) - ((xFlip - 1) / -2));

      if(!grid->isValid(*gridPos)) { break; }
      if(grid->isOcupied(*gridPos)) { return new Intersection(rayXPos, gridPos, rayXPos->getX() - floor(rayXPos->getX())); }

      rayXPos->add(*rayXInc);
    }
  }

  return new Intersection();
}
