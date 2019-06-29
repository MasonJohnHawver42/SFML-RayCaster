#include "camera.cpp"

class Camera3D : public Camera{
private:
  double fov;
  int rayCount;

public:
  Camera3D(World * w, Vector<double> * p, double dir)
  : Camera(w, p, dir)
  {
    fov = M_PI/3;
    rayCount = 400;
  }

  double getFov();
  int getRayCount();

  void setFov(double fov1);
  void setRayout(int rc);

  void display(sf::RenderWindow * window);
};
double Camera3D::getFov() { return fov; }
int Camera3D::getRayCount() { return rayCount; }

void Camera3D::setFov(double fov1) { fov = fov1; }
void Camera3D::setRayout(int rc) { rayCount = rc; }

void Camera3D::display(sf::RenderWindow * window) {
  double jump = fov / rayCount;

  double dirRad = dir->getRad();

  double rad = -1 * (fov / 2);

  double disToPP = (window->getSize().x / 2.0) / tan(fov / 2);

  int sliceWidth = max(1, (int)(window->getSize().x / rayCount));

  double xScale = sliceWidth / 1;

  int i, j;
  double dis;

  double actorDis[world->numActors()];
  double actorFos[world->numActors()];
  double radOffsets[world->numActors()];
  int order[world->numActors()];

  for (i = 0; i < world->numActors(); i++)
  {
    Actor * actor = world->getActor(i);
    dis = pos->getDis(*actor->getPos());
    double fos = atan((actor->getSize() / 2) / dis);

    Vector<double> diff = *(actor->getPos());
    diff.sub(*pos);

    double flip = (((dir->getY() / dir->getX()) * diff.getX()) - (diff.getY())) * (dir->getX() / abs(dir->getX()));
    flip = (flip == 0 ? 1: (-flip / abs(flip)));

    double offset = acos((((actor->getPos()->getX() - pos->getX()) * dir->getX()) + ((actor->getPos()->getY() - pos->getY()) * dir->getY())) / dis);
    offset = flip * offset;

    actorDis[i] = dis;
    actorFos[i] = fos;
    radOffsets[i] = offset;
    order[i] = i;
  }

  double key, key2, key3;
  int key4;

  for (i = 1; i < world->numActors(); i++)
  {
      key = actorDis[i];
      key2 = actorFos[i];
      key3 = radOffsets[i];
      key4 = order[i];
      j = i - 1;

      /* Move elements of arr[0..i-1], that are
      greater than key, to one position ahead
      of their current position */
      while (j >= 0 && actorDis[j] < key)
      {
          actorDis[j + 1] = actorDis[j];
          actorFos[j + 1] = actorFos[j];
          radOffsets[j + 1] = radOffsets[j];
          order[j + 1] = order[j];
          j = j - 1;
      }
      actorDis[j + 1] = key;
      actorFos[j + 1] = key2;
      radOffsets[j + 1] = key3;
      order[j + 1] = key4;

  }

  for(i = 0; i < rayCount; i++)
  {
    Intersection * inter = castRay(dirRad + rad);

    if(!inter->getHit()->equals(*new Vector<double>()))
    {

      dis = pos->getDis(*inter->getHit());

      double sliceHieght = (disToPP / (dis * cos((jump * i) - (fov / 2))));

      sf::Sprite wall;
      sf::Texture wallTexture = world->getMap()->get(*(inter->getWall()))->getTexture();

      wall.setTexture(wallTexture);

      double scale = (sliceHieght) / wall.getTexture()->getSize().y;

      wall.setTextureRect(sf::IntRect((int)(wall.getTexture()->getSize().x * inter->getSlice()), 0, 1, wall.getTexture()->getSize().y));
      wall.setScale(xScale, scale);

      wall.setPosition(sliceWidth * i, (window->getSize().y - sliceHieght) / 2.0);

      int colorG = max(0, (int)(255 * (min((double) window->getSize().y, sliceHieght * 4) / window->getSize().y)));

      wall.setColor(*new sf::Color(colorG, colorG, colorG));

      window->draw(wall);

      for(int j = 0; j < world->numActors(); j++)
      {
        double size = 1;

        double leftMost = radOffsets[j] - actorFos[j];
        double rightMost = radOffsets[j] + actorFos[j];

        if( (leftMost <= rad && rightMost >= rad) & actorDis[j] > .5)
        {
          double slice = actorDis[j] * tan(radOffsets[j] - rad);

          if(dis > sqrt((slice * slice) + (actorDis[j] * actorDis[j])))
          {
            sliceHieght = (disToPP / (actorDis[j] * cos(radOffsets[j])));

            sf::Sprite acter;
            sf::Texture actorTexture = world->getActor(order[j])->getTexture();

            acter.setTexture(actorTexture);

            acter.setTextureRect(sf::IntRect((int)(acter.getTexture()->getSize().x * ((slice + (size / 2)) / size)), 0, 1, acter.getTexture()->getSize().y));
            acter.setScale(xScale, (sliceHieght) / acter.getTexture()->getSize().y);

            acter.setPosition(sliceWidth * i, (window->getSize().y - (sliceHieght)) / 2.0);

            colorG = max(0, (int)(255 * (min((double) window->getSize().y, sliceHieght * 4) / window->getSize().y)));
            acter.setColor(*new sf::Color(colorG, colorG, colorG));

            window->draw(acter);
          }
        }
      }
    }


    rad += jump;
  }
}
