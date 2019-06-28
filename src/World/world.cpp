#include "../grid/grid.cpp"
#include <vector>

using namespace std;

class Actor;

class World {
private:
  Grid<Wall> * map;
  std::vector<Actor*> actors;


public:
  World()
  {
    map = new Grid<Wall>();
  }

  World(Grid<Wall> * m)
  {
    map = m;
  }

  void addWall(Vector<int> *loc);
  void addWall(Vector<int> *loc, sf::Texture t);
  void removeWall(Vector<int> loc);

  void addActor(Actor * actor);
  void removeActor(Actor * actor);

  int numActors();

  Actor * getActor(int index);

  Grid<Wall> * getMap();

};

void World::addWall(Vector<int> * loc) { map->put(new Wall(loc), *loc); }
void World::addWall(Vector<int> * loc, sf::Texture t) { map->put(new Wall(loc, t), *loc); }
void World::removeWall(Vector<int> loc) { map->put(nullptr, loc); }

void World::addActor(Actor * actor) { actors.push_back(actor); }
void World::removeActor(Actor * actor) {
  for (int i = 0; i < actors.size(); i++) {
    if(actors[i] == actor) {
      actors.erase(actors.begin() + i);
    }
  }
}

int World::numActors() { return actors.size(); }

Actor * World::getActor(int index) { return actors[index]; }

Grid<Wall> * World::getMap() { return map; }
