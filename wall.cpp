#include "tile.cpp"

class Wall : public Tile
{
public:
  Wall()
  : Tile()
  {
    passable = false;
    repr = "#";
  }
};
