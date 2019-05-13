#include "Vector.cpp"
#include <string>

class Player
{
public:
  Vector pos;
  Vector dir;
  Vector vel;

  Player(Vector p)
  {
    pos = p;
    dir = * new Vector(1, 0);
    vel = * new Vector(0, 0);
  }

  void update(char key)
  {
    ioUpdate(key);
  }

  void turn(double a)
  {
    dir.turn(a);
  }

  void ioUpdate(char key)
  {
    switch(tolower(key))
    {
      case 'w':
      vel = dir;
      vel.mult(.05);
      pos.add(vel);
      break;

      case 's':
      vel = dir;
      vel.mult(.05);
      pos.sub(vel);
      break;

      case 'a':
      turn(-M_PI / 90);
      break;

      case 'd':
      turn(M_PI / 90);

      break;
  }
  }


  std::string toString()
  {
    return "( " + std::to_string(dir.x) + ", " + std::to_string(dir.y) + " )";
  }

};
