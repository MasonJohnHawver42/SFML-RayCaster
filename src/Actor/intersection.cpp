#include "../Wall/wall.cpp"

class Intersection {
private:
  Vector<double> * pos;
  Vector<int> * wallPos;
  double slice;

public:
  Intersection()
  {
    pos = new Vector<double>();
    wallPos = new Vector<int>();
  }

  Intersection(Vector<double> * p, Vector<int> * wp, double s)
  {
    pos = p;
    wallPos = wp;
    slice = s;
  }

  Vector<double> * getHit();
  Vector<int> * getWall();
  double getSlice();
};

Vector<double> * Intersection::getHit() { return pos; }
Vector<int> * Intersection::getWall() { return wallPos; }
double Intersection::getSlice() { return slice; }
