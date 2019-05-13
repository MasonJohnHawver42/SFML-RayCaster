#include "map.cpp"

class Camera
{
public:
  Map * map;

  Vector * dir;
  Vector * pos;

  double fov;

  Camera(Map * m)
  {
    map = m;

    dir = &map->player->dir;
    pos = &map->player->pos;

    fov = 75;
  }

  void setDir(Vector * d)
  {
    dir = d;
  }

  void setPos(Vector * p)
  {
    pos = p;
  }



  double castRay(Vector * d)
  {
    int xFlip = (int) (d->x / abs(d->x));
    int yFlip = (int) (d->y / abs(d->y));



    double xLength = 1 / d->x;
    double yLength = 1 / d->y;

    Vector xPos = *d;
    xPos.mult(xLength * ((floor(pos->x) + ((xFlip + 1) / 2)) - pos->x));
    xPos.add(*pos);

    Vector yPos = *d;
    yPos.mult(yLength * ((floor(pos->y) + ((yFlip + 1) / 2)) - pos->y));
    yPos.add(*pos);

    Vector xJump = * d;
    xJump.mult(xLength * xFlip);

    Vector yJump = * d;
    yJump.mult(yLength * yFlip);


    while (true)
    {
      double xDis = abs(pos->x - xPos.x) + abs(pos->y - xPos.y);
      double yDis = abs(pos->x - yPos.x) + abs(pos->y - yPos.y);

      if(isnan(yDis) || xDis < yDis)
      {

        int x = xPos.x - ((xFlip - 1) / -2);
        int y = floor(xPos.y);

        if(map->hit(x, y))
        {
          return xPos.dis(*pos);
        }

        xPos.add(xJump);
      }

      else
      {
        int x = floor(yPos.x);
        int y = yPos.y - ((yFlip - 1) / -2);

        if(map->hit(x, y))
        {
            return yPos.dis(*pos);
        }

        yPos.add(yJump);
      }
    }
  }

  double * castRayField(int n)
  {
    double * dis = new double[n];

    double m = (n + 1) / 2.0;

    for (int i = 1; i <= n; i++)
    {
      Vector dirC = *dir;
      double ang = ((((i - ((n + 1) /  2.0)) / ((n - 1) / 2.0)) * (fov / 2)) * M_PI) / 180;

      dirC.turn(ang);



      dis[i - 1] = castRay(&dirC);
    }

    return dis;
  }
};
