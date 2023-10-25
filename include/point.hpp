#ifndef POINT_HPP
#define POINT_HPP

class Point {
public:
  Point(int x, int y);
  int getX() const;
  int getY() const;
  void setX(int x);
  void setY(int y);
  // std::string toString();

private:
  int m_x;
  int m_y;
};

#endif