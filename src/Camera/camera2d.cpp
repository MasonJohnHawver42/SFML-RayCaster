#include "camera2d.cpp"

class Camera2D: public Camera {
private:
  double hieght;
public:
  Camera2D(World * w, Vector<double> * p, double dir)
  : Camera(w, p, dir) { hieght = 10; }

  double getHeight();
  void setHieght(double h);

  void display(sf::RenderWindow * window);
};

double Camera2D::getHeight() { return hieght; }
void Camera2D::setHieght(double h) { hieght = h; }
