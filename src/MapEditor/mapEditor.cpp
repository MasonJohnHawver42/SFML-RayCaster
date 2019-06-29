#include "../Camera/camera3d.cpp"

class MapEditor {
private:
  World * world;

public:
  MapEditor(World * w)
  {
    world = w;
  }

  void displayMap(sf::RenderWindow * window, Vector<double> * pos, double pixelsPerTile);
  void edit(sf::RenderWindow * window);

};

void MapEditor::displayMap(sf::RenderWindow * window, Vector<double> * pos, double pixelsPerTile) {
  window->clear(*new sf::Color(60, 60, 60));

  Vector<int> * gridPos = new Vector<int>((int) pos->getX(), (int) pos->getY());

  sf::RectangleShape * gridLine;

  double border = .1;

  while ((gridPos->getY() - pos->getY()) * pixelsPerTile < window->getSize().y)
  {
    gridPos->setX((int) pos->getX());
    while ((gridPos->getX() - pos->getX()) * pixelsPerTile < window->getSize().x) {
      if(world->getMap()->isOcupied(*gridPos))
      {
        sf::RectangleShape * rect = new sf::RectangleShape(*new sf::Vector2f(pixelsPerTile, pixelsPerTile));
        sf::Sprite wall;
        sf::Texture wallTexture = world->getMap()->get(*gridPos)->getTexture();
        wall.setTexture(wallTexture);

        wall.scale((pixelsPerTile * (1 - (2 * border))) / wall.getTexture()->getSize().x, (pixelsPerTile * (1 - (2 * border))) / wall.getTexture()->getSize().y);

        double x, y;

        x = (gridPos->getX() - pos->getX()) * pixelsPerTile;
        y = (gridPos->getY() - pos->getY()) * pixelsPerTile;

        wall.setPosition(x + (pixelsPerTile * border), y + (pixelsPerTile * border));
        rect->setPosition(x, y);

        rect->setFillColor(*new sf::Color(0, 0, 0));

        window->draw(*rect);
        window->draw(wall);
      }

      else if (world->getMap()->isValid(*gridPos)){
        sf::RectangleShape * rect = new sf::RectangleShape(*new sf::Vector2f(pixelsPerTile, pixelsPerTile));

        double x, y;
        x = (gridPos->getX() - pos->getX()) * pixelsPerTile;
        y = (gridPos->getY() - pos->getY()) * pixelsPerTile;

        rect->setPosition(x, y);
        rect->setFillColor(*new sf::Color(40, 40, 40));

        window->draw(*rect);
      }
      gridLine = new sf::RectangleShape(*new sf::Vector2f(2 * (pixelsPerTile * border), window->getSize().y));

      gridLine->setPosition(((gridPos->getX() - pos->getX()) * pixelsPerTile) - (pixelsPerTile * border), 0);
      gridLine->setFillColor(*new sf::Color(0, 0, 0));
      window->draw(*gridLine);

      gridPos->add(*new Vector<int>(1, 0));
    }

    gridLine = new sf::RectangleShape(*new sf::Vector2f(window->getSize().x, 2 * (pixelsPerTile * border)));

    gridLine->setPosition(0, ((gridPos->getY() - pos->getY()) * pixelsPerTile) - (pixelsPerTile * border));
    gridLine->setFillColor(*new sf::Color(0, 0, 0));
    window->draw(*gridLine);

    gridPos->add(*new Vector<int>(0, 1));
  }
}

void MapEditor::edit(sf::RenderWindow * window) {
  sf::Texture wallTexture;
  wallTexture.loadFromFile("../assets/walls/stoneWall.jpg");

  MapEditor * editor = new MapEditor(world);

  Vector<double> * pos = new Vector<double>(-1, -1);

  double ppt = 50;

  sf::Event event;

  while (window->isOpen())
    {
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window->close();
            else if(event.type == sf::Event::MouseWheelMoved)
            {
                // display number of ticks mouse wheel has moved
                int delta = event.mouseWheel.delta;
                if (delta > 0) { ppt *= 1.05; }
                if (delta < 0) { ppt /= 1.05; }
            }
        }

        ppt = max(14.0, ppt);
        ppt = min(ppt, (double) window->getSize().y * (2/3.0) );

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window->close(); }
        }

        window->clear();

        editor->displayMap(window, pos, floor(ppt));

        sf::Vector2i mp = sf::Mouse::getPosition(*window);
        Vector<double> * mousePos = new Vector<double>(mp.x, mp.y);
        mousePos->div(ppt);
        mousePos->add(*pos);

        Vector<int> * gridPos = new Vector<int>(mousePos->getX(), mousePos->getY());

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
          world->addWall(new Vector<int>(gridPos->getX(), gridPos->getY()), wallTexture);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
          world->removeWall(*gridPos);
        }

        double mag = 10 / ppt;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { pos->add(*new Vector<double>(0, -mag)); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { pos->add(*new Vector<double>(0, mag)); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { pos->add(*new Vector<double>(-mag, 0)); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { pos->add(*new Vector<double>(mag, 0)); }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { return; }

        window->display();

        usleep(10000);
    }
}
