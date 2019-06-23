#include "Camera/camera.cpp"
#include <ctime>

int main(int argc, char const *argv[]) {

  Grid<Wall> * map = new Grid<Wall>(8, 8);
  World * world = new World(map);

  sf::Texture wallTexture;
  wallTexture.loadFromFile("../assets/walls/brickWall.jpg");

  for (int i = 0; i < world->getMap()->getRows(); i++)
  {
    world->addWall(new Vector<int>(0, i), wallTexture);
    world->addWall(new Vector<int>(world->getMap()->getCols() - 1, i), wallTexture);
  }

  for (int i = 0; i < world->getMap()->getCols(); i++)
  {
    world->addWall(new Vector<int>(i, 0), wallTexture);
    world->addWall(new Vector<int>(i, world->getMap()->getRows() - 1), wallTexture);
  }

  wallTexture.loadFromFile("../assets/walls/wallaa.jpg");

  world->addWall(new Vector<int>(2, 1), wallTexture);
  world->addWall(new Vector<int>(1, 6), wallTexture);
  world->addWall(new Vector<int>(5, 2), wallTexture);
  world->addWall(new Vector<int>(5, 3), wallTexture);
  world->addWall(new Vector<int>(4, 5), wallTexture);
  world->addWall(new Vector<int>(5, 5), wallTexture);
  world->addWall(new Vector<int>(6, 5), wallTexture);


  world->getMap()->toString();

  Camera * cam = new Camera(world, new Vector<double>(1.5, 1.5), M_PI/2);

  sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(800, 600), "TEST");

  while (window->isOpen())
    {

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window->close(); }
        }

        time_t t = std::time(0);
        long int before = static_cast<long int> (t);

        window->clear();

        cam->display(800, window);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { cam->moveForward(.06); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { cam->moveBackward(.06); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { cam->turn(M_PI/-150); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { cam->turn(M_PI/150); }

        window->display();

        t = std::time(0);
        long int after = static_cast<long int> (t);
    }
}
