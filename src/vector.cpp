#include <math.h>
#include <iostream>

using namespace std;


template<class T> class Vector
{
private:
  T x;
  T y;

public:
  Vector() {}

  Vector(T x1, T y1)
  {
    x = x1;
    y = y1;
  }


  T getX();
  T getY();

  void setX(T newX);
  void setY(T newY);

  void add(Vector<T> other);
  void sub(Vector<T> other);
  void mult(Vector<T> other);
  void div(Vector<T> other);

  void add(double val);
  void sub(double val);
  void mult(double val);
  void div(double val);

  double getDis(Vector<T> other);

  void perp();

  double getMag();
  void normalize();
  void setMag(double mag);

  void turn(double rad);

  double getRad();

  void toString();

  static Vector<double>* radianToVector(double rad);
  static Vector<double>* degreeToVector(double ang);


};

//getters :

template<class T> T Vector<T>::getX() { return x; }
template<class T> T Vector<T>::getY() { return y; }

template<class T> double Vector<T>::getDis(Vector<T> other){
  return sqrt(pow(x - other.getX(), 2) + pow(y - other.getY(), 2));
}

template<class T> double Vector<T>::getMag() { return sqrt(pow(x, 2) + pow(y, 2)); }

//setters :

template<class T> void Vector<T>::setX(T newX) { x = newX; }
template<class T> void Vector<T>::setY(T newY) { y = newY; }

// mutators :

template<class T> void Vector<T>::add(Vector<T> other) {
  x += other.getX();
  y += other.getY();
}

template<class T> void Vector<T>::sub(Vector<T> other) {
  x -= other.getX();
  y -= other.getY();
}

template<class T> void Vector<T>::mult(Vector<T> other) {
  x *= other.getX();
  y *= other.getY();
}

template<class T> void Vector<T>::div(Vector<T> other) {
  x /= other.getX();
  y /= other.getY();
}

// --

template<class T> void Vector<T>::add(double val) {
  y += val;
  x += val;
}

template<class T> void Vector<T>::sub(double val) {
  y -= val;
  x -= val;
}

template<class T> void Vector<T>::mult(double val) {
  y *= val;
  x *= val;
}

template<class T> void Vector<T>::div(double val) {
  y /= val;
  x /= val;
}

// --

template<class T> void Vector<T>::perp()
{
  T temp = y;
  y = -x;
  x = temp;
}

// --

template<class T> void Vector<T>::normalize() { div(getMag()); }
template<class T> void Vector<T>::setMag(double mag) { normalize(); mult(mag); }

//--
template<class T> void Vector<T>::turn(double rad) {
  double new_x = (x * cos(rad)) - (y * sin(rad));
  double new_y = (x * sin(rad)) + (y * cos(rad));

  x = new_x;
  y = new_y;
}

//--
template<class T> double Vector<T>::getRad() {
  int flip = (int)(abs(x) / x) - 1;
  return atan(y / x) + ((M_PI / 2) * flip);
}


template<class T> Vector<double>* Vector<T>::radianToVector(double rad) { return new Vector<double>(cos(rad), sin(rad)); }
template<class T> Vector<double>* Vector<T>::degreeToVector(double ang) { return radianToVector((ang * M_PI) / 180.0); }


template<class T> void Vector<T>::toString() { std::cout << "Vector:[x=" << x << ", y=" << y << "]"<< '\n';}
