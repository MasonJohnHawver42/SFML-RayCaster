#include "wall.cpp"
#include "player.cpp"

class Map
{
public:
  Tile **tiles;
  int width;
  int height;

  Player * player;

  Map()
  {
    tiles = new Tile* [0];

    width = 0;
    height = 0;
  }

  Map(Player * p, int w, int h)
  {
    player = p;
    tiles = new Tile* [h];

    for(int i = 0; i<h; i++)
    {
      tiles[i] = new Tile[w];

      if(i == 0 || i == h - 1)
      {
        for (int j = 0; j < w; j++) { tiles[i][j] = * new Wall(); }
      }

      else
      {
        tiles[i][0] = * new Wall;
        tiles[i][w - 1] = * new Wall;
      }
    }

    height = h;
    width = w;
  }

  void addWall(int x, int y)
  {
    tiles[x][y] = * new Wall();
  }

  bool hit(int x, int y)
  {
    return !tiles[y][x].isPassable();
  }

  void update(char key)
  {
    player->update(key);
  }

  void toString()
  {
    for(int i = 0; i < height; i++)
    {
      for(int j = 0; j < width; j++)
      {
        std::cout << tiles[i][j].toString();
      }

      std::cout << '\n';
    }
  }
};
