#include <math.h>

class Vector
{
public:
  double x;
  double y;

  Vector()
  {
    x = 0;
    y = 0;
  }

  Vector(int x1, int y1)
  {
    x = x1;
    y = y1;
  }

  void add(Vector other)
  {
    x += other.x;
    y += other.y;
  }

  void sub(Vector other)
  {
    x -= other.x;
    y -= other.y;
  }

  void mult(double n)
  {
    x *= n;
    y *= n;
  }

  void perp()
  {
    double temp = x;
    x = y * -1;
    y = temp;
  }

  double dis(Vector other)
  {
    return sqrt(pow((x - other.x), 2) + pow((y - other.y), 2));
  }

  void turn(double angle)
  {
    double new_x = (x * cos(angle)) - (y * sin(angle));
    double new_y = (x * sin(angle)) + (y * cos(angle));

    x = new_x;
    y = new_y;
  }


};
