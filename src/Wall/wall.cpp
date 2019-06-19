#include "../grid/grid.cpp"

//check

class Wall
{
private:
  Vector<int> * location;

public:
  Wall() { location = new Vector<int>(0, 0); }
  Wall(Vector<int> * loc)
  {
    location = loc;
  }

  Vector<int> * getLocation();
};

Vector<int> * Wall::getLocation() { return location; }
