#include <iostream>

using namespace std;

class Tile
{
protected:
  bool passable;
  const char* repr;

public:

  Tile()
  {
    passable = true;
    repr = ".";
  }

  bool isPassable() { return passable; }

  const char* toString()
  {
    return repr;
  }
};
