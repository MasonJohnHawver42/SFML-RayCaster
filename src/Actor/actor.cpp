#include "../Wall/wall.cpp"

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

  //radians
  Vector<double> castRay(double rad);
};

void Actor::setGrid(Grid<Wall> * g) { grid = g;}
Grid<Wall> * Actor::getGrid() { return grid; }


Vector<double> *Actor::getLocation() { return pos; }
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

Vector<double> Actor::castRay(double rad) {
  Vector<double> d = *Vector<double>::radianToVector(rad);

  int xFlip = (int) (d.getX() / abs(d.getX()));
  int yFlip = (int) (d.getY() / abs(d.getY()));

  double xLength = 1 / d.getX();
  double yLength = 1 / d.getY();

  Vector<double> xPos = d;
  xPos.mult(xLength * ((floor(pos->getX()) + ((xFlip + 1) / 2)) - pos->getX()));
  xPos.add(*pos);

  //xPos.toString();

  Vector<double> yPos = d;
  yPos.mult(yLength * ((floor(pos->getY()) + ((yFlip + 1) / 2)) - pos->getY()));
  yPos.add(*pos);

  //yPos.toString();

  Vector<double> xJump = d;
  xJump.mult(xLength * xFlip);

  Vector<double> yJump = d;
  yJump.mult(yLength * yFlip);

  int x;
  int y;

  int i = 0;

  while (true)
  {
    double xDis = abs(pos->getX() - xPos.getX()) + abs(pos->getY() - xPos.getY());
    double yDis = abs(pos->getX() - yPos.getX()) + abs(pos->getY() - yPos.getY());

    if(isnan(yDis) || xDis < yDis)
    {

      x = xPos.getX() - ((xFlip - 1) / -2);
      y = floor(xPos.getY());

      Vector<int> xtPos = *new Vector<int>(x, y);
      if(!grid->isValid(xtPos)) { break; }

      if(grid->isOcupied(xtPos))
      {
        //xtPos.toString();
        return xPos;
      }

      xPos.add(xJump);
    }

    else
    {
      x = floor(yPos.getX());
      y = yPos.getY() - ((yFlip - 1) / -2);

      Vector<int> ytPos = *new Vector<int>(x, y);
      if(!grid->isValid(ytPos)) { break; }



      if(grid->isOcupied(ytPos))
      {
          //ytPos.toString();
          return yPos;
      }

      yPos.add(yJump);
    }

    i++;
  }
}
