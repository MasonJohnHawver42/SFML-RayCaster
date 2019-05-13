#include "camera.cpp"
#include <ncurses.h>
#include <unistd.h>

class GameManager
{
public:
  Map * map;
  Camera * cam;

  GameManager(Map * m)
  {
    map = m;
    cam = new Camera(map);
  }

  void init()
  {
    initscr();
    clear();

    start_color();

    noecho();
    cbreak();
    curs_set (0);
    nodelay(stdscr, TRUE);

    //drawMap();
  }

  void update()
  {
    map->update(getch());
    cam->setDir(&map->player->dir);
    cam->setPos(&map->player->pos);
    draw();
    drawMap();

  }

  void end()
  {
    endwin();
  }

  void drawRect(int x, int y, int w, int h, char c)
  {
    for(int i = 0; i < h; i++)
    {
      for(int j = 0; j < w; j++)
      {
        mvaddch(y + i, x + j, c);
      }
    }
  }

  void draw()
  {

    int width = 340;
    int height = 60;

    int n = 200;

    int w = width / n;

    int max_dis = map->width + map->height;

    double * dis = cam->castRayField(n);
    for(int i = 0; i < n; i++)
    {
      //char ch = chars[max(0, 5, (int)(5 / *(dis + i)))];
      int h = (int)(height / *(dis + i));
      drawRect((i * w) + 0, (int)(height - h) / 2, w, min(h, height - (int)(height - h) / 2), 128);
      drawRect((i * w) + 0, 0, w, (int)(height - h) / 2, ' ');
      drawRect((i * w) + 0,((int)(height - h) / 2) + h, w, height - (h + ((int)(height - h) / 2)), '_');
      //printw(to_string(*(dis + i)).c_str());
    }
  }

  void drawMap()
  {
    for(int i = 0; i < map->height; i++)
    {
      for(int j = 0; j < map->width; j++)
      {
        mvaddch(i, j, *map->tiles[i][j].toString());
      }
    }

    mvaddch((int) map->player->pos.y, (int) map->player->pos.x, 'P');
  }


  void run()
  {
    init();

    while (1) { update(); usleep(1000);}

    end();

  }



};
