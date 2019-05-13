#include "manager.cpp"

int main(int argc, char const *argv[]) {

  Player * p = new Player(* new Vector(4, 4));

  Map * map = new Map(p, 8, 8);

  map->addWall(2, 1);
  map->addWall(1, 6);
  map->addWall(5, 2);
  map->addWall(5, 3);
  map->addWall(4, 5);
  map->addWall(5, 5);
  map->addWall(6, 5);


  GameManager * test = new GameManager(map);

  test->run();

  return 0;
}
