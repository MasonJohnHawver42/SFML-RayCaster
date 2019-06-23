#include "../Actor/actor.cpp"
#include <list>


class World {
private:
  Grid<Wall> * map;
  list<Actor> * actors;


public:
  World()
  {
    map = new Grid<Wall>();
    actors = new list<Actor>();
  }

  World(Grid<Wall> * m)
  {
    map = m;
  }

  void addWall(Vector<int> *loc);
  void addWall(Vector<int> *loc, sf::Texture t);
  void removeWall(Vector<int> loc);

  Grid<Wall> * getMap();

};

void World::addWall(Vector<int> * loc) { map->put(new Wall(loc), *loc); }
void World::addWall(Vector<int> * loc, sf::Texture t) { map->put(new Wall(loc, t), *loc); }
void World::removeWall(Vector<int> loc) { map->put(nullptr, loc); }

Grid<Wall> * World::getMap() { return map; }
