#include "MapEditor/mapEditor.cpp"
#include "Actor/bullet.cpp"

#include <ctime>

int main(int argc, char const *argv[]) {

  Grid<Wall> * map = new Grid<Wall>(20, 20);
  World * world = new World(map);

  Actor * barrel = new Actor(new Vector<double>(3.5, 3.5), 0);
  Actor * barrel2 = new Actor(new Vector<double>(10.5, 10.5), 0);

  sf::Texture barrelTexture;
  barrelTexture.loadFromFile("../assets/ActorSprites/barrel.png");

  barrel->setTexture(barrelTexture);
  barrel2->setTexture(barrelTexture);

  world->addActor(barrel);
  world->addActor(barrel2);

  sf::Texture wallTexture;
  wallTexture.loadFromFile("../assets/walls/stoneWall.jpg");

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

  //world->addWall(new Vector<int>(2, 1), wallTexture);
  //world->addWall(new Vector<int>(1, 6), wallTexture);
  //world->addWall(new Vector<int>(5, 2), wallTexture);
  //world->addWall(new Vector<int>(5, 3), wallTexture);
  //world->addWall(new Vector<int>(4, 5), wallTexture);
  //world->addWall(new Vector<int>(5, 5), wallTexture);
  //world->addWall(new Vector<int>(6, 5), wallTexture);


  //world->getMap()->toString();

  Camera * cam = new Camera(world, new Vector<double>(3.5, 3.5), M_PI/2);

  sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(800, 600), "Ray Caster Engine V2");

  MapEditor * editor = new MapEditor(world);

  editor->edit(window);

  Vector<double> * pos = new Vector<double>(-5, -5);

  sf::Vector2i mp = sf::Mouse::getPosition(*window);

  int origon = window->getSize().x / 2;

  window->setMouseCursorVisible(false);

  while (window->isOpen())
    {

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window->close(); }
        }

        window->clear(*new sf::Color(112, 112, 112));

        sf::RectangleShape rect = *new sf::RectangleShape(*new sf::Vector2f(window->getSize().x, window->getSize().y / 2.0));
        rect.setFillColor(*new sf::Color(26, 26, 26));
        window->draw(rect);

        cam->display(800, window);

        double mag = .1;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { cam->moveForward(mag); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { cam->moveBackward(mag); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { cam->strafe(mag); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { cam->strafe(-1 * mag); }

        mp = sf::Mouse::getPosition(*window);

        double disToPP = (window->getSize().x / 2.0) / tan(cam->getFov() / 2);

        cam->turn(atan((mp.x - origon) / disToPP));

        origon = window->getSize().x / 2;

        sf::Mouse::setPosition(*new sf::Vector2i(window->getSize().x / 2, window->getSize().y / 2), *window);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window->close(); }

        window->display();

        for(int i = 0; i < world->numActors(); i++)
        {
          world->getActor(i)->act();
        }
    }
}
