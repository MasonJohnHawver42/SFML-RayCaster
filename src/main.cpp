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

  barrel->addTexture(barrelTexture);
  barrel2->addTexture(barrelTexture);

  barrel->setWorld(world);
  barrel2->setWorld(world);

  Actor * multiDir = new Actor(new Vector<double>(6.5, 8.5), 0);

  sf::Texture number;
  number.loadFromFile("../assets/ActorSprites/numberedSprites/zero.jpg");
  multiDir->addTexture(number);

  number.loadFromFile("../assets/ActorSprites/numberedSprites/one.jpg");
  multiDir->addTexture(number);

  number.loadFromFile("../assets/ActorSprites/numberedSprites/two.jpg");
  multiDir->addTexture(number);

  number.loadFromFile("../assets/ActorSprites/numberedSprites/three.jpg");
  multiDir->addTexture(number);

  number.loadFromFile("../assets/ActorSprites/numberedSprites/four.jpg");
  multiDir->addTexture(number);

  multiDir->setWorld(world);

  sf::Texture wallTexture;
  wallTexture.loadFromFile("../assets/walls/ogWall.jpg");

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

  Camera3D * cam = new Camera3D(world, new Vector<double>(3.5, 3.5), M_PI/2);

  sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(800, 600), "Ray Caster Engine V2");

  MapEditor * editor = new MapEditor(world);

  editor->edit(window);

  Vector<double> * pos = new Vector<double>(-5, -5);

  sf::Vector2i mp = sf::Mouse::getPosition(*window);

  int origon = window->getSize().x / 2;

  window->setMouseCursorVisible(false);

  sf::Texture bulletTexture;
  bulletTexture.loadFromFile("../assets/ActorSprites/bullet.png");

  time_t t = std::time(0);
  long int before = static_cast<long int> (t) - 100;

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

        cam->display(window);

        double mag = .1;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { cam->moveForward(mag); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { cam->moveBackward(mag); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { cam->strafe(mag); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { cam->strafe(-1 * mag); }
        /**
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
          t = std::time(0);
          long int after = static_cast<long int> (t);
          if(after - before > 0)
          {
            before = after;

            Vector<double> * p = new Vector<double>(cam->getPos()->getX(), cam->getPos()->getY());
            double dir = cam->getDir()->getRad();
            Bullet * bill = new Bullet(p, dir);
            bill->setTexture(bulletTexture);
            bill->setWorld(world);
          }
        }
        */


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
