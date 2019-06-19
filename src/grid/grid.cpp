#include "../vector.cpp"
#include <iostream>
#include <string>

template<class T>
class Grid
{
protected:
  T*** board;

  int rows;
  int cols;

public:
  Grid()
  {
    rows = 10;
    cols = 10;

    board = new T**[10];

    for (int i = 0; i < 10; ++i) {
      board[i] = new T*[10];
    }
  }
  Grid(int r, int c)
  {
    rows = r;
    cols = c;

    board = new T**[r];

    for (int i = 0; i < r; ++i) {
      board[i] = new T*[c];
    }
  }

  int getRows();
  int getCols();

  T* get(Vector<int> loc);
  void put(T* obj, Vector<int> loc);

  bool isValid(Vector<int> loc);
  bool isOcupied(Vector<int> loc);

  void toString();


};

template<class T> int Grid<T>::getRows() { return rows; }
template<class T> int Grid<T>::getCols() { return cols; }

template<class T> T* Grid<T>::get(Vector<int> loc) {
  if(isValid(loc)) {
    return board[loc.getY()][loc.getX()];
  }
}

template<class T> void Grid<T>::put(T* obj, Vector<int> loc)
{
  if(isValid(loc)) {
    board[loc.getY()][loc.getX()] = obj;
  }
}

template<class T> bool Grid<T>::isValid(Vector<int> loc) {
  return (0 <= loc.getY() && getRows() > loc.getY()) && (0 <= loc.getX() && getCols() > loc.getX());
}

template<class T> bool Grid<T>::isOcupied(Vector<int> loc) {
  if(isValid(loc)) {
    return dynamic_cast<T*>(get(loc));
  }

  return false;
}

template<class T> void Grid<T>::toString() {

  for(int i = 0; i < rows; i++)
  {
    std::string line = "";
    for(int j = 0; j < cols; j++)
    {
      line += (isOcupied(*new Vector<int>(j, i)) ? "# " : "  ");
    }
    std::cout << line << '\n';
  }
}
