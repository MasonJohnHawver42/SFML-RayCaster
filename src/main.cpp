#include "Camera/camera.cpp"

int main(int argc, char const *argv[]) {
  Grid<Wall> * map = new Grid<Wall>(8, 8);
  World * world = new World(map);

  for (int i = 0; i < world->getMap()->getRows(); i++)
  {
    world->addWall(new Vector<int>(0, i));
    world->addWall(new Vector<int>(world->getMap()->getCols() - 1, i));
  }

  for (int i = 0; i < world->getMap()->getCols(); i++)
  {
    world->addWall(new Vector<int>(i, 0));
    world->addWall(new Vector<int>(i, world->getMap()->getRows() - 1));
  }

  world->addWall(new Vector<int>(2, 1));
  world->addWall(new Vector<int>(1, 6));
  world->addWall(new Vector<int>(5, 2));
  world->addWall(new Vector<int>(5, 3));
  world->addWall(new Vector<int>(4, 5));
  world->addWall(new Vector<int>(5, 5));
  world->addWall(new Vector<int>(6, 5));


  world->getMap()->toString();

  Camera * cam = new Camera(world, new Vector<double>(1, 1), M_PI/2);

  sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(1800, 1000), "TEST");

  while (window->isOpen())
    {
        sf::Event event;

        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();

                break;
            }
        }
        window->clear();

        cam->display(900, window);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { cam->moveForward(.005); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { cam->moveBackward(.005); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { cam->turn(M_PI/-1600); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { cam->turn(M_PI/1600); }

        window->display();
    }
}
